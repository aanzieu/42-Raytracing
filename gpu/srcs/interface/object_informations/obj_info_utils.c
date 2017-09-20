/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 13:31:03 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/19 17:44:06 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

int	draw_color_picker(struct nk_context *ctx, t_color *o, t_world *world)
{
	static struct nk_color	color;
	static const double		s = 1.0 / 255.0;
	static int				press ;

	nk_layout_row_dynamic(ctx, 125, 1);
	color.r = o->r / s;
	color.g = o->g / s;
	color.b = o->b / s;
	if (nk_color_pick(ctx, &color, NK_RGB))
	{
		o->r = (double)color.r * s;
		o->g = (double)color.g * s;
		o->b = (double)color.b * s;
		press = 2;
	}
	if(nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
	{
		press = -1;
		world->redraw = 1;
		return(1);
	}
	return(0);
}

void	header_info(struct nk_context *ctx, struct nk_image img, char *n)
{
	nk_layout_row_begin(ctx, NK_STATIC, 60, 2);
	{
		nk_layout_row_push(ctx, 60);
		nk_image(ctx, img);
		nk_layout_row_push(ctx, 150);
		nk_text(ctx, n, ft_strlen(n), NK_TEXT_LEFT);
	}
	nk_layout_row_end(ctx);
}

void	draw_chess_color(struct nk_context *ctx, t_world *world, t_color *c)
{
	static int check = 1;

	if (c->r != -1)
		check = 0;
	else
		check = 1;
	if (nk_checkbox_label(ctx, "ADD CHESS COLOR", &check))
		world->redraw = 1;
	if (!check)
	{
		if (c->r == -1)
		{
			c->r = 0;
			c->g = 0;
			c->b = 0;
		}
		draw_color_picker(ctx, c, world);
	}
	else
	{
		c->r = -1;
		c->g = -1;
		c->b = -1;
	}
}

void	draw_choose_color(struct nk_context *ctx, t_world *world, t_color *c)
{
	static int check = 1;

	if (nk_checkbox_label(ctx, "CHOOSE COLOR", &check))
		world->redraw = 0;
	if (!check)
		draw_color_picker(ctx, c, world);
}
