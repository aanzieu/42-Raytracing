/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_negative.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:19:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:21:54 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

void		negative_color(int *pix)
{
	int		x;
	int		y;
	int		r;
	int		g;
	int		b;
	int		cur;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			r = (pix[cur] & 0x0000FF);
			g = (pix[cur] & 0x00FF00) >> 8;
			b = pix[cur] >> 16;
			r ^= 0x00FFFFFF;
			g ^= 0x00FFFFFF;
			b ^= 0x00FFFFFF;
			pix[cur] = RGB(r, g, b);
		}
	}
}
