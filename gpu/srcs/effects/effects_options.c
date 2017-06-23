/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 11:25:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:25:46 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

void		solarized_effect(int *pix)
{
	int		i;
	int		j;
	int		cur;
	t_color	color;
	t_color tmp;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cur = i * WIN_WIDTH + j;
			color.r = (pix[cur] & 0x0000FF);
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.b = pix[cur] >> 16;
			tmp.r = color.r < 152 ? 255 - color.r : color.r;
			tmp.g = color.g < 116 ? 255 - color.g : color.g;
			tmp.b = color.b < 124 ? 255 - color.b : color.b;
			pix[cur] = RGB(tmp.r, tmp.g, tmp.b);
			j++;
		}
		i++;
	}
}


void		filter_color(int *pix)
{
	int		x;
	int		y;
	float	invgamma;
	int		cur;
	t_color		c;

	invgamma = 0.68;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			c.r = (pix[cur] & 0x0000FF);
			c.g = (pix[cur] & 0x00FF00) >> 8;
			c.b = pix[cur] >> 16;
			pix[cur] = (int)RGB((powf(c.r, invgamma)),
					(powf(c.g, invgamma)), (powf(c.b, invgamma)));
		}
	}
}

/* Not Fonctionnel, need fixe*/

void		exposure_color(int *pix)
{
	int		x;
	int		y;
	float	exposure;
	int		cur;
	t_color		c;

	exposure = -0.66f;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			c.r = (pix[cur] & 0x0000FF);
			c.g = (pix[cur] & 0x00FF00) >> 8;
			c.b = pix[cur] >> 16;
			pix[cur] = RGB((1.0f - expf(c.r * exposure)),
						(1.0f - expf(c.g * exposure)),
						(1.0f - expf(c.b * exposure)));
		}
	}
}
