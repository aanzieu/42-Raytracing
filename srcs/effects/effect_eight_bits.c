/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_eight_bits.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:16:24 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:21:59 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

static void		pixellize_screen(int *pix, int width, int height, int intensity)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		color;

	x = -intensity;
	while ((x += intensity) < width)
	{
		y = -intensity;
		while ((y += intensity) < height)
		{
			color = pix[width * y + x];
			i = -1;
			while (++i < intensity)
			{
				j = -1;
				while (++j < intensity)
					pix[width * (y + i) + x + j] = color;
			}
		}
	}
}

void			eight_bit_effect(int *pix)
{
	int		i;
	int		j;
	int		value;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			value = pix[i * WIN_WIDTH + j];
			value /= (1 << 4);
			pix[i * WIN_WIDTH + j] = value * (1 << 4);
			++j;
		}
		++i;
	}
	pixellize_screen(pix, WIN_WIDTH, WIN_HEIGHT, WIN_HEIGHT / 128);
}
