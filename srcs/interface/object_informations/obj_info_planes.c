/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_planes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:55:08 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/02 11:17:55 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

static void	draw_infos(struct nk_context *c, struct media *m, t_world *w,\
	int i)
{
	ui_widget_value_infos(c, m, &w->planes[i].pos.x, "POS X:");
	ui_widget_value_infos(c, m, &w->planes[i].pos.y, "POS Y:");
	ui_widget_value_infos(c, m, &w->planes[i].pos.z, "POS Z:");
	ui_widget_value_infos(c, m, &w->planes[i].up.x, "NORMAL X:");
	ui_widget_value_infos(c, m, &w->planes[i].up.y, "NORMAL Y:");
	ui_widget_value_infos(c, m, &w->planes[i].up.z, "NORMAL Z:");
	ui_slide_float_0_to_1(c, &w->planes[i].reflection_coef, "REFLECTION:");
	ui_slide_float_0_to_2(c, &w->planes[i].refraction_coef, "REFRACTION:");
	ui_slide_float_0_to_1(c, &w->planes[i].transparence_coef, "Transparence:");
	draw_infos_next(c, m, &w->planes[i].perlin, w);
	draw_apply_button(c, m, w);
	draw_p_presets(c, m, w, &w->planes[i].perlin);
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
		remove_plane(&world->planes_tmp, &o);
		load_planes(&world->planes, world->planes_tmp, &world->planes_len);
		world->redraw = 1;
	}
}

void		plane_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->planes_len)
	{
		if (world->id_save == world->planes[i].id)
		{
			header_info(ctx, media->plane, "PLANE");
			draw_infos(ctx, media, world, i);
			ui_widget_centered(ctx, media, 5);
			ui_header(ctx, media, "---- Colors ----");
			nk_style_set_font(ctx, &media->font_14->handle);
			draw_color_picker(ctx, &world->planes[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, media, world, &world->planes[i].chess);
			refresh_plane(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			if (move_object(ctx, &world->planes[i].pos,
				&world->planes[i].up))
				world->redraw = 1;
			break ;
		}
		i++;
	}
}
