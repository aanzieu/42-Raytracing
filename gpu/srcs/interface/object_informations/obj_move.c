/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:10:12 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 12:18:18 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include "gpu_rt.h"

static int	move_object_next2(struct nk_context *ctx, t_vec3d *normal)
{
	static int	press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_LEFT) && press == 2)
	{
		press = -1;
		rotate(normal, -10, 'y');
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_RIGHT) && press == 2)
	{
		press = -1;
		rotate(normal, 10, 'y');
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_UP) && press == 2)
	{
		press = -1;
		rotate(normal, 10, 'x');
		return (1);
	}
	return (0);
}

static int	move_object_next(struct nk_context *ctx, t_vec3d *pos,\
							t_vec3d *normal)
{
	static int	press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_W) && press == 2)
	{
		press = -1;
		translate(pos, 0, 1, 0);
		translate(normal, 0, 1, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_Q) && press == 2)
	{
		press = -1;
		rotate(normal, -10, 'z');
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_E) && press == 2)
	{
		press = -1;
		rotate(normal, 10, 'z');
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_DOWN) && press == 2)
	{
		press = -1;
		rotate(normal, -10, 'x');
		return (1);
	}
	return (move_object_next2(ctx, normal));
}

int			move_object(struct nk_context *ctx, t_vec3d *pos, t_vec3d *normal)
{
	static int	press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_A) && press == 2)
	{
		press = -1;
		translate(pos, -1, 0, 0);
		translate(normal, -1, 0, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_D) && press == 2)
	{
		press = -1;
		translate(pos, 1, 0, 0);
		translate(normal, 1, 0, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_S) && press == 2)
	{
		press = -1;
		translate(pos, 0, -1, 0);
		translate(normal, 0, -1, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_ADD) && press == 2)
	{
		press = -1;
		translate(pos, 0, 0, 1);
		translate(normal, 0, 0, 1);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_SUB) && press == 2)
	{
		press = -1;
		translate(pos, 0, 0, -1);
		translate(normal, 0, 0, -1);
		return (1);
	}
	return (move_object_next(ctx, pos, normal));
}

int			move_object_without_norm(struct nk_context *ctx, t_vec3d *pos)
{
	static int	press;

	press = 2;
	if (nk_input_is_key_released(&ctx->input, NK_KEY_A) && press == 2)
	{
		press = -1;
		translate(pos, -1, 0, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_D) && press == 2)
	{
		press = -1;
		translate(pos, 1, 0, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_S) && press == 2)
	{
		press = -1;
		translate(pos, 0, -1, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_W) && press == 2)
	{
		press = -1;
		translate(pos, 0, 1, 0);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_ADD) && press == 2)
	{
		press = -1;
		translate(pos, 0, 0, 1);
		return (1);
	}
	if (nk_input_is_key_released(&ctx->input, NK_KEY_SUB) && press == 2)
	{
		press = -1;
		translate(pos, 0, 0, -1);
		return (1);
	}
	return (0);
}
