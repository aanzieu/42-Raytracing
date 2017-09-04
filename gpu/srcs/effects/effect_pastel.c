/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_pastel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:20:22 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:21:55 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

void				int_to_int(int *src, int *dst, int width, int height)
{
	int		i;
	int		j;
	size_t	size;

	size = sizeof(int) * width * height;
	ft_bzero(dst, size);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			dst[i * width + j] = src[i * width + j];
			j++;
		}
		i++;
	}
}

static void			reinit_avg(int averages[][4], t_pastel pastel)
{
	int	i;
	int	j;

	i = pastel.level;
	while (i--)
	{
		j = 4;
		while (j--)
		{
			averages[i][j] = 0;
		}
	}
}

static void			each_in_radius(t_pastel pastel, t_pos pix,
										int *from, int averages[][4])
{
	int				lvl;
	int				i;
	int				j;
	t_color			color;
	int				cur;

	reinit_avg(averages, pastel);
	j = -(pastel.radius) - 1;
	while (++j < pastel.radius)
	{
		i = -(pastel.radius - 1);
		while (++i < pastel.radius)
		{
			if ((i + pix.x) >= 0 && (i + pix.x) < pix.width &&
						(j + pix.y) >= 0 && (j + pix.y) < pix.height)
			{
				cur = (j + pix.y) * pix.width + (i + pix.x);
				color.r = (from[cur] & 0x0000FF);
				color.g = (from[cur] & 0x00FF00) >> 8;
				color.b = from[cur] >> 16;
				lvl = (((double)color.r + (double)color.g +
					(double)color.b) / 3) * (double)pastel.level / 256.0;
				averages[lvl][3]++;
				averages[lvl][0] += color.r;
				averages[lvl][1] += color.g;
				averages[lvl][2] += color.b;
			}
		}
	}
}

static void			filler(t_pastel pastel, t_pos pix,
								int *to, int averages[][4])
{
	double			max;
	double			max_index;
	int				i;
	t_color			color;
	int				cur;

	i = pastel.level;
	max = 1;
	max_index = 0;
	while (i--)
	{
		if (max < averages[i][3])
		{
			max = averages[i][3];
			max_index = i;
		}
	}
	cur = (pix.y * pix.width + pix.x);
	color.r = averages[(int)max_index][0] / max;
	color.g = averages[(int)max_index][1] / max;
	color.b = averages[(int)max_index][2] / max;
	to[cur] = (RGB(color.r, color.g, color.b));
}

void				pastel_effect(int *pix, int height, int width)
{
	t_pastel	pastel;
	int			averages[pastel.level][4];
	int			x;
	int			y;
	t_pos		pos;
	int			*sum;

	pastel.level = 10;
	pastel.radius = 10;
	if (pastel.radius >= height * width)
		return ;
	sum = malloc(height * width * sizeof(int));
	ft_bzero(sum, height * width * sizeof(int));
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			pos.x = x;
			pos.y = y;
			pos.width = width;
			pos.height = height;
			each_in_radius(pastel, pos, pix, averages);
			filler(pastel, pos, sum, averages);
		}
	}
	int_to_int(sum, pix, width, height);
	free(sum);
}
