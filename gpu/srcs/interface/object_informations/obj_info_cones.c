/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_cones.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:55:08 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/18 14:04:40 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

static void	draw_infos(struct nk_context *c, struct media *m, t_world *w,\
						int i)
{
	ui_widget_value_infos(c, m, &w->cones[i].pos.x, "POS X:");
	ui_widget_value_infos(c, m, &w->cones[i].pos.y, "POS Y:");
	ui_widget_value_infos(c, m, &w->cones[i].pos.z, "POS Z:");
	ui_widget_value_infos(c, m, &w->cones[i].up.x, "NORMAL X:");
	ui_widget_value_infos(c, m, &w->cones[i].up.z, "NORMAL Z:");
	ui_widget_value_infos(c, m, &w->cones[i].height, "HEIGHT:");
	ui_widget_value_infos(c, m, &w->cones[i].half_angle, "RADIUS:");
	ui_widget_value_infos(c, m, &w->cones[i].reflection_coef, "REFLECTION:");
	ui_widget_value_infos(c, m, &w->cones[i].refraction_coef, "REFRACTION:");
	ui_widget_value_infos(c, m, &w->cones[i].transparence_coef, "TRANSPARENCE:");
	draw_infos_next(c, m, &w->cones[i].perlin, w);
	draw_p_presets(c, m, w, &w->cones[i].perlin);
}

static void	draw_delete_button(struct nk_context *c, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(c, media, 10);
	ui_widget_centered(c, media, 30);
	if (nk_button_image_label(c, media->del, "DELETE OBJECT",\
		NK_TEXT_CENTERED))
	{
		remove_cone(&world->cones_tmp, &o);
		load_cones(&world->cones, world->cones_tmp, &world->cones_len);
		world->redraw = 1;
	}
}

void		cone_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->cones_len)
	{
		if (world->id_save == world->cones[i].id)
		{
			header_info(ctx, media->cone, "CONE");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->cones[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, world, &world->cones[i].chess);
			refresh_cone(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
