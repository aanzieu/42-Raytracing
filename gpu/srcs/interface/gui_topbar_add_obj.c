/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_topbar_add_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 14:36:02 by PZC               #+#    #+#             */
/*   Updated: 2017/09/25 15:04:28 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../../includes/light.h"
#include "header/nuklear.h"
#include "header/gui.h"

static void	draw_topbar_add_objects_4(struct nk_context *c, struct media *m,\
								t_world *w)
{
	if (nk_menu_item_image_label(c, m->paraboloid, "PARABOLOID", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_paraboloid(&w->paraboloids,\
			&w->paraboloids_tmp, &w->paraboloids_len, w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->mobius, "MOBIUS", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_mobius(&w->mobius, &w->mobius_tmp,\
			&w->mobius_len, w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->h_cube, "HOLLOW CUBE", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_h_cube(&w->h_cubes, &w->h_cubes_tmp,\
			&w->h_cubes_len, w->id++);
		w->redraw = 1;
	}
}

static void	draw_topbar_add_objects_3(struct nk_context *c, struct media *m,\
								t_world *w)
{
	if (nk_menu_item_image_label(c, m->cube, "CUBE", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_cube(&w->cubes, &w->cubes_tmp, &w->cubes_len,\
			w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->triangle, "TRIANGLE", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_triangle(&w->triangles, &w->triangles_tmp,\
			&w->triangles_len, w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->hyperboloid, "HYPERBOLOID",\
		NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_hyperboloid(&w->hyperboloids,\
			&w->hyperboloids_tmp, &w->hyperboloids_len, w->id++);
		w->redraw = 1;
	}
	draw_topbar_add_objects_4(c, m, w);
}

static void	draw_topbar_add_objects_2(struct nk_context *c, struct media *m,\
								t_world *w)
{
	if (nk_menu_item_image_label(c, m->plane, "PLANE", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_plane(&w->planes, &w->planes_tmp,\
			&w->planes_len, w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->disk, "DISK", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_disk(&w->disks, &w->disks_tmp, &w->disks_len,\
			w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->torus, "TORUS", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_torus(&w->torus, &w->torus_tmp, &w->torus_len,\
			w->id++);
		w->redraw = 1;
	}
	draw_topbar_add_objects_3(c, m, w);
}

void		draw_topbar_add_objects(struct nk_context *c, struct media *m,\
								t_world *w)
{
	if (nk_menu_item_image_label(c, m->sphere, "SPHERE", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_sphere(&w->spheres, &w->spheres_tmp,\
			&w->spheres_len, w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->cone, "CONE", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_cone(&w->cones, &w->cones_tmp, &w->cones_len,\
			w->id++);
		w->redraw = 1;
	}
	if (nk_menu_item_image_label(c, m->cylinder, "CYLINDER", NK_TEXT_RIGHT))
	{
		if (w->a_h != NULL)
			thread_free_and_add_cylinder(&w->cylinders, &w->cylinders_tmp,\
			&w->cylinders_len, w->id++);
		w->redraw = 1;
	}
	draw_topbar_add_objects_2(c, m, w);
}
