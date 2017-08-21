/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/08/22 00:32:11 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gpu_rt.h"

void	mouse_press_handler(t_world *world, SDL_Event event)
{
	int	mouse_x;
	int mouse_y;

	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (event.button.button == SDL_BUTTON_LEFT) {
		if ((mouse_x > 0 && mouse_x < 100) && (mouse_y > 0 && mouse_y < 36))
			savebmp(world);
		if ((mouse_x > 102 && mouse_x < 202) && (mouse_y > 0 && mouse_y < 36))
			system("open ./screenshots");
		printf("x:%d y:%d\n", mouse_x, mouse_y);
	}
}

static void listen_cursor_statement(t_world *world)
{
	int	cursor_x;
	int cursor_y;

	SDL_GetMouseState(&cursor_x, &cursor_y);
	if ((cursor_x > 0 && cursor_x < 100) && (cursor_y > 0 && cursor_y < 36))
		world->keys.p = 1;
	else
		world->keys.p = 0;
	printf("x:%d y:%d\n", cursor_x, cursor_y);
}

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
	listen_cursor_statement(world);
}
