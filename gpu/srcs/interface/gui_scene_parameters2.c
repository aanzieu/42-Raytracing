/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_parameters2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 13:15:26 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 15:26:05 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include <vectors.h>
#include <gpu_rt.h>

static void	draw_objects_button_1(struct nk_context *ctx, struct media *media,\
								t_world *w)
{
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->sphere))
	{
		if (w->a_h != NULL)
			thread_free_and_add_sphere(&w->spheres, &w->spheres_tmp,\
			&w->spheres_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->cone))
	{
		if (w->a_h != NULL)
			thread_free_and_add_cone(&w->cones, &w->cones_tmp,\
			&w->cones_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->cylinder))
	{
		if (w->a_h != NULL)
			thread_free_and_add_cylinder(&w->cylinders, &w->cylinders_tmp,\
			&w->cylinders_len, w->id++);
		w->redraw = 1;
	}
}

static void	draw_objects_button_2(struct nk_context *ctx, struct media *media,\
								t_world *w)
{
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->plane))
	{
		if (w->a_h != NULL)
			thread_free_and_add_plane(&w->planes, &w->planes_tmp,\
			&w->planes_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->disk))
	{
		if (w->a_h != NULL)
			thread_free_and_add_disk(&w->disks, &w->disks_tmp,\
			&w->disks_len, w->id++);
		w->redraw = 1;
	}
	nk_layout_row_push(ctx, 32);
	if (nk_button_image(ctx, media->torus))
	{
		if (w->a_h != NULL)
			thread_free_and_add_torus(&w->torus, &w->torus_tmp,\
			&w->torus_len, w->id++);
		w->redraw = 1;
	}
}

static void	draw_objects_button(struct nk_context *ctx, struct media *media,\
							t_world *w)
{
	nk_layout_row_begin(ctx, NK_STATIC, 32, 6);
	{
		draw_objects_button_1(ctx, media, w);
		draw_objects_button_2(ctx, media, w);
		draw_objects_button_3(ctx, media, w);
	}
	nk_layout_row_end(ctx);
}

static void	draw_lights_button(struct nk_context *ctx, struct media *media,\
							t_world *world, int i)
{
	t_light *tmp;
	char	*light;
	char	*id;

	tmp = world->lights_tmp;
	nk_layout_row_begin(ctx, NK_STATIC, 20, 2);
	{
		while (tmp)
		{
			nk_layout_row_push(ctx, 106);
			id = ft_itoa(i++);
			light = ft_strjoin("LIGHT #", id);
			ft_strdel(&id);
			nk_style_set_font(ctx, &media->font_14->handle);
			if (nk_button_text(ctx, light, ft_strlen(light)))
			{
				world->ob_save = 'l';
				world->id_save = tmp->id;
			}
			ft_strdel(&light);
			tmp = tmp->next;
		}
	}
	nk_layout_row_end(ctx);
}

void		scene_parameters_next(struct nk_context *ctx, struct media *media,\
							t_world *world)
{
	ui_widget_centered(ctx, media, 10);
	ui_header(ctx, media, "---- Light's List");
	ui_widget_centered(ctx, media, 20);
	if (nk_button_text(ctx, "+ ADD LIGHT", ft_strlen("+ ADD LIGHT")))
	{
		if (world->a_h != NULL)
			thread_free_and_add_light(&world->lights, &world->lights_tmp,\
			&world->lights_len, world->id++);
		world->redraw = 1;
	}
	if (world->lights_len)
		draw_lights_button(ctx, media, world, 1);
	ui_widget_centered(ctx, media, 5);
	ui_header(ctx, media, "---- Add Objects");
	draw_objects_button(ctx, media, world);
}
