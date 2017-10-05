/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:24:13 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/27 17:07:03 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "parse.h"
#include "nuklear.h"
#include "gui.h"
#include "equation.h"

void	text_float_left(struct nk_context *ctx, char *str, int w)
{
	nk_layout_row_push(ctx, w);
	nk_text(ctx, str, ft_strlen(str), NK_TEXT_LEFT);
}

int		ui_slide_float_intensity(struct nk_context *ctx, double *value,\
									char *title)
{
	float		tmp;
	char		*nb;
	static int	press;

	tmp = (float)*value;
	nb = ft_itoa(round(*value * 100));
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	{
		text_float_left(ctx, title, 80);
		text_float_left(ctx, nb, 15);
		ft_strdel(&nb);
		nk_layout_row_push(ctx, 90);
		if (nk_slider_float(ctx, 0, &tmp, 1.0f, 0.1f))
			press = 2;
		*value = tmp;
		text_float_left(ctx, "100", 15);
	}
	nk_layout_row_end(ctx);
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		press = -1;
		return (1);
	}
	return (0);
}

void	ui_slide_float_perlin(struct nk_context *ctx, t_perlin *p,\
								double *value, char *title)
{
	float		tmp;
	char		*nb;
	static int	press;

	tmp = (float)*value;
	nb = ft_itoa(round(*value * 100));
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	{
		text_float_left(ctx, title, 80);
		text_float_left(ctx, nb, 15);
		ft_strdel(&nb);
		nk_layout_row_push(ctx, 90);
		if (nk_slider_float(ctx, 0, &tmp, 1.0f, 0.1f))
			press = 2;
		*value = tmp;
		text_float_left(ctx, "100", 15);
	}
	nk_layout_row_end(ctx);
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		if (p->is_set == 0 && p->scale > 0)
			p->is_set = 1;
		press = -1;
	}
}
