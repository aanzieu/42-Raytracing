/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:15:52 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/06 17:49:05 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include "parse.h"

/* =================================================================*
 *																	*
 *                    CAMERA CONTROLLER BAR							*
 *																	*
 * =================================================================*/

void camera_control_bar(struct nk_context *ctx, struct media *media, t_world *world)
{
	nk_style_set_font(ctx, &media->font_22->handle);
	if(nk_begin(ctx, "CAMERA BAR", nk_rect((world->screen.width / 2) - 150, world->screen.height - 52, 320, 52), NK_WINDOW_BORDER))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 30, 7);
		{
			nk_layout_row_push(ctx, 80);
			nk_label(ctx, "CAMERA", NK_TEXT_CENTERED);
			//nk_image(ctx, media->play);
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->play))
			{
				cam_rot(&world->camera, -90	, 'y');
				world->redraw = 1;
			}
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->prev))
			{
				move_left(world);
				world->redraw = 1;
			}
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->up))
			{
				move_forward(world);
				world->redraw = 1;
			}
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->down))
			{
				move_backward(world);
				world->redraw = 1;
			}
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->next))
			{
				move_right(world);
				world->redraw = 1;
			}
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->pause))
			{
				cam_rot(&world->camera, 90	, 'y');
				world->redraw = 1;
			}
		}
		nk_layout_row_end(ctx);
	}
	nk_end(ctx);
}