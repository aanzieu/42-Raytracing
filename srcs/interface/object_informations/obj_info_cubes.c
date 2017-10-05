/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_cubes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/26 16:30:01 by xpouzenc         ###   ########.fr       */
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
	ui_widget_value_infos(c, m, &w->cubes[i].min.x, "MIN X:");
	ui_widget_value_infos(c, m, &w->cubes[i].min.y, "MIN Y:");
	ui_widget_value_infos(c, m, &w->cubes[i].min.z, "MIN Z:");
	ui_widget_value_infos(c, m, &w->cubes[i].max.x, "MAX X:");
	ui_widget_value_infos(c, m, &w->cubes[i].max.y, "MAX Y:");
	ui_widget_value_infos(c, m, &w->cubes[i].max.z, "MAX Z:");
	ui_slide_float_0_to_1(c, &w->cubes[i].reflection_coef, "REFLECTION:");
	ui_slide_float_0_to_2(c, &w->cubes[i].refraction_coef, "REFRACTION:");
	ui_slide_float_0_to_1(c, &w->cubes[i].transparence_coef, "Transparence:");
	draw_infos_next(c, m, &w->cubes[i].perlin, w);
	draw_apply_button(c, m, w);
	draw_p_presets(c, m, w, &w->cubes[i].perlin);
}

static void	draw_delete_button(struct nk_context *c, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(c, media, 10);
	ui_widget_centered(c, media, 20);
	nk_style_set_font(c, &media->font_14->handle);
	if (nk_button_image_label(c, media->del, "DELETE OBJECT",\
		NK_TEXT_CENTERED))
	{
		remove_cube(&world->cubes_tmp, &o);
		load_cubes(&world->cubes, world->cubes_tmp,\
						&world->cubes_len);
		world->redraw = 1;
	}
}

void		cube_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->cubes_len)
	{
		if (world->id_save == world->cubes[i].id)
		{
			header_info(ctx, media->cube, "CUBE");
			draw_infos(ctx, media, world, i);
			ui_widget_centered(ctx, media, 5);
			ui_header(ctx, media, "---- Colors ----");
			nk_style_set_font(ctx, &media->font_14->handle);
			draw_color_picker(ctx, &world->cubes[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, media, world, &world->cubes[i].chess);
			refresh_cube(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
