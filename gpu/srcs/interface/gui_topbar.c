/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_topbar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:10:35 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 19:16:16 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "light.h"
#include "nuklear.h"
#include "gui.h"
#include "parse.h"

static void	add_object(struct nk_context *ctx, struct media *media,\
					t_world *world, int img_active[5])
{
	nk_layout_row_push(ctx, 60);
	if (nk_menu_begin_text(ctx, "Add", 3, NK_TEXT_CENTERED, nk_vec2(600, 90)))
	{
		img_active[3] = 1;
		nk_layout_row_dynamic(ctx, 20, 4);
		draw_topbar_add_objects(ctx, media, world);
		nk_menu_end(ctx);
	}
	else
		img_active[3] = 0;
}

static void	file_open(struct nk_context *ctx, struct media *media,\
					t_world *world, int img_active[5])
{
	nk_layout_row_push(ctx, 60);
	if (nk_menu_begin_text(ctx, "File", 4, NK_TEXT_CENTERED, nk_vec2(180, 90)))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		if (nk_menu_item_image_label(ctx, media->dir, "Open a scene",\
			NK_TEXT_RIGHT))
			img_active[0] = 1;
		if (nk_menu_item_image_label(ctx, media->icons.default_file,\
			"Open your file", NK_TEXT_RIGHT))
			img_active[4] = 1;
		if (nk_menu_item_image_label(ctx, media->icons.default_file,\
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

static void	file_save(struct nk_context *ctx, struct media *media,\
					t_world *world)
{
	nk_layout_row_push(ctx, 60);
	if (nk_menu_begin_text(ctx, "Save", 4, NK_TEXT_CENTERED, nk_vec2(180, 60)))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		if (nk_menu_item_image_label(ctx, media->convert, "Save as xml",\
			NK_TEXT_RIGHT) && world->a_h)
			save_xml_scene(world);
		if (nk_menu_item_image_label(ctx, media->convert, "Save as bitmap",\
			NK_TEXT_RIGHT))
		{
			if (world->a_h != NULL)
				savebmp(world);
		}
		nk_menu_end(ctx);
	}
}

static void	file_edit(struct nk_context *ctx, struct media *media)
{
	nk_layout_row_push(ctx, 60);
	if (nk_menu_begin_text(ctx, "Edit", 4, NK_TEXT_CENTERED, nk_vec2(180, 60)))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		if (nk_menu_item_image_label(ctx, media->dir, "Images folder",\
			NK_TEXT_RIGHT))
			system("open ./screenshots");
		nk_menu_end(ctx);
	}
}

void		scene_topbar(struct nk_context *ctx, struct media *media,\
					t_world *world)
{
	static int img_active[5];

	if (nk_begin(ctx, "TOPBAR", nk_rect(0, 0, world->screen.width, 52),\
		NK_WINDOW_BORDER))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 30, 5);
		{
			nk_layout_row_push(ctx, 40);
			nk_image(ctx, media->rocket);
			file_open(ctx, media, world, img_active);
			file_save(ctx, media, world);
			file_edit(ctx, media);
			add_object(ctx, media, world, img_active);
		}
		nk_layout_row_end(ctx);
		select_your_file(ctx, media, world, img_active);
		select_scene(ctx, media, world, img_active);
		if (img_active[0] == 1 || img_active[3] == 1 || img_active[4] == 1)
			world->hover_menu = 1;
		else
			world->hover_menu = 0;
	}
	nk_end(ctx);
}
