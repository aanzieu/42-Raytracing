/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_cylinders.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/18 14:07:38 by xpouzenc         ###   ########.fr       */
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
	ui_widget_value_infos(c, m, &w->cylinders[i].pos.x, "POS X:");
	ui_widget_value_infos(c, m, &w->cylinders[i].pos.y, "POS Y:");
	ui_widget_value_infos(c, m, &w->cylinders[i].pos.z, "POS Z:");
	ui_widget_value_infos(c, m, &w->cylinders[i].up.x, "NORMAL X:");
	ui_widget_value_infos(c, m, &w->cylinders[i].up.y, "NORMAL Y:");
	ui_widget_value_infos(c, m, &w->cylinders[i].up.z, "NORMAL Z:");
	ui_widget_value_infos(c, m, &w->cylinders[i].height, "HEIGHT:");
	ui_widget_value_infos(c, m, &w->cylinders[i].radius, "RADIUS:");
	ui_widget_value_infos(c, m, &w->cylinders[i].reflection_coef, "REFLECTION:");
	ui_widget_value_infos(c, m, &w->cylinders[i].refraction_coef,"REFRACTION:");
	ui_widget_value_infos(c, m, &w->cylinders[i].transparence_coef, "TRANSPARENCE:");
	draw_infos_next(c, m, &w->cylinders[i].perlin, w);
	draw_p_presets(c, m, w, &w->cylinders[i].perlin);
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
		remove_cylinder(&world->cylinders_tmp, &o);
		load_cylinders(&world->cylinders, world->cylinders_tmp,\
						&world->cylinders_len);
		world->redraw = 1;
	}
}

void		cylinder_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->cylinders_len)
	{
		if (world->id_save == world->cylinders[i].id)
		{
			header_info(ctx, media->cylinder, "CYLINDER");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->cylinders[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, world, &world->cylinders[i].chess);
			refresh_cylinder(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
