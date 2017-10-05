/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 09:39:05 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/04 14:45:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"

static int		move_camera_render_next5(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (ctx->input.keyboard.keys[NK_KEY_CTRL].down)
	{
		if (nk_input_is_key_released(&ctx->input, NK_KEY_W)
				&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			cam_rot(&world->camera, -90, 'x');
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_S)
				&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			cam_rot(&world->camera, 90, 'x');
			return (press = 1);
		}
	}
	return (0);
}

static int		move_camera_render_next4(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (ctx->input.keyboard.keys[NK_KEY_CTRL].down)
	{
		if (nk_input_is_key_released(&ctx->input, NK_KEY_Q)
				&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			vector_rot_z(&world->camera.right_v, &world->camera.up_v,
					deg_to_radians(-10));
			get_camera_axes(&world->camera);
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_E)
				&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			vector_rot_z(&world->camera.right_v, &world->camera.up_v, \
			deg_to_radians(10));
			get_camera_axes(&world->camera);
			return (press = 1);
		}
	}
	return (move_camera_render_next5(ctx, world));
}

static int		move_camera_render_next3(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (ctx->input.keyboard.keys[NK_KEY_CTRL].down)
	{
		if (nk_input_is_key_released(&ctx->input, NK_KEY_A)
				&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			press = -1;
			cam_rot(&world->camera, -90, 'y');
			return (1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_D)
				&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			press = -1;
			cam_rot(&world->camera, 90, 'y');
			return (1);
		}
	}
	return (move_camera_render_next4(ctx, world));
}

static int		move_camera_render_next2(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if (nk_input_is_key_released(&ctx->input, NK_KEY_W)
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			move_forward(world);
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_S)
				&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			move_backward(world);
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_A)
				&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			move_left(world);
			return (press = 1);
		}
	}
	return (move_camera_render_next3(ctx, world));
}

int				move_camera_render_next(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if (ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if (nk_input_is_key_released(&ctx->input, NK_KEY_D)
				&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			move_right(world);
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_UP)
				&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			move_up(world);
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_DOWN)
				&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			move_down(world);
			return (press = 1);
		}
	}
	return (move_camera_render_next2(ctx, world));
}
