/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:04:32 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/27 15:25:25 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "parse.h"
#include "nuklear.h"
#include "gui.h"
#include "equation.h"

void	ui_header(struct nk_context *ctx, struct media *media, const char *str)
{
	struct nk_color	color;

	color = (struct nk_color){255, 123, 0, 255};
	nk_style_set_font(ctx, &media->font_20->handle);
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label_colored(ctx, str, NK_TEXT_LEFT, color);
}

void	ui_widget(struct nk_context *ctx, struct media *media, float height)
{
	static const float	ratio[] = {0.15f, 0.85f};

	nk_style_set_font(ctx, &media->font_20->handle);
	nk_layout_row(ctx, NK_DYNAMIC, height, 2, ratio);
	nk_spacing(ctx, 1);
}

void	ui_widget_centered(struct nk_context *ctx, struct media *m, float h)
{
	nk_style_set_font(ctx, &m->font_14->handle);
	nk_layout_row_dynamic(ctx, h, 1);
	nk_spacing(ctx, 0);
}

void	ui_widget_small_button(struct nk_context *ctx, struct media *m, float h)
{
	static const float	ratio[] = {0.50f, 0.50f};

	nk_style_set_font(ctx, &m->font_18->handle);
	nk_layout_row(ctx, NK_DYNAMIC, h, 2, ratio);
	nk_spacing(ctx, 0);
}

void	ui_widget_special_mode(struct nk_context *ctx, struct media *m, float h)
{
	static const float	ratio[] = {0.50f, 0.50f};

	nk_style_set_font(ctx, &m->font_14->handle);
	nk_layout_row(ctx, NK_DYNAMIC, h, 2, ratio);
	nk_spacing(ctx, 0);
}
