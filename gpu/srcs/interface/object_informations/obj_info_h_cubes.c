/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_h_cubes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 08:13:23 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/20 08:13:26 by aanzieu          ###   ########.fr       */
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
	if (ui_widget_value_infos(ctx, m, &w->h_cubes[i].pos.x, "POS X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->h_cubes[i].pos.y, "POS Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->h_cubes[i].pos.z, "POS Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->h_cubes[i].reflection_coef,\
			"REFLECTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->h_cubes[i].refraction_coef,\
			"REFRACTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->h_cubes[i].transparence_coef,\
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
		remove_h_cube(&world->h_cubes_tmp, &o);
		load_h_cubes(&world->h_cubes, world->h_cubes_tmp,\
						&world->h_cubes_len);
		world->redraw = 1;
	}
}

void		h_cube_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->h_cubes_len)
	{
		if (world->id_save == world->h_cubes[i].id)
		{
			header_info(ctx, media->h_cube, "HOLLOW CUBE");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->h_cubes[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, world, &world->h_cubes[i].chess);
			refresh_h_cube(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
