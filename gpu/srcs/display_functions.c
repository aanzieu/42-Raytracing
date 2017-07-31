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
#include <gpu_rt.h>

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

int					average_colors(int color1, int color2)
{
	t_color		rgb_color1;
	t_color		rgb_color2;
	t_color		average;

	rgb_color1 = int_to_rgb(color1);
	rgb_color2 = int_to_rgb(color2);
	average.r = (rgb_color1.r + rgb_color2.r) / 2;
	average.g = (rgb_color1.g + rgb_color2.g) / 2;
	average.b = (rgb_color1.b + rgb_color2.b) / 2;		

	return (rgb_to_int(rgb_color1));
}

int	anti_aliasing(t_world *world, int x, int y)
{
	int color;
	int		i;
	int		j;

	color = 0;
	i = 0;
	while (i < world->anti_aliasing)
	{
		j = 0;
		while (j < world->anti_aliasing)
		{
			if (color == 0)
				color = world->a_h[y * world->viewplane.x_res + x];
			else
				color = average_colors(color, world->a_h[(y + i) * world->viewplane.x_res + (x + j)]);
			j++;
		}
		i++;
	}
	return (color);
}

void				put_pixel_screen(t_world *world)
{
	int 			i;
	int 			j;
	int 			y;
	int				x;
	int				color;


	effect_application(world);
	i = 0;
	y = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		x = 0;
		while (j < WIN_WIDTH)
		{
			color = 0;
			if (world->anti_aliasing == 1)
				color = world->a_h[y * world->viewplane.x_res + x];
			else
				color = anti_aliasing(world, x, y);
			pixel_to_image(world->window.screen, j, i,
				color);
			j++;
			if (j % world->render_factor == 0)
					x += world->anti_aliasing;
		}
		i++;
		if (i % world->render_factor == 0)
					y += world->anti_aliasing;
	}
}
