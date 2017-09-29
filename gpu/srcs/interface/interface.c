/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 20:47:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/29 12:38:12 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

void	text_input(GLFWwindow *win, unsigned int codepoint)
{
	nk_input_unicode((struct nk_context*)
	glfwGetWindowUserPointer(win), codepoint);
}

void	scroll_input(GLFWwindow *win, double u, double yoff)
{
	UNUSED(u);
	nk_input_scroll((struct nk_context*)
	glfwGetWindowUserPointer(win), nk_vec2(0, (float)yoff));
}

void	gui_calls(struct nk_context *ctx,\
					struct media *media, t_world *world)
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
}
