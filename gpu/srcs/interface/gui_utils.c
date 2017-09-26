/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:04:32 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/26 16:25:33 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "parse.h"
#include "nuklear.h"
#include "gui.h"
#include "equation.h"

/* ===============================================================
 *
 *                          CUSTOM WIDGET
 *
 * ===============================================================*/

int ui_piemenu(struct nk_context *ctx, struct nk_vec2 pos, float radius,
		struct nk_image *icons, int item_count)
{
	int ret = -1;
	struct nk_rect total_space;
	struct nk_rect bounds;
	int active_item = 0;

	/* pie menu popup */
	struct nk_color border = ctx->style.window.border_color;
	struct nk_style_item background = ctx->style.window.fixed_background;
	ctx->style.window.fixed_background = nk_style_item_hide();
	ctx->style.window.border_color = nk_rgba(0,0,0,0);

	total_space  = nk_window_get_content_region(ctx);
	ctx->style.window.spacing = nk_vec2(0,0);
	ctx->style.window.padding = nk_vec2(0,0);

	if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Add Objects", NK_WINDOW_NO_SCROLLBAR,
				nk_rect(pos.x - total_space.x - radius, pos.y - radius - total_space.y,
					2*radius,2*radius)))
	{
		int i = 0;
		struct nk_command_buffer* out = nk_window_get_canvas(ctx);
		const struct nk_input *in = &ctx->input;

		total_space = nk_window_get_content_region(ctx);
		ctx->style.window.spacing = nk_vec2(4,4);
		ctx->style.window.padding = nk_vec2(8,8);
		nk_layout_row_dynamic(ctx, total_space.h, 1);
		nk_widget(&bounds, ctx);

		/* outer circle */
		nk_fill_circle(out, bounds, nk_rgb(50,50,50));
		{
			/* circle buttons */
			float step = (2 * 3.141592654f) / (float)(MAX(1,item_count));
			float a_min = 0; float a_max = step;

			struct nk_vec2 center = nk_vec2(bounds.x + bounds.w / 2.0f, bounds.y + bounds.h / 2.0f);
			struct nk_vec2 drag = nk_vec2(in->mouse.pos.x - center.x, in->mouse.pos.y - center.y);
			float angle = (float)atan2(drag.y, drag.x);
			if (angle < -0.0f) angle += 2.0f * 3.141592654f;
			active_item = (int)(angle/step);

			for (i = 0; i < item_count; ++i) {
				struct nk_rect content;
				float rx, ry, dx, dy, a;
				nk_fill_arc(out, center.x, center.y, (bounds.w/2.0f),
						a_min, a_max, (active_item == i) ? nk_rgb(45,100,255): nk_rgb(60,60,60));

				/* separator line */
				rx = bounds.w/2.0f; ry = 0;
				dx = rx * (float)cos(a_min) - ry * (float)sin(a_min);
				dy = rx * (float)sin(a_min) + ry * (float)cos(a_min);
				nk_stroke_line(out, center.x, center.y,
						center.x + dx, center.y + dy, 1.0f, nk_rgb(50,50,50));

				/* button content */
				a = a_min + (a_max - a_min)/2.0f;
				rx = bounds.w/2.5f; ry = 0;
				content.w = 30; content.h = 30;
				content.x = center.x + ((rx * (float)cos(a) - ry * (float)sin(a)) - content.w/2.0f);
				content.y = center.y + (rx * (float)sin(a) + ry * (float)cos(a) - content.h/2.0f);
				nk_draw_image(out, content, &icons[i], nk_rgb(255,255,255));
				a_min = a_max; a_max += step;
			}
		}
		{
			/* inner circle */
			struct nk_rect inner;
			inner.x = bounds.x + bounds.w/2 - bounds.w/4;
			inner.y = bounds.y + bounds.h/2 - bounds.h/4;
			inner.w = bounds.w/2; inner.h = bounds.h/2;
			nk_fill_circle(out, inner, nk_rgb(45,45,45));

			/* active icon content */
			bounds.w = inner.w / 2.0f;
			bounds.h = inner.h / 2.0f;
			bounds.x = inner.x + inner.w/2 - bounds.w/2;
			bounds.y = inner.y + inner.h/2 - bounds.h/2;
			nk_draw_image(out, bounds, &icons[active_item], nk_rgb(255,255,255));
		}
		nk_layout_space_end(ctx);
		if (!nk_input_is_mouse_down(&ctx->input, NK_BUTTON_RIGHT)) {
			nk_popup_close(ctx);
			ret = active_item;
		}
	} else ret = -2;
	ctx->style.window.spacing = nk_vec2(4,4);
	ctx->style.window.padding = nk_vec2(8,8);
	nk_popup_end(ctx);

	ctx->style.window.fixed_background = background;
	ctx->style.window.border_color = border;
	return ret;
}

	void
ui_header(struct nk_context *ctx, struct media *media, const char *title)
{
	struct nk_color	color = {255, 123, 0, 255};
	nk_style_set_font(ctx, &media->font_20->handle);
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label_colored(ctx, title, NK_TEXT_LEFT, color);
}

	void
