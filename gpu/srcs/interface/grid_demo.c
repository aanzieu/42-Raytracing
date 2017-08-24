/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_demo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:03:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 21:10:56 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

/* ===============================================================
 *
 *                          GRID_DEMO
 *
 * ===============================================================*/

void	grid_demo(struct nk_context *ctx, struct media *media)
{
	static char text[3][64];
	static int text_len[3];
	static const char *items[] = {"Item 0","item 1","item 2"};
	static int selected_item = 0;
	static int check = 1;

	int i;
	nk_style_set_font(ctx, &media->font_20->handle);
	if (nk_begin(ctx, "Grid Demo", nk_rect(600, 350, 275, 250),
				NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|
				NK_WINDOW_NO_SCROLLBAR))
	{
		nk_style_set_font(ctx, &media->font_18->handle);
		nk_layout_row_dynamic(ctx, 30, 2);
		nk_label(ctx, "Floating point:", NK_TEXT_RIGHT);
		nk_edit_string(ctx, NK_EDIT_FIELD, text[0], &text_len[0], 64, nk_filter_float);
		nk_label(ctx, "Hexadecimal:", NK_TEXT_RIGHT);
		nk_edit_string(ctx, NK_EDIT_FIELD, text[1], &text_len[1], 64, nk_filter_hex);
		nk_label(ctx, "Binary:", NK_TEXT_RIGHT);
		nk_edit_string(ctx, NK_EDIT_FIELD, text[2], &text_len[2], 64, nk_filter_binary);
		nk_label(ctx, "Checkbox:", NK_TEXT_RIGHT);
		nk_checkbox_label(ctx, "Check me", &check);
		nk_label(ctx, "Combobox:", NK_TEXT_RIGHT);
		if (nk_combo_begin_label(ctx, items[selected_item], nk_vec2(nk_widget_width(ctx), 200))) {
			nk_layout_row_dynamic(ctx, 25, 1);
			for (i = 0; i < 3; ++i)
				if (nk_combo_item_label(ctx, items[i], NK_TEXT_LEFT))
					selected_item = i;
			nk_combo_end(ctx);
		}
	}
	nk_end(ctx);
	nk_style_set_font(ctx, &media->font_14->handle);
}
