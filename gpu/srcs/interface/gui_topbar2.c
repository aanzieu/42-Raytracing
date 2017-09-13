/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_topbar2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 13:18:04 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/12 13:53:25 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../../includes/light.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include "parse.h"

static void	select_local_cluster(struct nk_context *ctx, struct media *media,\
						t_world *world)
{
	static int toggle[2] = {1, 0};

	(void)world;
	// toggle[0] = 1;
	// toggle[1] = 0;
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
		//rajouter mode Cluster
	}
}

static void	select_gpu_cpu(struct nk_context *ctx, struct media *media,\
						t_world *world)
{
	static int toggle[2] = {1, 0};

	// toggle[0] = 1;
	// toggle[1] = 0;
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

static void	select_config(struct nk_context *ctx, struct media *media,\
					t_world *world, int img_active[3])
{
	if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Config Popup", 0,\
		nk_rect(340, 50, 320, 220)))
	{
		select_local_cluster(ctx, media, world);
		select_gpu_cpu(ctx, media, world);
		ui_header(ctx, media, "");
		ui_widget_centered(ctx, media, 30);
		press_launch(ctx, world, img_active);
		nk_popup_close(ctx);
		nk_popup_end(ctx);
	}
}

void		select_scene(struct nk_context *ctx, struct media *media,\
					t_world *world, int img_active[3])
{
	int i;

	if (img_active[0])
	{
		if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Scene Popup", 0,\
			nk_rect(60, 50, 320, 220)))
		{
			i = 1;
			nk_layout_row_static(ctx, 82, 82, 3);
			while (i < 4)
			{
				if (nk_button_image(ctx, media->images[i]))
				{
					img_active[2] = i;
					img_active[1] = !img_active[1];
					nk_popup_close(ctx);
				}
				nk_popup_close(ctx);
				i++;
			}
			nk_popup_end(ctx);
		}
		if (img_active[1])
			select_config(ctx, media, world, img_active);
	}
}
