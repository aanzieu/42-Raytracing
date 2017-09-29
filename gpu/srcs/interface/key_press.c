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
	if(nk_input_is_key_released(&ctx->input, NK_KEY_W) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		press = -1;	
		translate(&world->camera.pos, 0, 0, 1);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return(1);
	}
	if(nk_input_is_key_released(&ctx->input, NK_KEY_S) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		press = -1;
		translate(&world->camera.pos, 0, 0, -1);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return(1);
	}
	if(nk_input_is_key_released(&ctx->input, NK_KEY_A) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		press = -1;
		translate(&world->camera.pos, -1, 0, 0);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return(1);
	}
	if(nk_input_is_key_released(&ctx->input, NK_KEY_D) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		press = -1;
		translate(&world->camera.pos, 1, 0, 0);
		world->redraw = 1;
		get_camera_axes(&world->camera);
		return(1);
	}
	if(nk_input_is_key_released(&ctx->input, NK_KEY_UP) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		press = -1;
		cam_rot(&world->camera, -40, 'x');
		world->redraw = 1;
		return(1);
	}
	if(nk_input_is_key_released(&ctx->input, NK_KEY_DOWN) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down
		&& !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
	{
		press = -1;
		cam_rot(&world->camera, 40, 'x');
		world->redraw = 1;
		return(1);
	}
	
	if(ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_W) && !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			press = -1;
			move_forward(world);
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_S) && !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			press = -1;
			move_backward(world);
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_A) && !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			press = -1;
			move_left(world);
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_D) && !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			press = -1;
			move_right(world);
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_UP) && !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			press = -1;
			move_up(world);
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_SHIFT].down)
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_DOWN) && !ctx->input.keyboard.keys[NK_KEY_CTRL].down && press == 2)
		{
			press = -1;
			move_down(world);
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_CTRL].down )
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_A) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			press = -1;
			cam_rot(&world->camera, -90, 'y');
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_CTRL].down )
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_D) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			press = -1;
			cam_rot(&world->camera, 90, 'y');
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_CTRL].down )
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_Q) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			press = -1;
			vector_rot_z(&world->camera.right_v, &world->camera.up_v, \
			deg_to_radians(-10));
			world->camera.right_v = vector_normalize(world->camera.right_v);
			world->camera.dir_v = vector_normalize(world->camera.dir_v);
			world->camera.up_v = vector_normalize(world->camera.up_v);
			return(1);
		}
	}
	if(ctx->input.keyboard.keys[NK_KEY_CTRL].down )
	{
		if(nk_input_is_key_released(&ctx->input, NK_KEY_E) && !ctx->input.keyboard.keys[NK_KEY_SHIFT].down && press == 2)
		{
			press = -1;
			vector_rot_z(&world->camera.right_v, &world->camera.up_v, \
			deg_to_radians(10));
			world->camera.right_v = vector_normalize(world->camera.right_v);
			world->camera.dir_v = vector_normalize(world->camera.dir_v);
			world->camera.up_v = vector_normalize(world->camera.up_v);
			return(1);
		}
	}
	// if(nk_input_is_key_released(&ctx->input, NK_KEY_Q) && press == 2)
	// {
	// 	press = -1;
	// 	cam_rot(&world->camera, 90, 'y');//	deg_to_radians(10));
	// 	// world->camera.right_v = vector_normalize(world->camera.right_v);
	// 	// world->camera.dir_v = vector_normalize(world->camera.dir_v);
	// 	// world->camera.up_v = vector_normalize(world->camera.up_v);
	// 	// get_camera_axes(&world->camera);
	// 	world->redraw = 1;
	// 	return(1);
	// }
	// if(nk_input_is_key_released(&ctx->input, NK_KEY_E) && press == 2)
	// {
	// 	press = -1;
	// 	cam_rot(&world->camera, -90, 'y');//	deg_to_radians(10));
	// 	// vector_rot_y(&world->camera.right_v, &world->camera.dir_v, \
	// 	// deg_to_radians(-10));
	// 	// world->camera.right_v = vector_normalize(world->camera.right_v);
	// 	// world->camera.dir_v = vector_normalize(world->camera.dir_v);
	// 	// world->camera.up_v = vector_normalize(world->camera.up_v);
	// 	// get_camera_axes(&world->camera);
	// 	world->redraw = 1;
	// 	return(1);
	// }
	// if (ctx->input.keyboard.keys[NK_KEY_SHIFT].down){
		
	// if(nk_input_is_key_released(&ctx->input, NK_KEY_W)  && press == 2)
	// {
	// 	press = -1;
		
	// 	move_up(world);
	// 	// vector_rot_y(&world->camera.right_v, &world->camera.dir_v, \
	// 	// deg_to_radians(-10));
	// 	// world->camera.right_v = vector_normalize(world->camera.right_v);
	// 	// world->camera.dir_v = vector_normalize(world->camera.dir_v);
	// 	// world->camera.up_v = vector_normalize(world->camera.up_v);
	// 	// get_camera_axes(&world->camera);
	// 	return(1);
	// }
	// if(nk_input_is_key_released(&ctx->input, NK_KEY_S)  && press == 2)
	// {
	// 	press = -1;
		
	// 	move_down(world);
	// 	// vector_rot_y(&world->camera.right_v, &world->camera.dir_v, \
	// 	// deg_to_radians(-10));
	// 	// world->camera.right_v = vector_normalize(world->camera.right_v);
	// 	// world->camera.dir_v = vector_normalize(world->camera.dir_v);
	// 	// world->camera.up_v = vector_normalize(world->camera.up_v);
	// 	// get_camera_axes(&world->camera);
	// 	return(1);
	// }
	// }
	// if(nk_input_is_key_released(&ctx->input, NK_KEY_UP) && press == 2)
	// {
	// 	press = -1;
	// 	cam_rot(&world->camera, 40, 'x');//	deg_to_radians(10));
	// 	// get_camera_axes(&world->camera);
	// 	world->redraw = 1;
	// 	return(1);
	// }
	// if(nk_input_is_key_released(&ctx->input, NK_KEY_DOWN) && press == 2)
	// {
	// 	press = -1;
	// 	cam_rot(&world->camera, -40, 'x');//	deg_to_radians(10));
	// 	world->redraw = 1;
	// 	return(1);
	// }
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
