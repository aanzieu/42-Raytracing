/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:09:12 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"
#include "../../libft/libft.h"
#include "../../includes/keys.h"
#include <stdlib.h>
#include <math.h>
#include "../../frameworks/SDL2.framework/Headers/SDL.h"

void	get_event(t_world *world, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{		
		key_press_handler1(world, event);
		key_press_handler2(world, event);
		key_press_handler3(world, event);
		if (event.key.keysym.sym == SDLK_e)
			while (world->render_factor > 1)
				world->render_factor--;
	}
	if (event.type == SDL_KEYUP)
	{
		key_release_handler1(world, event);
		key_release_handler2(world, event);
	}

}

int		event_handler(t_world *world, SDL_Event event)
{
	if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
			event.key.keysym.sym == SDLK_ESCAPE))
		return (1);
	mouse_movement(world);		
	get_event(world, event);
	return (0);
}

/*
**	if (world->keys.up == 1)
**	if (world->keys.right == 1)
*/
