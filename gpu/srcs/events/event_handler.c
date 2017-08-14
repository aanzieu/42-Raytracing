/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/22 12:12:39 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	get_event(t_world *world, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		key_press_handler1(world, event);
		key_press_handler2(world, event);
		key_press_handler3(world);
		key_press_handler4(world);
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
