/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:14:19 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/26 16:25:12 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"

int move_camera_render(struct nk_context *ctx, t_world *world)
{
	static int press;

	press = 2;
	if(nk_input_is_key_released(&ctx->input, NK_KEY_W) && press == 2)
	{
		press = -1;	
		move_forward(world);
		return(1);
	}
	if(nk_input_is_key_released(&ctx->input, NK_KEY_S) && press == 2)
	{
		press = -1;
		move_backward(world);
		return(1);
	}
	if(nk_input_is_key_released(&ctx->input, NK_KEY_A) && press == 2)
	{
		press = -1;
		move_left(world);
		return(1);
	}
	
	if(nk_input_is_key_released(&ctx->input, NK_KEY_D) && press == 2)
	{
		press = -1;
		move_right(world);
		return(1);
	}
	return(0);
}

int	key_press(struct nk_context *ctx, t_world *world)
{
	if (ctx->input.keyboard.keys[NK_KEY_L].down)
		world->keys.light_none = 1;
	else if (ctx->input.keyboard.keys[NK_KEY_K].down)
		world->keys.light_none = 0;
	else if (world->id_save == -1 || world->ob_save == '\0')
	{
		if(move_camera_render(ctx, world))
			return(1);
	}
	// else
		return (0);
	return (0);
}
