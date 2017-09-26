/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 18:02:40 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"
#include "float.h"

int		mousepress_left(struct nk_context *ctx, t_world *world, struct nk_vec2 pos)
{
	t_ray      		ray;
	t_intersection	intersection;
	t_vec2d			padding;

	intersection.t = DBL_MAX;
	intersection.type = '0';
	intersection.id = -1;
	if(ctx->input.mouse.buttons[NK_BUTTON_LEFT].down)
	{
		padding.x = ctx->input.mouse.pos.x - pos.x;
		padding.y = ctx->input.mouse.pos.y - pos.y - 40;
		if(padding.x < 0 || padding.y < 0 || padding.x > WIN_WIDTH || padding.y > WIN_HEIGHT)
			return (0);
		get_up_left(world);
		get_ray_direction(*(world), &ray, padding.x, padding.y);
		get_closest_intersection(*(world), ray, &intersection);
		if(intersection.t != INFINITY)
		{
			world->id_save = intersection.id_save;
			world->ob_save = intersection.type;
			world->keys.select = 1;
			return(1);

		}
	}
	return(0);
}