/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_pastel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:20:22 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 15:59:47 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

void			int_to_int(int *src, int *dst, int width, int height)
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

void			reinit_avg(int averages[][4], t_pastel pastel)
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

void			each_in_radius(t_pastel pastel, t_pos p,
										int *from, int averages[][4])
{
	int				lvl;
	t_color			cl;
	int				cur;

	p.j = -(pastel.radius) - 1;
	while (++p.j < pastel.radius)
	{
		p.i = -(pastel.radius - 1);
		while (++p.i < pastel.radius)
		{
			if ((p.i + p.x) >= 0 && (p.i + p.x)
					< p.w && (p.j + p.y) >= 0 && (p.j + p.y) < p.h)
			{
				cur = (p.j + p.y) * p.w + (p.i + p.x);
				cl.r = (from[cur] & 0x0000FF);
				cl.g = (from[cur] & 0x00FF00) >> 8;
				cl.b = from[cur] >> 16;
				lvl = ((cl.r + cl.g + cl.b) / 3) * pastel.level / 256.0;
				averages[lvl][3]++;
				averages[lvl][0] += cl.r;
				averages[lvl][1] += cl.g;
				averages[lvl][2] += cl.b;
			}
		}
	}
}

void			filler(t_pastel pastel, t_pos p,
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
	cur = (p.y * p.w + p.x);
	color.r = averages[(int)max_index][0] / max;
	color.g = averages[(int)max_index][1] / max;
	color.b = averages[(int)max_index][2] / max;
	to[cur] = (RGB(color.r, color.g, color.b));
}

void			pastel_effect(int *pix, int height, int width,
		int averages[10][4])
{
	t_pastel	pastel;
	t_pos		pos;
	int			*sum;

	pastel.level = 10;
	pastel.radius = 10;
	if (pastel.radius >= height * width)
		return ;
	sum = ft_memalloc(height * width * sizeof(int));
	ft_bzero(sum, height * width * sizeof(int));
	pos.y = -1;
	while (++pos.y < height)
	{
		pos.x = -1;
		while (++pos.x < width)
		{
			pos.w = width;
			pos.h = height;
			reinit_avg(averages, pastel);
			each_in_radius(pastel, pos, pix, averages);
			filler(pastel, pos, sum, averages);
		}
	}
	int_to_int(sum, pix, width, height);
	free(sum);
}
