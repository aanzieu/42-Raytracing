/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:04:32 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/27 16:48:05 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "parse.h"
#include "nuklear.h"
#include "gui.h"
#include "equation.h"

int		ui_widget_value_infos_cam(struct nk_context *ctx, double *value,\
									char *title)
{
	double res;

	res = *value;
	nk_property_double(ctx, title, -100.0f, value, 100.0f, 1, 1);
	return (res == *value ? 0 : 1);
}

int		ui_widget_value_infos(struct nk_context *ctx, struct media *media,\
							double *value, char *title)
{
	double res;

	res = *value;
	nk_style_set_font(ctx, &media->font_14->handle);
	nk_layout_row_dynamic(ctx, 15, 1);
	nk_property_double(ctx, title, -1024.0f, value, 1024.0f, 0.1, 1);
	return (res == *value ? 0 : 1);
}

void	ui_slide_int_0_to_16(struct nk_context *ctx, t_world *w, int step,\
							char *title)
{
	char		*nb;
	static int	press;

	nb = ft_itoa(w->aa);
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	{
		text_float_left(ctx, title, 80);
		text_float_left(ctx, nb, 15);
		ft_strdel(&nb);
		nk_layout_row_push(ctx, 90);
		if (nk_slider_int(ctx, 0, &w->aa, 16, step))
			press = 2;
		if (w->aa == 0)
			w->aa = 1;
		text_float_left(ctx, "16", 15);
	}
	nk_layout_row_end(ctx);
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		press = -1;
		w->redraw = 1;
	}
}

void	ui_slide_float_0_to_1(struct nk_context *ctx, double *value,\
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
		press = -1;
}

void	ui_slide_float_0_to_2(struct nk_context *ctx, double *value,\
									char *title)
{
	float		tmp;
	char		*nb;
	static int	press;

	tmp = (float)*value;
	nb = ft_itoa(round((*value * 100) / 2));
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	{
		text_float_left(ctx, title, 80);
		text_float_left(ctx, nb, 15);
		ft_strdel(&nb);
		nk_layout_row_push(ctx, 90);
		if (nk_slider_float(ctx, 0, &tmp, 2.0f, 0.2f))
			press = 2;
		*value = tmp;
		text_float_left(ctx, "100", 15);
	}
	nk_layout_row_end(ctx);
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
		press = -1;
}
