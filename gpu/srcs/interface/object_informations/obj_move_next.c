/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 09:14:02 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 09:14:04 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include "gpu_rt.h"

static int		move_object_without_norm2(struct nk_context *ctx, t_vec3d *pos)
{
	static int	press;

	press = 2;
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

int				move_object_without_norm(struct nk_context *ctx, t_vec3d *pos)
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
	return (move_object_without_norm2(ctx, pos));
}
