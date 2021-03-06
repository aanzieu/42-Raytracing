/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/23 11:45:19 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	key_release_handler1(t_world *world, SDL_Event event)
{
	(void)world;
	if (event.key.keysym.sym == SDLK_UP)
		world->keys.up = 0;
	if (event.key.keysym.sym == SDLK_DOWN)
		world->keys.down = 0;
	if (event.key.keysym.sym == SDLK_RIGHT)
		world->keys.right = 0;
	if (event.key.keysym.sym == SDLK_LEFT)
		world->keys.left = 0;
	if (event.key.keysym.sym == SDLK_SPACE)
	{
		world->keys.space = 0;
		world->render_factor = 1;
	}
	if (event.key.keysym.sym == SDLK_w)
		world->keys.w = 0;
	if (event.key.keysym.sym == SDLK_a)
		world->keys.a = 0;
	if (event.key.keysym.sym == SDLK_s)
		world->keys.s = 0;
	if (event.key.keysym.sym == SDLK_d)
		world->keys.d = 0;
	return ;
}

void	key_release_handler2(t_world *world, SDL_Event event)
{
	(void)event;
	(void)world;
	if (event.key.keysym.sym == SDLK_1)
		world->keys.pad_1 = 0;
	if (event.key.keysym.sym == SDLK_2)
		world->keys.pad_2 = 0;
	if (event.key.keysym.sym == SDLK_3)
		world->keys.pad_3 = 0;
	if (event.key.keysym.sym == SDLK_4)
		world->keys.pad_4 = 0;
	if (event.key.keysym.sym == SDLK_5)
		world->keys.pad_5 = 0;
	if (event.key.keysym.sym == SDLK_6)
		world->keys.pad_6 = 0;
	if (event.key.keysym.sym == SDLK_7)
		world->keys.pad_7 = 0;
	if (event.key.keysym.sym == SDLK_8)
		world->keys.pad_8 = 0;
	if (event.key.keysym.sym == SDLK_9)
		world->keys.pad_9 = 0;
	if (event.key.keysym.sym == SDLK_q)
		world->keys.q = 0;
	if (event.key.keysym.sym == SDLK_e)
		world->keys.e = 0;
	return ;
}
