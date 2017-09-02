/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_demo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:10:35 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 21:31:25 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

/* ===============================================================
 *
 *                         SCENE_PARAMETERS
 *
 * ===============================================================*/

	void
scene_parameters(struct nk_context *ctx, struct media *media, t_world *world)
{
	static int option = 1;
	static int toggle0 = 1;
	static int toggle1 = 0;
	static int toggle2 = 1;
	static int toggle3 = 0;
	static int image_active;
	int i = 0;
	static int selected_image = 3;

	
	
	nk_style_set_font(ctx, &media->font_20->handle);
	if(nk_begin(ctx, "SCENE PARAMETERS", nk_rect(0,0,250,610),
			NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_TITLE))
	{
		ui_header(ctx, media, "---- Open & Save ----");
		nk_layout_row_static(ctx, 50, 50, 2);
		if (nk_button_image_label(ctx, media->dir,
			"Images", NK_TEXT_LEFT))
			image_active = !image_active;
	/*------------------------------------------------
	 *                  MENU SAVE
	 *------------------------------------------------*/
		if (nk_menu_begin_image(ctx, "Open", media->play, nk_vec2(110,120)))
		{
			/* settings */
			nk_layout_row_dynamic(ctx, 15, 1);
			if(nk_menu_item_image_label(ctx, media->play,
				".xml", NK_TEXT_RIGHT))
				save_xml_scene(world);
			if(nk_menu_item_image_label(ctx, media->stop,
				".bmp", NK_TEXT_RIGHT))
				savebmp(world);
			// nk_menu_item_image_label(ctx, media->pause, "Pause", NK_TEXT_RIGHT);
			// nk_menu_item_image_label(ctx, media->next, "Next", NK_TEXT_RIGHT);
			// nk_menu_item_image_label(ctx, media->prev, "Prev", NK_TEXT_RIGHT);
			nk_menu_end(ctx);
		}
	// /*------------------------------------------------
	//  *                  SELECTED IMAGE
	//  *------------------------------------------------*/
		ui_header(ctx, media, "---- File Active ----");
		ui_widget_centered(ctx, media, 100);
		nk_image(ctx, media->images[selected_image]);
		if (image_active)
		{
			if (nk_popup_begin(ctx, NK_POPUP_STATIC,
				"Image Popup", 0, nk_rect(265, 0, 320, 220)))
			{
				nk_layout_row_static(ctx, 82, 82, 3);
				for (i = 0; i < 9; ++i)
				{
					if (nk_button_image(ctx, media->images[i]))
					{
						selected_image = i;
						image_active = 0;
						nk_popup_close(ctx);
					}
					nk_popup_close(ctx);
				}
				nk_popup_end(ctx);
			}
		}
	
	
		/* toolbar */
		// ui_header(ctx, media, "---- Save ----");
		// nk_layout_row_static(ctx, 50, 50, 2);
		// if (nk_menu_begin_image(ctx, "Music", media->play, nk_vec2(110,120)))
		// {
		// 	/* settings */
		// 	nk_layout_row_dynamic(ctx, 25, 1);
		// 	nk_menu_item_image_label(ctx, media->play, "Play", NK_TEXT_RIGHT);
		// 	nk_menu_item_image_label(ctx, media->stop, "Stop", NK_TEXT_RIGHT);
		// 	nk_menu_item_image_label(ctx, media->pause, "Pause", NK_TEXT_RIGHT);
		// 	nk_menu_item_image_label(ctx, media->next, "Next", NK_TEXT_RIGHT);
		// 	nk_menu_item_image_label(ctx, media->prev, "Prev", NK_TEXT_RIGHT);
		// 	nk_menu_end(ctx);
		// }


	/*------------------------------------------------
	 *                  BUTTON MODE
	 *------------------------------------------------*/

	ui_header(ctx, media, "---- Choose mode ----");
	ui_widget_small_button(ctx, media, 30);
	if (nk_button_image_label(ctx, (toggle0) 
	? media->checked: media->unchecked, "Local", NK_TEXT_LEFT))
	{
		toggle0 = !toggle0;
		toggle1 = !toggle1;
		//rajouter mode Local
	}
	if (nk_button_image_label(ctx, (toggle1)
	? media->checked: media->unchecked, "Cluster", NK_TEXT_LEFT))
	{
		toggle1 = !toggle1;
		toggle0 = !toggle0;
		//rajouter mode Cluster
	}
	ui_widget_small_button(ctx, media, 30);
	if (nk_button_image_label(ctx, (toggle2) 
	? media->checked: media->unchecked, "Cpu", NK_TEXT_LEFT))
	{
		toggle2 = !toggle2;
		toggle3 = !toggle3;
		world->mode = 0;
	}
	if (nk_button_image_label(ctx, (toggle3)
	? media->checked: media->unchecked, "Gpu", NK_TEXT_LEFT))
	{
		toggle3 = !toggle3;
		toggle2 = !toggle2;
		world->mode = 1;
	}
	/*------------------------------------------------
	 *                  LAUNCH RT
	 *------------------------------------------------*/
	ui_widget_centered(ctx, media, 25);
	if (nk_button_label(ctx, "Launch"))
		rt(world);

	/*------------------------------------------------
	 *                  SPECIAL MODE
	 *------------------------------------------------*/
	ui_header(ctx, media, "---- Special Mode ----");
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 1)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NONE", NK_TEXT_LEFT))
		option = 1;
	if (nk_button_symbol_label(ctx, (option == 0)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "SEPIA", NK_TEXT_LEFT))
		option = 0;
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 2)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "BAYER", NK_TEXT_LEFT))
		option = 2;
	if (nk_button_symbol_label(ctx, (option == 3)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "8 BITS", NK_TEXT_LEFT))
		option = 3;
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 4)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "PASTEL", NK_TEXT_LEFT))
		option = 4;
	if (nk_button_symbol_label(ctx, (option == 5)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "B&W", NK_TEXT_LEFT))
		option = 5;
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 6)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "CARTOON", NK_TEXT_LEFT))
		option = 6;
	if (nk_button_symbol_label(ctx, (option == 7)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NEGATIVE", NK_TEXT_LEFT))
		option = 7;

	/*------------------------------------------------
	 *                  INFORMATIONS
	 *------------------------------------------------*/
	
	ui_header(ctx, media, "---- Informations ----");
	if(ui_widget_value_infos(ctx, media, &world->ambient.intensity, "Ambient"))
		world->redraw = 1;

	/*------------------------------------------------
	 *                  COLOR TABLES
	 *------------------------------------------------*/

	// static struct	nk_color color = {255, 123, 0, 255};
	// nk_layout_row_dynamic(ctx, 100, 1);
	// nk_color_pick(ctx, &color, NK_RGBA);
	
	// /*------------------------------------------------
	//  *                  CONTEXTUAL
	//  *------------------------------------------------*/
	// nk_style_set_font(ctx, &media->font_18->handle);
	// if (nk_contextual_begin(ctx, NK_WINDOW_NO_SCROLLBAR, nk_vec2(150, 300), nk_window_get_bounds(ctx))) {
	// 	nk_layout_row_dynamic(ctx, 30, 1);
	// 	if (nk_contextual_item_image_label(ctx, media->copy, "Clone", NK_TEXT_RIGHT))
	// 		fprintf(stdout, "pressed clone!\n");
	// 	if (nk_contextual_item_image_label(ctx, media->del, "Delete", NK_TEXT_RIGHT))
	// 		fprintf(stdout, "pressed delete!\n");
	// 	if (nk_contextual_item_image_label(ctx, media->convert, "Convert", NK_TEXT_RIGHT))
	// 		fprintf(stdout, "pressed convert!\n");
	// 	if (nk_contextual_item_image_label(ctx, media->edit, "Edit", NK_TEXT_RIGHT))
	// 		fprintf(stdout, "pressed edit!\n");
	// 	nk_contextual_end(ctx);
	// }
	


	nk_style_set_font(ctx, &media->font_14->handle);
	nk_end(ctx);
			}
}
