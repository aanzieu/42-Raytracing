/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_cam_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 17:15:52 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/27 14:59:00 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include "parse.h"

static void	rot_camera(t_world *world, size_t i)
{
	if (i == 1)
		vector_rot_y(&world->camera.right_v, &world->camera.dir_v, \
		deg_to_radians(-10));
	else if (i == 2)
		vector_rot_y(&world->camera.right_v, &world->camera.dir_v, \
		deg_to_radians(10));
	world->camera.right_v = vector_normalize(world->camera.right_v);
	world->camera.dir_v = vector_normalize(world->camera.dir_v);
	world->camera.up_v = vector_normalize(world->camera.up_v);
	world->redraw = 1;
}

static void	set_direction_icons(struct nk_context *ctx, struct media *media,\
								t_world *world)
{
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->a_rot_left))
		rot_camera(world, 1);
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->a_up))
		move_up(world);
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->a_rot_right))
		rot_camera(world, 2);
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->zoom_in))
		move_forward(world);
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->a_left))
		move_left(world);
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->a_down))
		move_down(world);
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->a_right))
		move_right(world);
	nk_layout_row_push(ctx, 25);
	if (nk_button_image(ctx, media->zoom_out))
		move_backward(world);
}

static void	add_cam_infos_next(struct nk_context *ctx, struct media *m,\
								t_world *w)
{
	ui_widget_special_mode(ctx, m, 15);
	if (ui_widget_value_infos_cam(ctx, &w->camera.pos.y, "POS Y:"))
	{
		get_camera_axes(&w->camera);
		w->redraw = 1;
	}
	if (ui_widget_value_infos_cam(ctx, &w->camera.look_at.y, "LAT Y:"))
	{
		get_camera_axes(&w->camera);
		w->redraw = 1;
	}
	ui_widget_special_mode(ctx, m, 15);
	if (ui_widget_value_infos_cam(ctx, &w->camera.pos.z, "POS Z:"))
	{
		get_camera_axes(&w->camera);
		w->redraw = 1;
	}
	if (ui_widget_value_infos_cam(ctx, &w->camera.look_at.z, "LAT Z:"))
	{
		get_camera_axes(&w->camera);
		w->redraw = 1;
	}
}

void		camera_control_bar(struct nk_context *ctx, struct media *m,\
								t_world *w)
{
	if (nk_begin(ctx, "CAMERA LEFT", nk_rect((w->screen.width / 2) - 200, \
		w->screen.height - 76, 140, 76), NK_WINDOW_BORDER))
	{
		nk_layout_row_begin(ctx, NK_STATIC, 25, 4);
		set_direction_icons(ctx, m, w);
		nk_layout_row_end(ctx);
	}
	nk_end(ctx);
	if (nk_begin(ctx, "CAMERA RIGHT", nk_rect((w->screen.width / 2) - 60, \
		w->screen.height - 76, 240, 76), NK_WINDOW_BORDER))
	{
		ui_widget_special_mode(ctx, m, 15);
		if (ui_widget_value_infos_cam(ctx, &w->camera.pos.x, "POS X:"))
		{
			get_camera_axes(&w->camera);
			w->redraw = 1;
		}
		if (ui_widget_value_infos_cam(ctx, &w->camera.look_at.x, "LAT X:"))
		{
			get_camera_axes(&w->camera);
			w->redraw = 1;
		}
		add_cam_infos_next(ctx, m, w);
	}
	nk_end(ctx);
}
