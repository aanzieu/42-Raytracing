/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_cones.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:55:08 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/25 17:06:13 by PZC              ###   ########.fr       */
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
	ui_slide_float_0_to_1(c, &w->cones[i].reflection_coef, "REFLECTION:");
	ui_slide_float_0_to_2(c, &w->cones[i].refraction_coef, "REFRACTION:");
	ui_slide_float_0_to_1(c, &w->cones[i].transparence_coef, "Transparence:");
	draw_infos_next(c, m, &w->cones[i].perlin, w);
	draw_apply_button(c, m, w);
	draw_p_presets(c, m, w, &w->cones[i].perlin);
}

static void	draw_delete_button(struct nk_context *c, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(c, media, 10);
	ui_widget_centered(c, media, 20);
	nk_style_set_font(c, &media->font_14->handle);
	if (nk_button_image_label(c, media->del, "DELETE OBJECT", NK_TEXT_CENTERED))
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
			ui_widget_centered(ctx, media, 5);
			ui_header(ctx, media, "---- Colors ----");
			nk_style_set_font(ctx, &media->font_14->handle);
			draw_color_picker(ctx, &world->cones[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, media, world, &world->cones[i].chess);
			refresh_cone(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
