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
	

	nk_style_set_font(ctx, &media->font_20->handle);
	nk_begin(ctx, "SCENE PARAMETERS", nk_rect(100,100,255,610),
			NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_TITLE|NK_TEXT_CENTERED);

	/*------------------------------------------------
	 *                  MENU SAVE
	 *------------------------------------------------*/
	nk_menubar_begin(ctx);
	{
		/* toolbar */
		nk_layout_row_static(ctx, 40, 40, 3);
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
		nk_button_image(ctx, media->tools);
		nk_button_image(ctx, media->cloud);
		nk_button_image(ctx, media->pen);
	}
	nk_menubar_end(ctx);


	// (void)world;
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
	}
	if (nk_button_image_label(ctx, (toggle1)
	? media->checked: media->unchecked, "Cluster", NK_TEXT_LEFT))
	{
		toggle1 = !toggle1;
		toggle0 = !toggle0;
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
	// ui_header(ctx, media, "RT");
	ui_widget_centered(ctx, media, 35);
	if (nk_button_label(ctx, "Launch"))
		rt(world);
	// if (nk_button_label(ctx, "Master"))
	// 	fprintf(stdout, "rocket!\n");
	// if (nk_button_label(ctx, "Cpu"))
	// 	fprintf(stdout, "rocket!\n");
	// if (nk_button_label(ctx, "Gpu"))
	// 	fprintf(stdout, "rocket!\n");

	// ui_widget(ctx, media, 35);
	// if (nk_button_image_label(ctx, media->rocket, "Styled", NK_TEXT_CENTERED))
	// 	fprintf(stdout, "rocket!\n");

	
	// ui_header(ctx, media, "Repeater");
	// ui_widget(ctx, media, 35);
	// if (nk_button_label(ctx, "Press me"))
	// 	fprintf(stdout, "pressed!\n");

	/*------------------------------------------------
	 *                  SPECIAL MODE
	 *------------------------------------------------*/
	ui_header(ctx, media, "---- Special Mode ----");
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 1)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NONE", NK_TEXT_LEFT))
		option = 1;
	// ui_widget(ctx, media, 35);
	if (nk_button_symbol_label(ctx, (option == 0)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "SEPIA", NK_TEXT_LEFT))
		option = 0;
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 2)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "BAYER", NK_TEXT_LEFT))
		option = 2;
		// ui_widget(ctx, media, 35);
	if (nk_button_symbol_label(ctx, (option == 3)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "8 BITS", NK_TEXT_LEFT))
		option = 3;
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 4)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "PASTEL", NK_TEXT_LEFT))
		option = 4;
		// ui_widget(ctx, media, 35);
	if (nk_button_symbol_label(ctx, (option == 5)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "B&W", NK_TEXT_LEFT))
		option = 5;
	ui_widget_special_mode(ctx, media, 15);
	if (nk_button_symbol_label(ctx, (option == 6)? 
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "CARTOON", NK_TEXT_LEFT))
		option = 6;
		// ui_widget(ctx, media, 35);
	if (nk_button_symbol_label(ctx, (option == 7)?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NEGATIVE", NK_TEXT_LEFT))
		option = 7;
	// ui_widget(ctx, media, 35);
	// if (nk_button_symbol_label(ctx, (option == 2)?
	// NK_SYMBOL_CIRCLE_OUTLINE:NK_SYMBOL_CIRCLE_SOLID, "Select", NK_TEXT_LEFT))
	// 	option = 2;


	/*------------------------------------------------
	 *                  INFORMATIONS
	 *------------------------------------------------*/
	// static char *text[3];
	// static int text_len[3];
	
	// static double ambient;
	// ambient = world->intensity;	
	// static size_t prog = 0;
	
	ui_header(ctx, media, "---- Informations ----");
	// printf("before = %lf\n",world->ambient.intensity);
	if(ui_widget_value_infos(ctx, media, &world->lights[0].intensity_coef, "Ambient"))
		rt(world);
	
	printf("camera  = %lf\n",world->camera.pos.z);
	// nk_style_set_font(ctx, &media->font_18->handle);
	// nk_layout_row_dynamic(ctx, 35, 1);
	// nk_property_double(ctx, "Ambiant", -100.0, &double_len, 100.0, 1.0, 10);
	// nk_style_set_font(ctx, &media->font_18->handle);
	// nk_layout_row(ctx, NK_DYNAMIC, 25, 2, ratio2);
	// nk_spacing(ctx, 0);
	// //nk_layout_row_dynamic(ctx, 35, 2);
	// nk_label(ctx, "Ambiant", NK_TEXT_LEFT);
	// nk_edit_string(ctx, NK_EDIT_READ_ONLY, text[0], &text_len[0], strlen(text[0]), nk_filter_float);
	// ui_widget_bar(ctx, media, 10);
	// nk_progress(ctx, &prog, 100, nk_true);
	//nk_edit_string(ctx, NK_EDIT_FIELD, text[0], &text_len[0], 64, nk_filter_float);	
	// nk_label(ctx, "Hexadecimal:", NK_TEXT_RIGHT);
	// nk_edit_string(ctx, NK_EDIT_FIELD, text[1], &text_len[1], 64, nk_filter_hex);
	// nk_label(ctx, "Binary:", NK_TEXT_RIGHT);
	// nk_edit_string(ctx, NK_EDIT_FIELD, text[2], &text_len[2], 64, nk_filter_binary);
	/*------------------------------------------------
	 *                  CONTEXTUAL
	 *------------------------------------------------*/
	nk_style_set_font(ctx, &media->font_18->handle);
	if (nk_contextual_begin(ctx, NK_WINDOW_NO_SCROLLBAR, nk_vec2(150, 300), nk_window_get_bounds(ctx))) {
		nk_layout_row_dynamic(ctx, 30, 1);
		if (nk_contextual_item_image_label(ctx, media->copy, "Clone", NK_TEXT_RIGHT))
			fprintf(stdout, "pressed clone!\n");
		if (nk_contextual_item_image_label(ctx, media->del, "Delete", NK_TEXT_RIGHT))
			fprintf(stdout, "pressed delete!\n");
		if (nk_contextual_item_image_label(ctx, media->convert, "Convert", NK_TEXT_RIGHT))
			fprintf(stdout, "pressed convert!\n");
		if (nk_contextual_item_image_label(ctx, media->edit, "Edit", NK_TEXT_RIGHT))
			fprintf(stdout, "pressed edit!\n");
		nk_contextual_end(ctx);
	}
	nk_style_set_font(ctx, &media->font_14->handle);
	nk_end(ctx);
}
