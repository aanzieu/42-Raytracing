/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_hyperboloids.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/21 18:29:15 by xpouzenc         ###   ########.fr       */
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
	ui_widget_value_infos(c, m, &w->hyperboloids[i].top.x, "POS X:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].top.y, "POS Y:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].top.z, "POS Z:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].normal.x, "NORMAL X:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].normal.y, "NORMAL Y:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].normal.z, "NORMAL Z:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].radius, "RADIUS:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].maxm, "MAXM:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].reflection_coef,\
						"REFLECTION:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].refraction_coef,\
						"REFRACTION:");
	ui_widget_value_infos(c, m, &w->hyperboloids[i].transparence_coef,\
						"TRANSPARENCE:");
	draw_infos_next(c, m, &w->hyperboloids[i].perlin, w);
	draw_apply_button(c, m, w);
	draw_p_presets(c, m, w, &w->hyperboloids[i].perlin);
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
		remove_hyperboloid(&world->hyperboloids_tmp, &o);
		load_hyperboloids(&world->hyperboloids, world->hyperboloids_tmp,\
						&world->hyperboloids_len);
		world->redraw = 1;
	}
}

void		hyperboloid_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->hyperboloids_len)
	{
		if (world->id_save == world->hyperboloids[i].id)
		{
			header_info(ctx, media->hyperboloid, "HYPERBOLOID");
			draw_infos(ctx, media, world, i);
			ui_widget_centered(ctx, media, 5);
			ui_header(ctx, media, "---- Colors ----");
			nk_style_set_font(ctx, &media->font_14->handle);
			draw_color_picker(ctx, &world->hyperboloids[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, media, world, &world->hyperboloids[i].chess);
			refresh_hyperboloid(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
