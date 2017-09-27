/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_effect_button.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 14:37:50 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/27 14:47:55 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include <vectors.h>
#include <gpu_rt.h>

static void	draw_effect_button_3(struct nk_context *ctx, struct media *media,\
							t_world *world, int option)
{
	ui_widget_special_mode(ctx, media, 20);
	if (nk_button_symbol_label(ctx, (option == 6) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "CARTOON", NK_TEXT_LEFT))
	{
		option = 6;
		world->keys.pad_0 = 6;
		world->redraw = 1;
	}
	if (nk_button_symbol_label(ctx, (option == 7) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "NEGATIVE", NK_TEXT_LEFT))
	{
		option = 7;
		world->keys.pad_0 = 7;
		world->redraw = 1;
	}
	ui_widget_special_mode(ctx, media, 20);
	if (nk_button_symbol_label(ctx, (option == 8) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "ANAGLYPH", NK_TEXT_LEFT))
	{
		option = 8;
		world->keys.pad_0 = 8;
		world->redraw = 1;
	}
}

static void	draw_effect_button_2(struct nk_context *ctx, struct media *media,\
							t_world *world, int option)
{
	if (nk_button_symbol_label(ctx, (option == 3) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "8 BITS", NK_TEXT_LEFT))
	{
		option = 3;
		world->keys.pad_0 = 3;
		world->redraw = 1;
	}
	ui_widget_special_mode(ctx, media, 20);
	if (nk_button_symbol_label(ctx, (option == 4) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "PASTEL", NK_TEXT_LEFT))
	{
		option = 4;
		world->keys.pad_0 = 4;
		world->redraw = 1;
	}
	if (nk_button_symbol_label(ctx, (option == 5) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "B&W", NK_TEXT_LEFT))
	{
		option = 5;
		world->keys.pad_0 = 5;
		world->redraw = 1;
	}
}

static void	draw_effect_button_1(struct nk_context *ctx, struct media *media,\
							t_world *world, int option)
{
	if (nk_button_symbol_label(ctx, (option == 1) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "NONE", NK_TEXT_LEFT))
	{
		option = 1;
		world->keys.pad_0 = 0;
		world->redraw = 1;
	}
	if (nk_button_symbol_label(ctx, (option == 0) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "SEPIA", NK_TEXT_LEFT))
	{
		option = 0;
		world->keys.pad_0 = 1;
		world->redraw = 1;
	}
	ui_widget_special_mode(ctx, media, 20);
	if (nk_button_symbol_label(ctx, (option == 2) ? NK_SYMBOL_CIRCLE_SOLID :\
		NK_SYMBOL_CIRCLE_OUTLINE, "BAYER", NK_TEXT_LEFT))
	{
		option = 2;
		world->keys.pad_0 = 2;
		world->redraw = 1;
	}
}

void		scene_effects(struct nk_context *ctx, struct media *media,\
							t_world *world, int option)
{
	ui_header(ctx, media, "---- Render Effects");
	ui_widget_special_mode(ctx, media, 20);
	draw_effect_button_1(ctx, media, world, option);
	draw_effect_button_2(ctx, media, world, option);
	draw_effect_button_3(ctx, media, world, option);
}
