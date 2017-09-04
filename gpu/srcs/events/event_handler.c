/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/08/22 14:37:12 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	get_event(t_world *world, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		key_press_handler1(world, event);
		key_press_handler2(world, event);
		key_press_handler3(world, event);
		key_press_handler4(world);
		key_press_handler5(world);
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