ui_widget(struct nk_context *ctx, struct media *media, float height)
{
	static const float ratio[] = {0.15f, 0.85f};
	nk_style_set_font(ctx, &media->font_20->handle);
	nk_layout_row(ctx, NK_DYNAMIC, height, 2, ratio);
	nk_spacing(ctx, 1);
}

	void
ui_widget_centered(struct nk_context *ctx, struct media *media, float height)
{
	nk_style_set_font(ctx, &media->font_14->handle);
	nk_layout_row_dynamic(ctx, height, 1);
	nk_spacing(ctx, 0);
}

void
ui_widget_small_button(struct nk_context *ctx, struct media *media, float height)
{
	static const float ratio[] = {0.50f, 0.50f};
	nk_style_set_font(ctx, &media->font_18->handle);
	nk_layout_row(ctx, NK_DYNAMIC, height, 2, ratio);
	nk_spacing(ctx, 0);
}
int
ui_widget_value_infos(struct nk_context *ctx, struct media *media, double *value, char *title)
{
	double res = *value;

	nk_style_set_font(ctx, &media->font_14->handle);
	nk_layout_row_dynamic(ctx, 15, 1);
	nk_property_double(ctx, title, -1024.0f, value, 1024.0f, 0.1, 1);
	return(res == *value ? 0 : 1);
}

int
ui_widget_value_infos_cam(struct nk_context *ctx, struct media *media, double *value, char *title)
{
	double res = *value;
	(void)media;
//	nk_style_set_font(ctx, &media->font_14->handle);
//	nk_layout_row_dynamic(ctx, 15, 1);
	nk_property_double(ctx, title, -100.0f, value, 100.0f, 1, 1);
//	nk_spacing(ctx, 0);
	return(res == *value ? 0 : 1);
}

int
ui_widget_value_infos_int(struct nk_context *ctx, struct media *media, int *value, char *title)
{
	int res = *value;

	nk_style_set_font(ctx, &media->font_18->handle);
	nk_layout_row_dynamic(ctx, 15, 1);
	nk_property_int(ctx, title, 1, value, 32, 1, 1);
	nk_spacing(ctx, 0);
	return(res == *value ? 0 : 1);
}
int	ui_slide_int_0_to_16(struct nk_context *ctx, int *value, char *title)
{
	int		step;
	char	*nb;
	static 	int	press;

	step = (*value == 1) ? 1 : 2;
	nb = ft_itoa(*value);
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	{
		nk_layout_row_push(ctx, 80);
		nk_text(ctx, title, ft_strlen(title), NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 15);
		nk_text(ctx, nb, ft_strlen(nb), NK_TEXT_LEFT);
		ft_strdel(&nb);
		nk_layout_row_push(ctx, 90);
		if(nk_slider_int(ctx, 0, value, 16, step))
			press = 2;
		if (*value == 0)
			*value = 1;
		nk_layout_row_push(ctx, 15);
		nk_text(ctx, "16", ft_strlen("16"), NK_TEXT_LEFT);
	}
	nk_layout_row_end(ctx);
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		press = -1;
		return(1);
	}
	return (0);
}

int	ui_slide_float_0_to_1(struct nk_context *ctx, double *value,\
									char *title)
{
	float		tmp;
	char		*nb;
	static int	press;

	tmp = (float)*value;
	nb = ft_itoa(round(*value * 100));
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	{
		nk_layout_row_push(ctx, 80);
		nk_text(ctx, title, ft_strlen(title), NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 15);
		nk_text(ctx, nb, ft_strlen(nb), NK_TEXT_LEFT);
		ft_strdel(&nb);
		nk_layout_row_push(ctx, 90);
		if(nk_slider_float(ctx, 0, &tmp, 1.0f, 0.1f))
			press = 2;
		*value = tmp;
		nk_layout_row_push(ctx, 15);
		nk_text(ctx, "100", ft_strlen("100"), NK_TEXT_LEFT);
	}
	nk_layout_row_end(ctx);
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		press = -1;
		return(1);
	}
	return (0);
}

int	ui_slide_float_0_to_2(struct nk_context *ctx, double *value,\
									char *title)
{
	float		tmp;
	char		*nb;
	static int	press;

	tmp = (float)*value;
	nb = ft_itoa(round((*value * 100) / 2));
	nk_layout_row_begin(ctx, NK_STATIC, 20, 4);
	{
		nk_layout_row_push(ctx, 80);
		nk_text(ctx, title, ft_strlen(title), NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 15);
		nk_text(ctx, nb, ft_strlen(nb), NK_TEXT_LEFT);
		ft_strdel(&nb);
		nk_layout_row_push(ctx, 90);
		if(nk_slider_float(ctx, 0, &tmp, 2.0f, 0.2f))
			press = 2;
		*value = tmp;
		nk_layout_row_push(ctx, 15);
		nk_text(ctx, "100", ft_strlen("100"), NK_TEXT_LEFT);
	}
	nk_layout_row_end(ctx);
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		press = -1;
		return (1);
	}
	return (0);
}

void
ui_widget_special_mode(struct nk_context *ctx, struct media *media, float height)
{
	static const float ratio[] = {0.50f, 0.50f};
	nk_style_set_font(ctx, &media->font_14->handle);
	nk_layout_row(ctx, NK_DYNAMIC, height, 2, ratio);
	nk_spacing(ctx, 0);
}
