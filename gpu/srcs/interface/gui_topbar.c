/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_topbar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:10:35 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/11 17:19:25 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../../includes/light.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include "parse.h"

/* ===============================================================
 *
 *                              TOP BAR
 *
 * ===============================================================*/

void	clear_world(t_world *world)
{
	if(world->lights_tmp != NULL)
		free_light(&world->lights_tmp, &world->lights, &world->lights_len);
	if(world->spheres_tmp != NULL)
		free_sphere(&world->spheres_tmp, &world->spheres, &world->spheres_len);
	if(world->planes_tmp != NULL)
		free_plan(&world->planes_tmp, &world->planes, &world->planes_len);
	if(world->cylinders_tmp != NULL)
		free_cy(&world->cylinders_tmp, &world->cylinders, &world->cylinders_len);
	if(world->cones_tmp != NULL)
		free_cone(&world->cones_tmp, &world->cones, &world->cones_len);
	if(world->mobius_tmp != NULL)
		free_mobius(&world->mobius_tmp, &world->mobius, &world->mobius_len);
	if(world->torus_tmp != NULL)
		free_torus(&world->torus_tmp, &world->torus, &world->torus_len);
	if(world->hyperboloids_tmp != NULL)
		free_hyper(&world->hyperboloids_tmp, &world->hyperboloids, &world->hyperboloids_len);
	if(world->paraboloids_tmp != NULL)
		free_para(&world->paraboloids_tmp, &world->paraboloids, &world->paraboloids_len);
	if(world->cubes_tmp != NULL)
		free_cube(&world->cubes_tmp, &world->cubes, &world->cubes_len);
	if(world->triangles_tmp != NULL)
		free_triangle(&world->triangles_tmp, &world->triangles, &world->triangles_len);
	if(world->title != NULL)
	{
		free(world->title);
		world->title = NULL;
	}
	if(world->video_buffer != NULL)
	{
		free(world->video_buffer);
		world->video_buffer = NULL;
	}
	if(world->a_h != NULL)
	{
		free(world->a_h);
		world->a_h = NULL;
	}
}

void	file_open(struct nk_context *ctx, struct media *media, t_world *world, int image_active[3])
{
	/* file */
	nk_layout_row_push(ctx, 60);
	if (nk_menu_begin_text(ctx, "File", 4, NK_TEXT_CENTERED, nk_vec2(180, 60)))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		if(nk_menu_item_image_label(ctx, media->dir,
			"Open...", NK_TEXT_RIGHT))
			image_active[0] = !image_active[0];
		if(nk_menu_item_image_label(ctx, media->icons.default_file,
			"New file", NK_TEXT_RIGHT))
		{
			clear_world(world);
			parse_rtv1(world, "testfiles/new.xml");
			load_data(world);
			rt(world);
			world->img_scene = 0;
			world->redraw = 3;
		}
		nk_menu_end(ctx);
	}
}

void	file_save(struct nk_context *ctx, struct media *media, t_world *world)
{
	nk_layout_row_push(ctx, 60);
	if (nk_menu_begin_text(ctx, "Save", 4, NK_TEXT_CENTERED, nk_vec2(180, 60)))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		if(nk_menu_item_image_label(ctx, media->convert,
			"Save as xml", NK_TEXT_RIGHT))
			save_xml_scene(world);
		if(nk_menu_item_image_label(ctx, media->convert,
			"Save as bitmap", NK_TEXT_RIGHT))
			savebmp(world);
		nk_menu_end(ctx);
	}
}

void	file_edit(struct nk_context *ctx, struct media *media, t_world *world)
{
	/* edit */
	(void)world;
	nk_layout_row_push(ctx, 60);
	if (nk_menu_begin_text(ctx, "Edit", 4, NK_TEXT_CENTERED, nk_vec2(180, 60)))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		if(nk_menu_item_image_label(ctx, media->dir,
			"Images folder", NK_TEXT_RIGHT))
			system("open ./screenshots");
		nk_menu_end(ctx);
	}
}

void	video_launch(struct nk_context *ctx, struct media *media, t_world *world)
{
	static int toggle0 = 0;
	static int toggle1 = 1;

	(void)world;
	nk_layout_row_push(ctx, 100);
	if (nk_button_image_label(ctx, (toggle0)
	? media->rec_on: media->rec, "      Record", NK_TEXT_RIGHT))
	{
		toggle0 = !toggle0;
		toggle1 = !toggle1;
		// mode video active ou non !
	}
}

