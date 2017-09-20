/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_triangles.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:58:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/18 14:16:31 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

static void draw_p_presets_next(struct nk_context *ctx, t_world *w, int i)
{
	int option;

	option = get_preset_info(w->triangles[i].perlin);
	if (nk_button_symbol_label(ctx, (option == 2) ?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "MARBLE", NK_TEXT_LEFT))
	{
		option = 2;
		if (w->triangles[i].perlin.is_set == 1)
			w->triangles[i].perlin.is_set = 0;
		w->triangles[i].perlin.pre_set = MARBLE;
		w->triangles[i].perlin.scale = 0.9;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(ctx, (option == 3) ?
	NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "GLASS", NK_TEXT_LEFT))
	{
		option = 3;
		if (w->triangles[i].perlin.is_set == 1)
			w->triangles[i].perlin.is_set = 0;
		w->triangles[i].perlin.pre_set = GLASS;
	}
}

static void	draw_p_presets(struct nk_context *ctx, struct media *m,\
	t_world *w, int i)
{
	int option;

	option = get_preset_info(w->triangles[i].perlin);
	ui_header(ctx, m, "---- Perlin Presets ----");
	ui_widget_special_mode(ctx, m, 20);
	if (nk_button_symbol_label(ctx, (option == 0) ?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "NONE", NK_TEXT_LEFT))
	{
		option = 0;
		w->triangles[i].perlin.pre_set = 0;
		w->triangles[i].perlin.is_set = 0;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(ctx, (option == 1) ?
		NK_SYMBOL_CIRCLE_SOLID:NK_SYMBOL_CIRCLE_OUTLINE, "WOOD", NK_TEXT_LEFT))
	{
		option = 1;
		if (w->triangles[i].perlin.is_set == 1)
			w->triangles[i].perlin.is_set = 0;
		w->triangles[i].perlin.pre_set = WOOD;
		w->triangles[i].perlin.scale = 0.19;
		w->redraw = 1;
	}
	draw_p_presets_next(ctx, w, i);
}

static void	draw_infos_next(struct nk_context *ctx, struct media *m,\
							t_world *w, int i)
{
	if (ui_widget_value_infos(ctx, m, &w->triangles[i].up.x, "NORMAL X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].up.y, "NORMAL Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].up.z, "NORMAL Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].reflection_coef,\
			"REFLECTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].refraction_coef,\
			"REFRACTION:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].transparence_coef,\
			"TRANSPARENCE:"))
		w->redraw = 1;
		else
			draw_infos_next(ctx, m, w, i);
		draw_p_presets(ctx, m, w, i);
}

static void	draw_infos(struct nk_context *ctx, struct media *m, t_world *w,\
						int i)
{
	if (ui_widget_value_infos(ctx, m, &w->triangles[i].pos.x, "POS X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].pos.y, "POS Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].pos.z, "POS Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].v1.x, "SIDE1 X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].v1.y, "SIDE1 Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].v1.z, "SIDE1 Z:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].v2.x, "SIDE2 X:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].v2.y, "SIDE2 Y:"))
		w->redraw = 1;
	else if (ui_widget_value_infos(ctx, m, &w->triangles[i].v2.z, "SIDE2 Z:"))
		w->redraw = 1;
	draw_infos_next(ctx, m, w, i);
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
		remove_triangle(&world->triangles_tmp, &o);
		load_triangles(&world->triangles, world->triangles_tmp,\
						&world->triangles_len);
		world->redraw = 1;
	}
}

void		triangle_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->triangles_len)
	{
		if (world->id_save == world->triangles[i].id)
		{
			header_info(ctx, media->triangle, "TRIANGLE");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->triangles[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, world, &world->triangles[i].chess);
			refresh_triangle(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}
