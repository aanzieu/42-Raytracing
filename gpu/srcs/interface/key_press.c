/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:14:19 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/02 11:15:37 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"

static int			move_camera_render3(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_UP)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		cam_rot(&world->camera, -40, 'x');
		world->redraw = 1;
		return (press = 1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_DOWN)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		cam_rot(&world->camera, 40, 'x');
		world->redraw = 1;
		return (press = 1);
	}
	return (0);
}

static int			move_camera_render2(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_A)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		translate(&world->camera.pos, -1, 0, 0);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return (press = 1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_D)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		translate(&world->camera.pos, 1, 0, 0);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return (press = 1);
	}
	return (move_camera_render3(ctx, world));
}

int					move_camera_render(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_W)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		translate(&world->camera.pos, 0, 0, 1);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return (press = 1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_S)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		translate(&world->camera.pos, 0, 0, -1);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return (press = 1);
	}
	return (move_camera_render2(ctx, world));
}

int					key_press(struct nk_context *ctx, t_world *world)
{
	if (ctx->input.keyboard.keys[NK_KEY_L].down)
		world->keys.light_none = 1;
	else if (ctx->input.keyboard.keys[NK_KEY_K].down)
		world->keys.light_none = 0;
	else if (world->id_save == -1 || world->ob_save == '\0')
	{
		if (move_camera_render(ctx, world)
			|| move_camera_render_next(ctx, world))
			return (1);
	}
	return (0);
}
