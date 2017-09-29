/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_parameters3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 15:00:25 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 15:26:46 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include <vectors.h>
#include <gpu_rt.h>

static void	draw_objects_button_4(struct nk_context *ctx, struct media *media,\
								t_world *w)
{
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->paraboloid))
	{
		if (w->a_h != NULL)
			thread_free_and_add_paraboloid(&w->paraboloids,\
			&w->paraboloids_tmp, &w->paraboloids_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->mobius))
	{
		if (w->a_h != NULL)
			thread_free_and_add_mobius(&w->mobius, &w->mobius_tmp,\
			&w->mobius_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->h_cube))
	{
		if (w->a_h != NULL)
			thread_free_and_add_h_cube(&w->h_cubes, &w->h_cubes_tmp,\
			&w->h_cubes_len, w->id++);
		w->redraw = 1;
	}
}

void		draw_objects_button_3(struct nk_context *ctx, struct media *media,\
								t_world *w)
{
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->cube))
	{
		if (w->a_h != NULL)
			thread_free_and_add_cube(&w->cubes, &w->cubes_tmp,\
			&w->cubes_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->triangle))
	{
		if (w->a_h != NULL)
			thread_free_and_add_triangle(&w->triangles, &w->triangles_tmp,\
			&w->triangles_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->hyperboloid))
	{
		if (w->a_h != NULL)
			thread_free_and_add_hyperboloid(&w->hyperboloids,\
			&w->hyperboloids_tmp, &w->hyperboloids_len, w->id++);
		w->redraw = 1;
	}
	draw_objects_button_4(ctx, media, w);
}
