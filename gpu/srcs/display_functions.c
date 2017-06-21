/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/21 11:49:07 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8 *pixel;

	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

void				put_pixel_screen(t_world *world)
{
	int 			i;
	int 			j;
	int 			y;
	int				x;

	i = 0;
	y = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		x = 0;
		while (j < WIN_WIDTH)
		{
			pixel_to_image(world->window.screen, j, i,
					world->a_h[y * world->viewplane.x_res + x]);
			j++;
			if (j % world->render_factor == 0)
				x++;
		}
		i++;
		if (i % world->render_factor == 0)
			y++;
	}
}
