/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_mobius.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 17:14:02 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/13 17:15:46 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

static void	draw_infos(struct nk_context *ctx, struct media *m, t_world *w,\
						int i)
{
	if (ui_widget_value_infos(ctx, m, &w->mobius[i].pos.x, "POS X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->mobius[i].pos.y, "POS Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->mobius[i].pos.z, "POS Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->mobius[i].radius, "RADIUS:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->mobius[i].reflection_coef,\
			"REFLECTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->mobius[i].refraction_coef,\
			"REFRACTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->mobius[i].transparence_coef,\
			"TRANSPARENCE:"))
		w->redraw = 1;
}

static void	draw_delete_button(struct nk_context *ctx, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(ctx, media, 10);
	ui_widget_centered(ctx, media, 30);
	if (nk_button_image_label(ctx, media->del, "DELETE OBJECT",\
		NK_TEXT_CENTERED))
	{
		remove_mobius(&world->mobius_tmp, &o);
		load_mobius(&world->mobius, world->mobius_tmp,\
						&world->mobius_len);
		world->redraw = 1;
	}
}

void		mobius_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->mobius_len)
	{
		if (world->id_save == world->mobius[i].id)
		{
			header_info(ctx, media->mobius, "MOBIUS");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->mobius[i].color, world);
			refresh_mobius(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
