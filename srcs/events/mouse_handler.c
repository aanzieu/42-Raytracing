/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 16:08:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gpu_rt.h"

void	mouse_movement(t_world *world)
{
	int	mouse_x;
	int mouse_y;

	SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
	if (world->keys.space == 1)
	{
		if (mouse_x < 0)
			cam_rot(&world->camera, -90	, 'y');
		else if (mouse_x > 0)
			cam_rot(&world->camera, 90	, 'y');
		if (mouse_y < 0)
			cam_rot(&world->camera, -90	, 'x');
		else if (mouse_y > 0)
			cam_rot(&world->camera, 90	, 'x');
	}
	mouse_x = 0;
	mouse_y = 0;
}
