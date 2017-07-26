/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/26 14:46:23 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <effects.h>

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8 *pixel;

	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}
/*
int			*ft_intcpy(int	*src, int width, int height)
{
	int	i;
	int	j;
	int	*tmp;
	size_t size;

	size = sizeof(int) * width * height;
	if (!(tmp = malloc(size)))
		exit(0);
	ft_bzero(tmp, size);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			tmp[i * width + j] = src[i * width + j];
			j++;
		}
		i++;
	}
	return(tmp);
}
*/
void				effect_application(t_world *world)
{
	if(world->keys.pad_1 == 1)
		eight_bit_effect(world->a_h);
	else if(world->keys.pad_2 == 1)
		black_and_white_effect(world->a_h);
	else if(world->keys.pad_3 == 1)
		sepia_effect(world->a_h);
	else if(world->keys.pad_4 == 1)
		pastel_effect(world->a_h, world->viewplane.y_res, world->viewplane.x_res);
	else if(world->keys.pad_0 == 1)
		solarized_effect(world->a_h);
	else if(world->keys.pad_5 == 1)
		bayer_color(world->a_h);
	else if(world->keys.pad_6 == 1)
		negative_color(world->a_h);
	else if(world->keys.pad_7 == 1)
		filter_color(world->a_h);
// Not fonctionnel
//	else if(world->keys.pad_8 == 1)
//		exposure_color(world->a_h);
	else if(world->keys.pad_9 == 1)
		shell_shading_effect(world->a_h);

}

void				put_pixel_screen(t_world *world)
{
	int 			i;
	int 			j;
	int 			y;
	int				x;


	effect_application(world);
	i = 0;
	y = 0;
//	printf("couleurs %d :\n", world->a_h[620]);
	while (i < WIN_HEIGHT)
	{
		j = 0;
		x = 0;
		while (j < WIN_WIDTH)
		{
		//	printf("couleur pixel %d\n", world->a_h[y * world->viewplane.x_res + x]);
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
