/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scene_parameters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:10:35 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 19:53:57 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include <vectors.h>
#include <gpu_rt.h>

static void	scene_ambient(struct nk_context *ctx, struct media *media,\
							t_world *world)
{
	ui_widget_centered(ctx, media, 5);
	ui_header(ctx, media, "---- Ambient Light");
	nk_style_set_font(ctx, &media->font_14->handle);
	if (ui_slide_float_intensity(ctx, &world->ambient.intensity, "Intensity:"))
		world->redraw = 1;
	ui_widget_centered(ctx, media, 30);
	nk_style_set_font(ctx, &media->font_14->handle);
	draw_choose_color(ctx, world, &world->ambient.color);
}

static void	scene_definition(struct nk_context *ctx, struct media *media,\
							t_world *world)
{
	static int hd = 1;

	if (world->keys.light_none == 0)
		hd = 1;
	ui_header(ctx, media, "---- Render Definition");
	ui_widget_special_mode(ctx, media, 20);
	if (nk_button_symbol_label(ctx, (hd == 0) ?\
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "HD", NK_TEXT_LEFT))
	{
		hd = 0;
		world->keys.light_none = 1;
		world->redraw = 1;
	}
	if (nk_button_symbol_label(ctx, (hd == 1) ?\
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "LOW", NK_TEXT_LEFT))
	{
		hd = 1;
		world->keys.light_none = 0;
		world->redraw = 1;
	}
	ui_slide_int_0_to_8(ctx, world, (world->aa == 1) ? 1 : 2, "Anti-Aliasing:");
}

static void	scene_info_header(struct nk_context *ctx, struct media *media,\
							t_world *world)
{
	ui_header(ctx, media, "---- Scene Active");
	nk_style_set_font(ctx, &media->font_18->handle);
	nk_text(ctx, world->title, ft_strlen(world->title), NK_TEXT_LEFT);
	ui_widget_special_mode(ctx, media, 100);
	nk_image(ctx, media->images[world->img_scene]);
	ui_widget_centered(ctx, media, 5);
}

void		scene_parameters(struct nk_context *ctx, struct media *media,\
							t_world *world)
{
	nk_style_set_font(ctx, &media->font_20->handle);
	if (nk_begin(ctx, "Scene parameters", nk_rect(0, 52, 250,\
		world->screen.height - 52), NK_WINDOW_BORDER | NK_WINDOW_TITLE |\
		NK_WINDOW_BACKGROUND))
	{
		scene_info_header(ctx, media, world);
		scene_definition(ctx, media, world);
		scene_effects(ctx, media, world);
		scene_ambient(ctx, media, world);
		scene_parameters_next(ctx, media, world);
	}
	nk_end(ctx);
}
