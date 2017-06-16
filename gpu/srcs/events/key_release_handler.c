/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 10:46:37 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"
#include "../../srcs/cuda/cudaheader/gpu_rt.cuh"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <math.h>
#include "../../frameworks/SDL2.framework/Headers/SDL.h"

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
	// if (event.key.keysym.sym == SDLK_KP_4)
	// 	world->keys.four = 0;
	// if (event.key.keysym.sym == SDLK_KP_5)
	// 	world->keys.five = 0;
	// if (event.key.keysym.sym == SDLK_KP_6)
	// 	world->keys.six = 0;
	// if (event.key.keysym.sym == SDLK_KP_8)
	// 	world->keys.eight = 0;
	return ;
}
