/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 13:31:03 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 12:23:19 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

static int		get_light_type(t_light light)
{
	if (light.type == LIGHT_BOX)
		return (1);
	if (light.type == LIGHT_PARALLEL)
		return (2);
	return (0);
}

void	draw_light_type(struct nk_context *c, struct media *m, t_world *w,\
						t_light *light)
{
	int	option;

	option = get_light_type(*light);
	ui_header(c, m, "---- Light Type");
	ui_widget_special_mode(c, m, 20);
	if (nk_button_symbol_label(c, (option == 0) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "POINT", NK_TEXT_LEFT))
	{
		option = 0;
		if (light->type == LIGHT_BOX && light->intensity_coef >= 0.2)
			light->intensity_coef -= 0.2;
		light->type = LIGHT_P;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(c, (option == 1) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "BOX", NK_TEXT_LEFT))
	{
		option = 1;
		if (light->type == LIGHT_P && light->intensity_coef <= 0.8)
			light->intensity_coef += 0.2;
		light->type = LIGHT_BOX;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(c, (option == 2) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "PARALLEL", NK_TEXT_LEFT))
	{
		option = 2;
		light->type = LIGHT_PARALLEL;
		w->redraw = 1;
	}
}
