/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_paraboloids.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/13 17:51:29 by xpouzenc         ###   ########.fr       */
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
	if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].top.x, "POS X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].top.y, "POS Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].top.z, "POS Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].normal.x, "NORMAL X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].normal.y, "NORMAL Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].normal.z, "NORMAL Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].distance, "DISTANCE:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].maxm, "MAXM:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].reflection_coef,\
			"REFLECTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].refraction_coef,\
			"REFRACTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->paraboloids[i].transparence_coef,\
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
		remove_paraboloid(&world->paraboloids_tmp, &o);
		load_paraboloids(&world->paraboloids, world->paraboloids_tmp,\
						&world->paraboloids_len);
		world->redraw = 1;
	}
}

void		paraboloid_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->paraboloids_len)
	{
		if (world->id_save == world->paraboloids[i].id)
		{
			header_info(ctx, media->paraboloid, "PARABOLOID");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->paraboloids[i].color, world);
			refresh_paraboloid(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
