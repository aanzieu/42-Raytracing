/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:10:12 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/02 11:16:53 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include "gpu_rt.h"

static int	move_object_next3(struct nk_context *ctx, t_vec3d *normal)
{
	static int	press;

	press = 2;
	if (ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if (nk_input_is_key_released(&ctx->input, NK_KEY_Q) && press == 2)
		{
			rotate(normal, -20, 'z');
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_E) && press == 2)
		{
			rotate(normal, 20, 'z');
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_S) && press == 2)
		{
			rotate(normal, -20, 'x');
			return (press = 1);
		}
	}
	return (0);
}

static int	move_object_next2(struct nk_context *ctx, t_vec3d *normal)
{
	static int	press;

	press = 2;
	if (ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if (nk_input_is_key_released(&ctx->input, NK_KEY_A) && press == 2)
		{
			rotate(normal, -20, 'y');
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_D) && press == 2)
		{
			rotate(normal, 20, 'y');
			return (press = 1);
		}
		if (nk_input_is_key_released(&ctx->input, NK_KEY_W) && press == 2)
		{
			rotate(normal, 20, 'x');
			return (press = 1);
		}
	}
	return (move_object_next3(ctx, normal));
}

static int	move_object_next(struct nk_context *ctx, t_vec3d *pos,\
							t_vec3d *normal)
{
	static int	press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_A)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
	{
		translate(pos, -1, 0, 0);
		return (press = 1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_D)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
	{
		translate(pos, 1, 0, 0);
		return (press = 1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_S)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
	{
		translate(pos, 0, -1, 0);
		return (press = 1);
	}
	return (move_object_next2(ctx, normal));
}

int			move_object(struct nk_context *ctx, t_vec3d *pos, t_vec3d *normal)
{
	static int	press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_ADD)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
	{
		translate(pos, 0, 0, 1);
		return (press = 1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_SUB)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
	{
		translate(pos, 0, 0, -1);
		return (press = 1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_W)
	&& !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
	{
		translate(pos, 0, 1, 0);
		return (press = 1);
	}
	return (move_object_next(ctx, pos, normal));
}
