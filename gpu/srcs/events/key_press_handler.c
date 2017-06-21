/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/21 10:13:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <vectors.h>
#include <gpu_rt.h>

void	key_press_handler1(t_world *world, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_UP)
		world->keys.up = 1;
	if (event.key.keysym.sym == SDLK_DOWN)
		world->keys.down = 1;
	if (event.key.keysym.sym == SDLK_RIGHT)
		world->keys.right = 1;
	if (event.key.keysym.sym == SDLK_LEFT)
		world->keys.left = 1;
	if (event.key.keysym.sym == SDLK_SPACE)
		world->keys.space = 1;
	if (event.key.keysym.sym == SDLK_w)
		world->keys.w = 1;
	if (event.key.keysym.sym == SDLK_w)
		world->keys.w = 1;
	if (event.key.keysym.sym == SDLK_w)
		world->keys.w = 1;
	if (event.key.keysym.sym == SDLK_a)
		world->keys.a = 1;
	if (event.key.keysym.sym == SDLK_s)
		world->keys.s = 1;
	if (event.key.keysym.sym == SDLK_d)
		world->keys.d = 1;
	// if (event.key.keysym.sym == SDLK_RIGHTBRACKET)
	// 	world->keys.rightbracket = 1;
	// if (event.key.keysym.sym == SDLK_LEFTBRACKET)
	// 	world->keys.leftbracket = 1;
	// if (event.key.keysym.sym == SDLK_j)
	// 	world->keys.j = 1;
	// if (event.key.keysym.sym == SDLK_l)
	// 	world->keys.l = 1;
	// if (event.key.keysym.sym == SDLK_k)
	// 	world->keys.k = 1;
	// if (event.key.keysym.sym == SDLK_i)
	// 	world->keys.i = 1;
	return ;
}

void	key_press_handler2(t_world *world, SDL_Event event)
{
	(void)event;
	(void)world;
	// if (event.key.keysym.sym == SDLK_q)
	// {
	// 	world->keys.w = 0;
	// 	world->keys.q = 1;
	// }
	// if (event.key.keysym.sym == SDLK_w)
	// {
	// 	world->keys.q = 0;
	// 	world->keys.w = 1;
	// }
	// if (event.key.keysym.sym == SDLK_KP_4)
	// 	world->keys.four = 1;
	// if (event.key.keysym.sym == SDLK_KP_5)
	// 	world->keys.five = 1;
	// if (event.key.keysym.sym == SDLK_KP_6)
	// 	world->keys.six = 1;
	// if (event.key.keysym.sym == SDLK_KP_8)
	// 	world->keys.eight = 1;
}

void	key_press_handler3(t_world *world, SDL_Event event)
{
	(void)event;
	if (world->keys.up == 1)
		cam_rot(&world->camera, -90	, 'x');
	if (world->keys.down == 1)
		cam_rot(&world->camera, 90	, 'x');
	if (world->keys.left == 1)
		cam_rot(&world->camera, -90	, 'y');
	if (world->keys.right == 1)
		cam_rot(&world->camera, 90	, 'y');
	if (world->keys.w == 1)
	{
		translate(&world->camera.pos, 0, 0, 0.5);
		translate(&world->camera.look_at, 0, 0, 0.5);
		get_camera_axes(&world->camera);	
		// translate(&world->camera.dir_v, 0, 0, 1);
		// translate(&world->camera.up_v, 0, 0, 1);
		// translate(&world->camera.right_v, 0, 0, 1);		
	}
	if (world->keys.a == 1)
	{
		translate(&world->camera.pos, -0.5, 0, 0);
		translate(&world->camera.look_at, -0.5, 0, 0);
		get_camera_axes(&world->camera);	
	}
	if (world->keys.s == 1)
	{
		translate(&world->camera.pos, 0, 0, -0.5);
		translate(&world->camera.look_at, 0, 0, -0.5);
		get_camera_axes(&world->camera);	
	}
	if (world->keys.d == 1)
	if (world->keys.a == 1)
	{
		translate(&world->camera.pos, 0.5, 0, 0);
		translate(&world->camera.look_at, 0.5, 0, 0);
		get_camera_axes(&world->camera);	
	}
	if (world->keys.space == 1)
	{
		while ((WIN_HEIGHT / world->render_factor) != 32)
					world->render_factor++;
	}
	// if (world->keys.rightbracket == 1)
	// 	world->lights->pos.z += 0.05;
	// if (world->keys.leftbracket == 1)
	// 	world->lights->pos.z -= 0.05;
	// // if (world->keys.q == 1)
	// // 	sphere_key_handler(world);
	// // if (world->keys.w == 1)
	// // 	plane_key_handler(world);
	// if (world->keys.j == 1)
	// 	world->lights->pos.x -= 0.1;
	// if (world->keys.l == 1)
	// 	world->lights->pos.x += 0.1;
	// if (world->keys.k == 1)
	// 	world->lights->pos.y -= 0.1;
	// if (world->keys.i == 1)
	// 	world->lights->pos.y += 0.1;
}
