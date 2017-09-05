/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topbar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:10:35 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/05 16:53:15 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include "parse.h"

/* ===============================================================
 *
 *                              TOP BAR
 *
 * ===============================================================*/

	void
scene_topbar(struct nk_context *ctx, struct media *media, t_world *world)
{
	(void)world;
	static int image_active;
	static int image_active_2;
	static int toggle0 = 0;
	static int toggle1 = 1;
	static int toggle2 = 1;
	static int toggle3 = 0;
	static int toggle4 = 1;
	static int toggle5 = 0;
	int i = 0;
	//static int selected_image;

	nk_style_set_font(ctx, &media->font_22->handle);
	if(nk_begin(ctx, "TOPBAR", nk_rect(0,0,world->screen.width,52), NK_WINDOW_BORDER))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 30, 5);
		{
			nk_layout_row_push(ctx, 60);
			nk_label(ctx, "RT", NK_TEXT_CENTERED);
			/* file */
			nk_layout_row_push(ctx, 60);
			if (nk_menu_begin_text(ctx, "File", 4, NK_TEXT_CENTERED, nk_vec2(180, 60)))
			{
				nk_layout_row_dynamic(ctx, 20, 1);
				if(nk_menu_item_image_label(ctx, media->dir,
					"Open...", NK_TEXT_RIGHT))
					image_active = !image_active;
				if(nk_menu_item_image_label(ctx, media->icons.default_file,
					"New file", NK_TEXT_RIGHT))
				{
					parse_rtv1(world, "testfiles/new.xml");
					load_data(world);
					rt(world);
				}
				nk_menu_end(ctx);
			}
			/* save */
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
			/* edit */
			nk_layout_row_push(ctx, 60);
			if (nk_menu_begin_text(ctx, "Edit", 4, NK_TEXT_CENTERED, nk_vec2(180, 60)))
			{
				nk_layout_row_dynamic(ctx, 20, 1);
				if(nk_menu_item_image_label(ctx, media->dir,
					"Images folder", NK_TEXT_RIGHT))
					system("open ./screenshots");
				nk_menu_end(ctx);
			}
			nk_layout_row_push(ctx, 100);
			if (nk_button_image_label(ctx, (toggle0)
			? media->rec_on: media->rec, "      Record", NK_TEXT_RIGHT))
			{
				toggle0 = !toggle0;
				toggle1 = !toggle1;
				// mode video active ou non !
			}
		}
		nk_layout_row_end(ctx);

		/*------------------------------------------------
		*                  SELECTED SCENE
		*------------------------------------------------*/
		if (image_active)
		{
			if (nk_popup_begin(ctx, NK_POPUP_STATIC,
				"Scene Popup", 0, nk_rect(60, 50, 320, 220)))
			{
				nk_layout_row_static(ctx, 82, 82, 3);
				for (i = 0; i < 2; ++i)
				{
					if (nk_button_image(ctx, media->images[i]))
					{
						//selected_image = i;
						if (i == 0)
							parse_rtv1(world, "testfiles/1.xml");
						if (i == 1)
							parse_rtv1(world, "testfiles/2.xml");
						load_data(world);
						image_active_2 = !image_active_2;
						nk_popup_close(ctx);
					}
					nk_popup_close(ctx);
				}
				nk_popup_end(ctx);
			}
		}
		/*------------------------------------------------
		*                  SELECTED CONFIG
		*------------------------------------------------*/
		if (image_active_2)
		{
			if (nk_popup_begin(ctx, NK_POPUP_STATIC,
				"Config Popup", 0, nk_rect(340, 50, 320, 220)))
			{
				ui_header(ctx, media, "---- Choose Local/Cluster ----");
				ui_widget_small_button(ctx, media, 30);
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
				/*------------------------------------------------
				 *                  LAUNCH RT
				 *------------------------------------------------*/
				ui_header(ctx, media, "");
				ui_widget_centered(ctx, media, 30);
				if (nk_button_label(ctx, "Launch"))
				{
					rt(world);
					image_active = 0;
					image_active_2 = 0;
					nk_popup_close(ctx);
				}
				nk_popup_close(ctx);
				nk_popup_end(ctx);
			}
		}

	}
	nk_end(ctx);
}
