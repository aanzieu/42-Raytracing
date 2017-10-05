/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 20:47:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 19:32:47 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

void		clear(struct nk_context *ctx, t_world *w)
{
	if (w->redraw == 3)
	{
		nk_clear(ctx);
		w->redraw = 0;
	}
}

static void	get_mouse_hover_gui(struct nk_context *ctx, t_world *w)
{
	if (nk_input_is_mouse_hovering_rect(&ctx->input,\
	nk_rect((w->screen.width / 2) - 200, w->screen.height - 76, 140, 76))\
	|| nk_input_is_mouse_hovering_rect(&ctx->input,\
	nk_rect((w->screen.width / 2) - 60, w->screen.height - 76, 240, 76))\
	|| nk_input_is_mouse_hovering_rect(&ctx->input,\
	nk_rect(0, 0, w->screen.width, 52))\
	|| nk_input_is_mouse_hovering_rect(&ctx->input,\
	nk_rect(w->screen.width - 250, 52, 250, w->screen.height - 52))\
	|| nk_input_is_mouse_hovering_rect(&ctx->input,\
	nk_rect(0, 52, 250, w->screen.height - 52)))
		w->hover_ui = 1;
	else if (w->hover_menu == 1)
		w->hover_ui = 1;
	else
		w->hover_ui = 0;
}

void		text_input(GLFWwindow *win, unsigned int codepoint)
{
	nk_input_unicode((struct nk_context*)
	glfwGetWindowUserPointer(win), codepoint);
}

void		scroll_input(GLFWwindow *win, double u, double yoff)
{
	UNUSED(u);
	nk_input_scroll((struct nk_context*)
	glfwGetWindowUserPointer(win), nk_vec2(0, (float)yoff));
}

void		gui_calls(struct nk_context *ctx, struct media *media,\
						t_world *world)
{
	if (world->a_h != NULL)
	{
		scene_parameters(ctx, media, world);
		camera_control_bar(ctx, media, world);
		render_scene(ctx, media, world);
		objects_param(ctx, media, world);
		scene_topbar(ctx, media, world);
	}
	else
	{
		objects_param(ctx, media, world);
		scene_topbar(ctx, media, world);
	}
	get_mouse_hover_gui(ctx, world);
}
