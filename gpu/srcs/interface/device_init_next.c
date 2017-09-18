/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device_init_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 11:30:46 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/13 13:52:31 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_FONT
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include <assert.h>

void	defaut_opengl_state()
{
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
	glDisable(GL_SCISSOR_TEST);
}

void	set_up_global_state(struct device *dev, GLfloat ortho[4][4])
{
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(dev->prog);
	glUniform1i(dev->uniform_tex, 0);
	glUniformMatrix4fv(dev->uniform_proj, 1, GL_FALSE, &ortho[0][0]);
}

void	device_draw(struct device *dev, struct nk_context *ctx,\
					t_screen *screen, enum nk_anti_aliasing AA)
{
	GLfloat ortho[4][4] = {{2.0f, 0.0f, 0.0f, 0.0f}, {0.0f,-2.0f, 0.0f, 0.0f},
		{0.0f, 0.0f,-1.0f, 0.0f}, {-1.0f,1.0f, 0.0f, 1.0f},};
	const struct nk_draw_command *cmd;
	const nk_draw_index *offset = NULL;

	ortho[0][0] /= (GLfloat)screen->width;
	ortho[1][1] /= (GLfloat)screen->height;
	set_up_global_state(dev, ortho);
	allocate_vertex_buffer(dev, AA, ctx);
	nk_draw_foreach(cmd, ctx, &dev->cmds)
	{
		if (!cmd->elem_count) continue;
		glBindTexture(GL_TEXTURE_2D, (GLuint)cmd->texture.id);
		glScissor(
			(GLint)(cmd->clip_rect.x * screen->scale.x),
			(GLint)((screen->height - (GLint)(cmd->clip_rect.y + cmd->clip_rect.h)) * screen->scale.y),
			(GLint)(cmd->clip_rect.w * screen->scale.x),
			(GLint)(cmd->clip_rect.h * screen->scale.y));
		glDrawElements(GL_TRIANGLES, (GLsizei)cmd->elem_count, GL_UNSIGNED_SHORT, offset);
		offset += cmd->elem_count;
	}
	nk_clear(ctx);
	defaut_opengl_state();
}

void init_glfw_start(GLFWwindow **win, struct nk_context *ctx, t_screen *screen)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		show_error("[GFLW] failed to init!\n");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	*win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"RAYTRACER", NULL, NULL);
	glfwMakeContextCurrent(*win);
	glfwSetWindowUserPointer(*win, ctx);
	glfwSetCharCallback(*win, text_input);
	glfwSetScrollCallback(*win, scroll_input);
	glfwGetWindowSize(*win, &screen->width, &screen->height);
	glfwGetFramebufferSize(*win, &screen->display_width, &screen->display_height);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK)
		show_error("Failed to setup GLEW\n");
}
