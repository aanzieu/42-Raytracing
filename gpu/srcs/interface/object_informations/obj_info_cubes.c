/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_cubes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/13 17:30:01 by xpouzenc         ###   ########.fr       */
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
	if (ui_widget_value_infos(ctx, m, &w->cubes[i].min.x, "MIN X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].min.y, "MIN Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].min.z, "MIN Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].max.x, "MAX X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].max.y, "MAX Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].max.z, "MAX Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].reflection_coef,\
			"REFLECTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].refraction_coef,\
			"REFRACTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->cubes[i].transparence_coef,\
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
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->cubes[i].color, world);
			refresh_cube(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
