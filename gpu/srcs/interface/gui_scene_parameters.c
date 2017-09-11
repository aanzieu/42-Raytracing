/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_parameters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:10:35 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/11 17:40:17 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include <vectors.h>
#include <gpu_rt.h>

/* ===============================================================
 *
 *                         SCENE_PARAMETERS
 *
 * ===============================================================*/

	void
scene_parameters(struct nk_context *ctx, struct media *media, t_world *world)
{
	static int option = 1;
	static int hd = 1;

	nk_style_set_font(ctx, &media->font_20->handle);
	if (nk_begin(ctx, "Scene parameters", nk_rect(0,52,250,650),
			NK_WINDOW_BORDER|NK_WINDOW_TITLE))
	{
		/*------------------------------------------------
		 *                  SCENE INFO
		 *------------------------------------------------*/

		ui_header(ctx, media, "---- Scene Active ----");
		nk_text(ctx, world->title, ft_strlen(world->title), NK_TEXT_LEFT);
		ui_widget_special_mode(ctx, media, 100);
		nk_image(ctx, media->images[world->img_scene]);

		ui_widget_centered(ctx, media, 5);

		/*------------------------------------------------
		 *                 CHOOSE DEFINITION
		 *------------------------------------------------*/

		ui_header(ctx, media, "---- Render Definition ----");
		ui_widget_special_mode(ctx, media, 20);
		if (nk_button_symbol_label(ctx, (hd == 0)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "HD", NK_TEXT_LEFT))
		{
			hd = 0;
			world->keys.light_none = 1;
			world->redraw = 1;
		}
		if (nk_button_symbol_label(ctx, (hd == 1)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "LOW", NK_TEXT_LEFT))
		{
			hd = 1;
			world->keys.light_none = 0;
			world->redraw = 1;
		}

		ui_widget_centered(ctx, media, 5);

		/*------------------------------------------------
		 *                  SPECIAL MODE
		 *------------------------------------------------*/

		ui_header(ctx, media, "---- Render Effects ----");
		ui_widget_special_mode(ctx, media, 20);
		if (nk_button_symbol_label(ctx, (option == 1)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NONE", NK_TEXT_LEFT))
		{
			option = 1;
			world->keys.pad_0 = 0;
			world->redraw = 1;
		}
		if (nk_button_symbol_label(ctx, (option == 0)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "SEPIA", NK_TEXT_LEFT))
		{
			option = 0;
			world->keys.pad_0 = 1;
			world->redraw = 1;
		}
		ui_widget_special_mode(ctx, media, 20);
		if (nk_button_symbol_label(ctx, (option == 2)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "BAYER", NK_TEXT_LEFT))
		{
			option = 2;
			world->keys.pad_0 = 2;
			world->redraw = 1;
		}
		if (nk_button_symbol_label(ctx, (option == 3)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "8 BITS", NK_TEXT_LEFT))
		{
			option = 3;
			world->keys.pad_0 = 3;
			world->redraw = 1;
		}
		ui_widget_special_mode(ctx, media, 20);
		if (nk_button_symbol_label(ctx, (option == 4)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "PASTEL", NK_TEXT_LEFT))
		{
			option = 4;
			world->keys.pad_0 = 4;
			world->redraw = 1;
		}
		if (nk_button_symbol_label(ctx, (option == 5)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "B&W", NK_TEXT_LEFT))
		{
			option = 5;
			world->keys.pad_0 = 5;
			world->redraw = 1;
		}
		ui_widget_special_mode(ctx, media, 20);
		if (nk_button_symbol_label(ctx, (option == 6)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "CARTOON", NK_TEXT_LEFT))
		{
			option = 6;
			world->keys.pad_0 = 6;
			world->redraw = 1;
		}

		if (nk_button_symbol_label(ctx, (option == 7)?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NEGATIVE", NK_TEXT_LEFT))
		{
			option = 7;
			world->keys.pad_0 = 7;
			world->redraw = 1;
		}

		/*------------------------------------------------
		 *                  AMBIENT
		 *------------------------------------------------*/

		ui_widget_centered(ctx, media, 5);

		ui_header(ctx, media, "---- Ambient Light ----");
		if(ui_widget_value_infos(ctx, media, &world->ambient.intensity, "Intensity"))
			world->redraw = 1;
			if(ui_widget_value_infos_int(ctx, media, &world->aa, "Anti Aliasing"))
			{
				printf("aa: %d\n", world->aa);
				world->redraw = 1;
			}
		/*------------------------------------------------
		 *                  ADD OBJECT
		 *------------------------------------------------*/

		ui_widget_centered(ctx, media, 5);
		ui_header(ctx, media, "---- Add Objects ----");

		nk_layout_row_begin(ctx, NK_STATIC, 40, 5);
		{
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->sphere))
			{
				if(world->a_h != NULL)
					thread_free_and_add_sphere(&world->spheres, &world->spheres_tmp, &world->spheres_len, world->id);
				world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->cone))
			{
				if(world->a_h != NULL)
					thread_free_and_add_cone(&world->cones, &world->cones_tmp, &world->cones_len, world->id);
				world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->cylinder))
			{
				if(world->a_h != NULL)
					thread_free_and_add_cylinder(&world->cylinders, &world->cylinders_tmp, &world->cylinders_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->plane))
			{
				if(world->a_h != NULL)
					thread_free_and_add_plane(&world->planes, &world->planes_tmp, &world->planes_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->disk))
			{
				if(world->a_h != NULL)
					thread_free_and_add_disk(&world->disks, &world->disks_tmp, &world->disks_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->torus))
			{
				if(world->a_h != NULL)
					thread_free_and_add_torus(&world->torus, &world->torus_tmp, &world->torus_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->cube))
			{
				if(world->a_h != NULL)
					thread_free_and_add_cube(&world->cubes, &world->cubes_tmp, &world->cubes_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->triangle))
			{
				if(world->a_h != NULL)
					thread_free_and_add_triangle(&world->triangles, &world->triangles_tmp, &world->triangles_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->hyperboloid))
			{
				if(world->a_h != NULL)
					thread_free_and_add_hyperboloid(&world->hyperboloids, &world->hyperboloids_tmp, &world->hyperboloids_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->paraboloid))
			{
				if(world->a_h != NULL)
					thread_free_and_add_paraboloid(&world->paraboloids, &world->paraboloids_tmp, &world->paraboloids_len, world->id);
					world->redraw = 1;
			}
			nk_layout_row_push(ctx, 40);
			if(nk_button_image(ctx, media->moebius))
			{
				if(world->a_h != NULL)
					thread_free_and_add_mobius(&world->mobius, &world->mobius_tmp, &world->mobius_len, world->id);
					world->redraw = 1;
			}
		}
		nk_layout_row_end(ctx);

		/*------------------------------------------------
		 *                  LOADER
		 *------------------------------------------------*/

		// ui_header(ctx, media, "---- Loader ----");
		// if (world->load != 100) {
		// 	char *p = ft_itoa(world->load);
		// 	nk_text(ctx, p, 3, NK_TEXT_LEFT);
		// 	ft_strdel(&p);
		// }
		// static size_t cur = 0;
		// nk_size max = 100;
		// nk_progress(ctx, &cur, max, 1);
		// cur = world->load;
		//printf("%zu %%\n", world->load);
		//printf("TEST\n");
	}
	nk_end(ctx);
}
