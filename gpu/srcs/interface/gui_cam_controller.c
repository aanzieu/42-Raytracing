/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_cam_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:15:52 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/11 17:37:40 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include "parse.h"

static void	set_direction(struct nk_context *ctx, struct media *media,\
								t_world *world)
{
	nk_layout_row_push(ctx, 30);
	if (nk_button_image(ctx, media->a_left))
	{
		move_left(world);
		world->redraw = 1;
	}
	nk_layout_row_push(ctx, 30);
	if (nk_button_image(ctx, media->a_up))
	{
		move_forward(world);
		world->redraw = 1;
	}
	nk_layout_row_push(ctx, 30);
	if (nk_button_image(ctx, media->a_down))
	{
		move_backward(world);
		world->redraw = 1;
	}
	nk_layout_row_push(ctx, 30);
	if (nk_button_image(ctx, media->a_right))
	{
		move_right(world);
		world->redraw = 1;
	}
}

static void	rot_camera(t_world *world, size_t i)
{
	if (i == 1)
		vector_rot_z(&world->camera.right_v, &world->camera.up_v,\
					deg_to_radians(10));
	else if (i == 2)
		vector_rot_z(&world->camera.right_v, &world->camera.up_v,\
					deg_to_radians(-10));
	world->camera.right_v = vector_normalize(world->camera.right_v);
	world->camera.dir_v = vector_normalize(world->camera.dir_v);
	world->camera.up_v = vector_normalize(world->camera.up_v);
	world->redraw = 1;
}

void		camera_control_bar(struct nk_context *ctx, struct media *media,\
								t_world *world)
{
	if (nk_begin(ctx, "CAMERA BAR", nk_rect((world->screen.width / 2) - 150, \
		world->screen.height - 52, 260, 52), NK_WINDOW_BORDER))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 30, 7);
		{
			nk_layout_row_push(ctx, 30);
			nk_image(ctx, media->cam);
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->a_rot_left))
				rot_camera(world, 1);
			set_direction(ctx, media, world);
			nk_layout_row_push(ctx, 30);
			if (nk_button_image(ctx, media->a_rot_right))
				rot_camera(world, 2);
		}
		nk_layout_row_end(ctx);
	}
	nk_end(ctx);
}
