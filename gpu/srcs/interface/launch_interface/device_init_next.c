/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   device_init_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 18:04:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 18:04:27 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_FONT

#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include <assert.h>

void	defaut_opengl_state(void)
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

void	device_command(struct device *dev, struct nk_context *ctx,
		t_screen *screen)
{
	const struct nk_draw_command	*cmd;
	const nk_draw_index				*offset = NULL;

	cmd = nk__draw_begin(ctx, &dev->cmds);
	while (cmd != 0)
	{
		glBindTexture(GL_TEXTURE_2D, (GLuint)cmd->texture.id);
		glScissor(
			(GLint)(cmd->clip_rect.x * screen->scale.x),
			(GLint)((screen->height - (GLint)(cmd->clip_rect.y
						+ cmd->clip_rect.h)) * screen->scale.y),
			(GLint)(cmd->clip_rect.w * screen->scale.x),
			(GLint)(cmd->clip_rect.h * screen->scale.y));
		glDrawElements(GL_TRIANGLES, (GLsizei)cmd->elem_count,
				GL_UNSIGNED_SHORT, offset);
		offset += cmd->elem_count;
		cmd = nk__draw_next(cmd, &dev->cmds, ctx);
	}
}

void	device_draw(struct device *dev, struct nk_context *ctx,\
					t_screen *screen, enum nk_anti_aliasing aa)
{
	GLfloat ortho[4][4];

	ortho[0][0] = 2.0f / (GLfloat)screen->width;
	ortho[0][1] = 0.0f;
	ortho[0][2] = 0.0f;
	ortho[0][3] = 0.0f;
	ortho[1][0] = 0.0f;
	ortho[1][1] = -2.0f / (GLfloat)screen->height;
	ortho[1][2] = 0.0f;
	ortho[1][3] = 0.0f;
	ortho[2][0] = 0.0f;
	ortho[2][1] = 0.0f;
	ortho[2][2] = -1.0f;
	ortho[2][3] = 0.0f;
	ortho[3][0] = -1.0f;
	ortho[3][1] = 1.0f;
	ortho[3][2] = 0.0f;
	ortho[3][3] = 1.0f;
	set_up_global_state(dev, ortho);
	allocate_vertex_buffer(dev, aa, ctx);
	device_command(dev, ctx, screen);
	nk_clear(ctx);
	defaut_opengl_state();
}

void	init_glfw_start(GLFWwindow **w, struct nk_context *ctx,
		t_screen *screen)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		show_error("[GFLW] failed to init!\n");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	*w = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "RAYTRACER", NULL, NULL);
	glfwMakeContextCurrent(*w);
	glfwSetWindowUserPointer(*w, ctx);
	glfwSetCharCallback(*w, text_input);
	glfwSetScrollCallback(*w, scroll_input);
	glfwGetWindowSize(*w, &screen->width, &screen->height);
	glfwGetFramebufferSize(*w,
			&screen->display_width, &screen->display_height);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK)
		show_error("Failed to setup GLEW\n");
}