void	select_mode(struct nk_context *ctx, struct media *media, t_world *world)
{

	static int toggle2 = 1;
	static int toggle3 = 0;
	static int toggle4 = 1;
	static int toggle5 = 0;

	if (nk_button_image_label(ctx, (toggle2)
	? media->checked: media->unchecked, "Local", NK_TEXT_LEFT))
	{
		toggle2 = !toggle2;
		toggle3 = !toggle3;
		//rajouter mode Local
	}
	if (nk_button_image_label(ctx, (toggle3)
	? media->checked: media->unchecked, "Cluster", NK_TEXT_LEFT))
	{
		toggle3 = !toggle3;
		toggle2 = !toggle2;
		//rajouter mode Cluster
	}
	ui_header(ctx, media, "---- Choose CPU/GPU ----");
	ui_widget_small_button(ctx, media, 30);
	if (nk_button_image_label(ctx, (toggle4)
	? media->checked: media->unchecked, "Cpu", NK_TEXT_LEFT))
	{
		toggle4 = !toggle4;
		toggle5 = !toggle5;
		world->mode = 0;
	}
	if (nk_button_image_label(ctx, (toggle5)
	? media->checked: media->unchecked, "Gpu", NK_TEXT_LEFT))
	{
		toggle5 = !toggle5;
		toggle4 = !toggle4;
		world->mode = 1;
	}
}

void	press_launch(struct nk_context *ctx, t_world *world, int image_active[3])
{
	if (nk_button_label(ctx, "Launch"))
	{
		if (image_active[2] == 1)
		{
			clear_world(world);
			parse_rtv1(world, "testfiles/1.xml");
			load_data(world);
			rt(world);
			world->img_scene = 1;
			world->redraw = 3;
		}
		else if (image_active[2] == 2)
		{
			clear_world(world);
			parse_rtv1(world, "testfiles/2.xml");
			load_data(world);
			rt(world);
			world->img_scene = 2;
			world->redraw = 3;
		}
		else if (image_active[2] == 3)
		{
			clear_world(world);
			parse_rtv1(world, "testfiles/2.xml");
			load_data(world);
			rt(world);
			world->img_scene = 3;
			world->redraw = 3;
		}
		image_active[0] = 0;
		image_active[1] = 0;
		nk_popup_close(ctx);
	}
}

void	select_config(struct nk_context *ctx, struct media *media, t_world *world, int image_active[3])
{
	if (nk_popup_begin(ctx, NK_POPUP_STATIC,
		"Config Popup", 0, nk_rect(340, 50, 320, 220)))
	{
		ui_header(ctx, media, "---- Choose Local/Cluster ----");
		ui_widget_small_button(ctx, media, 30);
		select_mode(ctx, media, world);
		/*------------------------------------------------
		 *                  LAUNCH RT
		 *------------------------------------------------*/
		ui_header(ctx, media, "");
		ui_widget_centered(ctx, media, 30);
		press_launch(ctx, world, image_active);
		nk_popup_close(ctx);
		nk_popup_end(ctx);
	}
}

void	select_scene(struct nk_context *ctx, struct media *media, t_world *world, int image_active[3])
{
	int i = 0;
	/*------------------------------------------------
	*                  SELECTED SCENE
	*------------------------------------------------*/
	if (image_active[0])
	{
		if (nk_popup_begin(ctx, NK_POPUP_STATIC,
			"Scene Popup", 0, nk_rect(60, 50, 320, 220)))
		{
			nk_layout_row_static(ctx, 82, 82, 3);
			for (i = 1; i < 4; ++i)
			{
				if (nk_button_image(ctx, media->images[i]))
				{
					image_active[2] = i;
					image_active[1] = !image_active[1];
					nk_popup_close(ctx);
				}
				nk_popup_close(ctx);
			}
			nk_popup_end(ctx);
		}
		/*------------------------------------------------
		*                  SELECTED CONFIG
		*------------------------------------------------*/
		if (image_active[1])
			select_config(ctx, media, world, image_active);
	}
}

void scene_topbar(struct nk_context *ctx, struct media *media, t_world *world)
{
	static int image_active[3];

	nk_style_set_font(ctx, &media->font_22->handle);
	if(nk_begin(ctx, "TOPBAR", nk_rect(0,0,world->screen.width,52), NK_WINDOW_BORDER))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 30, 5);
		{
			nk_layout_row_push(ctx, 40);
			nk_image(ctx, media->rocket);
			file_open(ctx, media, world, image_active);
			file_save(ctx, media, world);
			file_edit(ctx, media, world);
			video_launch(ctx, media, world);
		}
		nk_layout_row_end(ctx);
		select_scene(ctx, media, world, image_active);

	}
	nk_end(ctx);
}
