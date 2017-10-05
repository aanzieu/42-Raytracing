/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 13:31:03 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/05 13:36:47 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

static void	draw_p_presets_next(struct nk_context *c, t_world *w, t_perlin *p)
{
	int	option;

	option = get_preset_info(*p);
	if (nk_button_symbol_label(c, (option == 1) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "WOOD", NK_TEXT_LEFT))
	{
		option = 1;
		if (p->is_set == 1)
			p->is_set = 0;
		p->pre_set = WOOD;
		p->scale = 0.19;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(c, (option == 2) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "MARBLE", NK_TEXT_LEFT))
	{
		option = 2;
		if (p->is_set == 1)
			p->is_set = 0;
		p->pre_set = MARBLE;
		p->scale = 0.9;
		w->redraw = 1;
	}
}

void		draw_p_presets(struct nk_context *c, struct media *m, t_world *w,\
						t_perlin *p)
{
	int	option;

	option = get_preset_info(*p);
	ui_header(c, m, "---- Perlin Presets");
	ui_widget_special_mode(c, m, 20);
	if (nk_button_symbol_label(c, (option == 0) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "NONE", NK_TEXT_LEFT))
	{
		option = 0;
		p->pre_set = 0;
		p->is_set = 0;
		p->scale = 0;
		p->amount = 0;
		w->redraw = 1;
	}
	draw_p_presets_next(c, w, p);
}

void		draw_infos_next(struct nk_context *c, struct media *m, t_perlin *p,\
						t_world *w)
{
	(void)w;
	nk_style_set_font(c, &m->font_14->handle);
	ui_slide_float_perlin(c, p, &p->scale, "PERLIN SCALE:");
	if (p->scale == 0)
		p->is_set = 0;
	if (ui_widget_value_infos(c, m, &p->amount, "PERLIN AMOUNT:"))
	{
		if (p->is_set == 0 && p->amount > 0)
			p->is_set = 1;
	}
}

int			get_preset_info(t_perlin p)
{
	if (p.pre_set == WOOD)
		return (1);
	if (p.pre_set == MARBLE)
		return (2);
	return (0);
}
