/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_parameters2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 13:15:26 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/27 14:28:05 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include <vectors.h>
#include <gpu_rt.h>

static void	draw_objects_button(struct nk_context *ctx, struct media *media,\
							t_world *world)
{
	nk_layout_row_begin(ctx, NK_STATIC, 32, 6);
	{
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->sphere))
		{
			if (world->a_h != NULL)
				thread_free_and_add_sphere(&world->spheres, &world->spheres_tmp, &world->spheres_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->cone))
		{
			if (world->a_h != NULL)
				thread_free_and_add_cone(&world->cones, &world->cones_tmp, &world->cones_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->cylinder))
		{
			if (world->a_h != NULL)
				thread_free_and_add_cylinder(&world->cylinders, &world->cylinders_tmp, &world->cylinders_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->plane))
		{
			if (world->a_h != NULL)
				thread_free_and_add_plane(&world->planes, &world->planes_tmp, &world->planes_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->disk))
		{
			if (world->a_h != NULL)
				thread_free_and_add_disk(&world->disks, &world->disks_tmp, &world->disks_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->torus))
		{
			if (world->a_h != NULL)
				thread_free_and_add_torus(&world->torus, &world->torus_tmp, &world->torus_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->cube))
		{
			if (world->a_h != NULL)
				thread_free_and_add_cube(&world->cubes, &world->cubes_tmp, &world->cubes_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->triangle))
		{
			if (world->a_h != NULL)
				thread_free_and_add_triangle(&world->triangles, &world->triangles_tmp, &world->triangles_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->hyperboloid))
		{
			if (world->a_h != NULL)
				thread_free_and_add_hyperboloid(&world->hyperboloids, &world->hyperboloids_tmp, &world->hyperboloids_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->paraboloid))
		{
			if (world->a_h != NULL)
				thread_free_and_add_paraboloid(&world->paraboloids, &world->paraboloids_tmp, &world->paraboloids_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->mobius))
		{
			if (world->a_h != NULL)
				thread_free_and_add_mobius(&world->mobius, &world->mobius_tmp, &world->mobius_len, world->id++);
			world->redraw = 1;
		}
		nk_layout_row_push(ctx, 32);
		if (nk_button_image(ctx, media->h_cube))
		{
			if (world->a_h != NULL)
				thread_free_and_add_h_cube(&world->h_cubes, &world->h_cubes_tmp, &world->h_cubes_len, world->id++);
			world->redraw = 1;
		}
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
