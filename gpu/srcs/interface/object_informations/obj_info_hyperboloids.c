/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_hyperboloids.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/18 14:21:23 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

static void draw_p_presets_next(struct nk_context *c, t_world *w, int i)
{
	int option;

	option = get_preset_info(w->hyperboloids[i].perlin);
	if (nk_button_symbol_label(c, (option == 2) ?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "MARBLE", NK_TEXT_LEFT))
	{
		option = 2;
		if (w->hyperboloids[i].perlin.is_set == 1)
			w->hyperboloids[i].perlin.is_set = 0;
		w->hyperboloids[i].perlin.pre_set = MARBLE;
		w->hyperboloids[i].perlin.scale = 0.9;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(c, (option == 3) ?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "GLASS", NK_TEXT_LEFT))
	{
		option = 3;
		if (w->hyperboloids[i].perlin.is_set == 1)
			w->hyperboloids[i].perlin.is_set = 0;
		w->hyperboloids[i].perlin.pre_set = GLASS;
	}
}

static void	draw_p_presets(struct nk_context *c, struct media *m,\
	t_world *w, int i)
{
	int option;

	option = get_preset_info(w->hyperboloids[i].perlin);
	ui_header(c, m, "---- Perlin Presets ----");
	ui_widget_special_mode(c, m, 20);
	if (nk_button_symbol_label(c, (option == 0) ?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NONE", NK_TEXT_LEFT))
	{
		option = 0;
		w->hyperboloids[i].perlin.pre_set = 0;
		w->hyperboloids[i].perlin.is_set = 0;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(c, (option == 1) ?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "WOOD", NK_TEXT_LEFT))
	{
		option = 1;
		if (w->hyperboloids[i].perlin.is_set == 1)
			w->hyperboloids[i].perlin.is_set = 0;
		w->hyperboloids[i].perlin.pre_set = WOOD;
		w->hyperboloids[i].perlin.scale = 0.19;
		w->redraw = 1;
	}
	draw_p_presets_next(c, w, i);
}

static void draw_infos_next(struct nk_context *c, struct media *m, t_world *w,\
	int i)
{
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].perlin.scale,\
			"PERLIN NOISE SCALE:"))
	{
		if (w->hyperboloids[i].perlin.is_set == 0 && w->hyperboloids[i].perlin.scale > 0)
			w->hyperboloids[i].perlin.is_set = 1;
		if (w->hyperboloids[i].perlin.scale > 0 && w->hyperboloids[i].perlin.amount > 0)
			w->redraw = 1;
	}
	else if (ui_widget_value_infos(c, m, &w->hyperboloids[i].perlin.amount,\
			"PERLIN NOISE AMOUNT:"))
	{
		if (w->hyperboloids[i].perlin.is_set == 0 && w->hyperboloids[i].perlin.amount > 0)
			w->hyperboloids[i].perlin.is_set = 1;
		if (w->hyperboloids[i].perlin.scale > 0 && w->hyperboloids[i].perlin.amount > 0)
			w->redraw = 1;
	}
}

static void	draw_infos(struct nk_context *c, struct media *m, t_world *w,\
		int i)
{
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].top.x, "POS X:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].top.y, "POS Y:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].top.z, "POS Z:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].normal.x, "NORMAL X:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].normal.y, "NORMAL Y:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].normal.z, "NORMAL Z:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].radius, "RADIUS:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].maxm, "MAXM:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].reflection_coef,\
			"REFLECTION:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].refraction_coef,\
			"REFRACTION:"))
		w->redraw = 1;
	if (ui_widget_value_infos(c, m, &w->hyperboloids[i].transparence_coef,\
			"TRANSPARENCE:"))
			w->redraw = 1;
		else
			draw_infos_next(c, m, w, i);
		draw_p_presets(c, m, w, i);
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
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->hyperboloids[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, world, &world->hyperboloids[i].chess);
			refresh_hyperboloid(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
