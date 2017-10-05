/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_topbar3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 17:15:18 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/03 12:57:37 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "light.h"
#include "nuklear.h"
#include "gui.h"
#include "parse.h"

static void	select_local_cluster(struct nk_context *ctx, struct media *media,\
						t_world *world)
{
	static int toggle[2] = {1, 0};

	(void)world;
	ui_header(ctx, media, "---- Choose Local/Cluster ----");
	ui_widget_small_button(ctx, media, 30);
	if (nk_button_image_label(ctx, (toggle[0])
	? media->checked : media->unchecked, "Local", NK_TEXT_LEFT))
	{
		toggle[0] = !toggle[0];
		toggle[1] = !toggle[1];
		world->mode_cluster = 0;
	}
	if (nk_button_image_label(ctx, (toggle[1])
	? media->checked : media->unchecked, "Cluster", NK_TEXT_LEFT))
	{
		toggle[1] = !toggle[1];
		toggle[0] = !toggle[0];
		world->mode_cluster = 1;
	}
}

static void	select_gpu_cpu(struct nk_context *ctx, struct media *media,\
						t_world *world)
{
	static int toggle[2] = {1, 0};

	ui_header(ctx, media, "---- Choose CPU/GPU ----");
	ui_widget_small_button(ctx, media, 30);
	if (nk_button_image_label(ctx, (toggle[0])
	? media->checked : media->unchecked, "Cpu", NK_TEXT_LEFT))
	{
		toggle[0] = !toggle[0];
		toggle[1] = !toggle[1];
		world->mode = 0;
	}
	if (nk_button_image_label(ctx, (toggle[1])
	? media->checked : media->unchecked, "Gpu", NK_TEXT_LEFT))
	{
		toggle[1] = !toggle[1];
		toggle[0] = !toggle[0];
		world->mode = 1;
	}
}

static int	select_config(struct nk_context *ctx, struct media *media,\
					t_world *world, char *text)
{
	if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Config Popup", 0,\
		nk_rect(340, 52, 280, 280)))
	{
		select_local_cluster(ctx, media, world);
		select_gpu_cpu(ctx, media, world);
		ui_header(ctx, media, "");
		ui_widget_centered(ctx, media, 30);
		nk_style_set_font(ctx, &media->font_18->handle);
		if (launch_xml_file(ctx, world, text))
			return (1);
		nk_popup_close(ctx);
		nk_popup_end(ctx);
	}
	return (0);
}

static void	draw_popup_scene(struct nk_context *ctx, struct media *media,\
								int img_active[5], char *text)
{
	if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Scene Popup", 0,\
		nk_rect(60, 52, 280, 280)))
	{
		nk_layout_row_dynamic(ctx, 30, 1);
		nk_label(ctx, "Enter a valid xml file,", NK_TEXT_CENTERED);
		nk_label(ctx, "(it must be into 'testfiles' folder)", NK_TEXT_CENTERED);
		nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, text, 100,\
		nk_filter_default);
		nk_style_set_font(ctx, &media->font_14->handle);
		if (nk_button_label(ctx, "SUBMIT"))
		{
			img_active[1] = !img_active[1];
			nk_popup_close(ctx);
		}
		nk_popup_close(ctx);
		nk_popup_end(ctx);
	}
}

void		select_your_file(struct nk_context *ctx, struct media *media,\
					t_world *world, int img_active[5])
{
	static char text[100];

	if (img_active[4])
	{
		if (nk_input_is_mouse_hovering_rect(&ctx->input,\
			nk_rect(60, 40, 570, 292)))
		{
			draw_popup_scene(ctx, media, img_active, text);
			if (img_active[1])
			{
				if (select_config(ctx, media, world, text))
				{
					img_active[4] = 0;
					img_active[1] = 0;
				}
			}
		}
		else
		{
			img_active[4] = 0;
			img_active[1] = 0;
		}
	}
	nk_popup_end(ctx);
}
