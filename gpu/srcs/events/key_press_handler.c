/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/08/21 23:53:06 by PZC              ###   ########.fr       */
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
	if (event.key.keysym.sym == SDLK_a)
		world->keys.a = 1;
	if (event.key.keysym.sym == SDLK_s)
		world->keys.s = 1;
	if (event.key.keysym.sym == SDLK_d)
		world->keys.d = 1;
	if (event.key.keysym.sym == SDLK_0)
		world->keys.pad_0 = 1;
}

void	key_press_handler2(t_world *world, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_1)
		world->keys.pad_1 = 1;
	if (event.key.keysym.sym == SDLK_2)
		world->keys.pad_2 = 1;
	if (event.key.keysym.sym == SDLK_3)
		world->keys.pad_3 = 1;
	if (event.key.keysym.sym == SDLK_4)
		world->keys.pad_4 = 1;
	if (event.key.keysym.sym == SDLK_5)
		world->keys.pad_5 = 1;
	if (event.key.keysym.sym == SDLK_6)
		world->keys.pad_6 = 1;
	if (event.key.keysym.sym == SDLK_7)
		world->keys.pad_7 = 1;
	if (event.key.keysym.sym == SDLK_8)
		world->keys.pad_8 = 1;
	if (event.key.keysym.sym == SDLK_9)
		world->keys.pad_9 = 1;
	if (event.key.keysym.sym == SDLK_q)
		world->keys.q = 1;
	if (event.key.keysym.sym == SDLK_e)
		world->keys.e = 1;
	if (event.key.keysym.sym == SDLK_p)
		world->keys.p = 1;
}

void	key_press_handler3(t_world *world, SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_PAGEUP)
		world->recording = 1;
	if (event.key.keysym.sym == SDLK_PAGEDOWN)
		world->recording = 0;
	if (event.key.keysym.sym == SDLK_HOME)
		world->animation_forward = 1;
	if (event.key.keysym.sym == SDLK_END)
		world->animation_forward = 0;
}

void	key_press_handler4(t_world *world)
{
	if (world->keys.up == 1)
		cam_rot(&world->camera, -90	, 'x');
	if (world->keys.down == 1)
		cam_rot(&world->camera, 90	, 'x');
	if (world->keys.left == 1)
		cam_rot(&world->camera, -90	, 'y');
	if (world->keys.right == 1)
		cam_rot(&world->camera, 90	, 'y');
	if (world->keys.w == 1)
		move_forward(world);
	if (world->keys.a == 1)
		move_left(world);
	if (world->keys.s == 1)
		move_backward(world);
	if (world->keys.d == 1)
		move_right(world);
}

void	key_press_handler5(t_world *world)
{
	if (world->keys.p == 1)
		savebmp(world);
	if (world->keys.space == 1)
	{
		while ((WIN_HEIGHT / world->render_factor) != 32)
			world->render_factor++;
	}
}
