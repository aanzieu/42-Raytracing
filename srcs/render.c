/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 17:43:01 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <display.h>

/*
**	color = ray_tracer(world, x, y);
*/

void	render(t_world *world)
{
	int x;
	int y;
	int color;

	color = 0;
	y = 0;
	while (y < world->viewplane.y_res)
	{
		x = 0;
		while (x < world->viewplane.x_res)
		{
			pixel_to_image(world->window.screen, x, y, color);
			x++;
		}
		y++;
	}
}
