/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 11:24:54 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"
#include "float.h"

static void	intersection_find(t_world *world, t_ray ray)
{
	t_intersection	intersection;

	intersection.t = DBL_MAX;
	intersection.type = '0';
	intersection.id = -1;
	get_closest_intersection(*(world), ray, &intersection);
	if (intersection.t != INFINITY)
	{
		world->id_save = intersection.id_save;
		world->ob_save = intersection.type;
		world->keys.select = 1;
	}
}

int			mousepress_left(struct nk_context *ctx, t_world *world,\
						struct nk_vec2 pos)
{
	t_ray			ray;
	t_vec2d			pad;
	static int		press;

	if (ctx->input.mouse.buttons[NK_BUTTON_LEFT].down && world->menu_on == 0)
	{
		pad.x = ctx->input.mouse.pos.x - pos.x;
		pad.y = ctx->input.mouse.pos.y - pos.y - 40;
		if (pad.x < 0 || pad.y < 0 || pad.x > WIN_WIDTH || pad.y > WIN_HEIGHT)
			return (0);
		press = 2;
		get_up_left(world);
		get_ray_direction(*(world), &ray, pad.x / world->render_factor,\
						pad.y / world->render_factor);
		intersection_find(world, ray);
	}
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		press = -1;
		return (1);
	}
	return (0);
}
