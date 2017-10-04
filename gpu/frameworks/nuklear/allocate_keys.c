/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 16:00:05 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 16:49:34 by aanzieu          ###   ########.fr       */
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
#include "nuklear.h"
#include "gui.h"

void	allocate_mouse(struct nk_context *c, GLFWwindow *w)
{
	double x;
	double y;

	nk_input_key(c, NK_KEY_SPACE, glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_SHIFT, glfwGetKey(w, GLFW_KEY_LEFT_SHIFT)
			== GLFW_PRESS);
	nk_input_key(c, NK_KEY_CTRL, glfwGetKey(w, GLFW_KEY_LEFT_CONTROL)
			== GLFW_PRESS);
	glfwGetCursorPos(w, &x, &y);
	nk_input_motion(c, (int)x, (int)y);
	nk_input_button(c, NK_BUTTON_LEFT, (int)x, (int)y,
			glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
	nk_input_button(c, NK_BUTTON_MIDDLE, (int)x, (int)y,
			glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
	nk_input_button(c, NK_BUTTON_RIGHT, (int)x, (int)y,
			glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
	nk_input_end(c);
}

void	allocate_keys(struct nk_context *c, GLFWwindow *w)
{
	nk_input_key(c, NK_KEY_DEL, glfwGetKey(w, GLFW_KEY_DELETE) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_ENTER, glfwGetKey(w, GLFW_KEY_ENTER) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_TAB, glfwGetKey(w, GLFW_KEY_TAB) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_BACKSPACE, glfwGetKey(w, GLFW_KEY_BACKSPACE)
			== GLFW_PRESS);
	nk_input_key(c, NK_KEY_LEFT, glfwGetKey(w, GLFW_KEY_LEFT) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_RIGHT, glfwGetKey(w, GLFW_KEY_RIGHT) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_UP, glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_DOWN, glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_K, glfwGetKey(w, GLFW_KEY_K) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_L, glfwGetKey(w, GLFW_KEY_L) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_X, glfwGetKey(w, GLFW_KEY_X) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_A, glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_S, glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_D, glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_W, glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_Q, glfwGetKey(w, GLFW_KEY_Q) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_E, glfwGetKey(w, GLFW_KEY_E) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_ECHAP, glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_ADD, glfwGetKey(w, GLFW_KEY_KP_ADD) == GLFW_PRESS);
	nk_input_key(c, NK_KEY_SUB, glfwGetKey(w, GLFW_KEY_KP_SUBTRACT)
			== GLFW_PRESS);
	allocate_mouse(c, w);
}

void	allocate_vertex_buffer_next(struct nk_context *ctx,
		struct device *dev, struct nk_convert_config config)
{
	void				*vertices;
	void				*elements;
	struct nk_buffer	vbuf;
	struct nk_buffer	ebuf;

	vertices = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	elements = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	nk_buffer_init_fixed(&vbuf, vertices, MAX_VERTEX_MEMORY);
	nk_buffer_init_fixed(&ebuf, elements, MAX_ELEMENT_MEMORY);
	nk_convert(ctx, &dev->cmds, &vbuf, &ebuf, &config);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

int		render_condition(struct nk_context *ctx, t_world *world)
{
	if (ctx->input.keyboard.keys[NK_KEY_ECHAP].down != 0)
	{
		clear_world(world);
		ft_printf("Thank you to played with us");
		return (0);
	}
	if (nk_input_is_key_pressed(&ctx->input, NK_KEY_SPACE)
			&& world->render_factor != 32)
	{
		if(world->on == 1)
			world->render_factor = 16;
		world->redraw = 1;
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_SPACE))
	{
		world->render_factor = 1;
		world->ob_save = '\0';
		world->id_save = -1;
		world->redraw = 1;
	}
	return (1);
}
