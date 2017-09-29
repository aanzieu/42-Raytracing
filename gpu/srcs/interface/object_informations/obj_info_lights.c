/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 08:13:23 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/29 12:24:41 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

static void	draw_infos(struct nk_context *ctx, struct media *m, t_world *w,\
						int i)
{
	ui_widget_value_infos(ctx, m, &w->lights[i].pos.x, "POS X:");
	ui_widget_value_infos(ctx, m, &w->lights[i].pos.y, "POS Y:");
	ui_widget_value_infos(ctx, m, &w->lights[i].pos.z, "POS Z:");
	ui_slide_float_0_to_1(ctx, &w->lights[i].intensity_coef, "INTENSITY:");
	draw_apply_button(ctx, m, w);
	draw_light_type(ctx, m, w, &w->lights[i]);
}

static void	draw_delete_button(struct nk_context *ctx, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(ctx, media, 10);
	ui_widget_centered(ctx, media, 20);
	nk_style_set_font(ctx, &media->font_14->handle);
	if (nk_button_image_label(ctx, media->del, "DELETE OBJECT",\
		NK_TEXT_CENTERED))
	{
		remove_light(&world->lights_tmp, &o);
		load_lights(&world->lights, world->lights_tmp,\
						&world->lights_len);
		world->redraw = 1;
	}
}

void		light_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->lights_len)
	{
		if (world->id_save == world->lights[i].id)
		{
			header_info(ctx, media->light, "LIGHT");
			draw_infos(ctx, media, world, i);
			ui_widget_centered(ctx, media, 5);
			ui_header(ctx, media, "---- Colors ----");
			nk_style_set_font(ctx, &media->font_14->handle);
			draw_color_picker(ctx, &world->lights[i].color, world);
			refresh_h_cube(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			if (move_object_without_norm(ctx, &world->lights[i].pos))
				world->redraw = 1;
			break ;
		}
		i++;
	}
}
