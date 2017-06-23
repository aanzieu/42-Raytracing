/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_bayer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:22:50 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:25:04 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

void		bayer_color(int *pix)
{
	int		x;
	int		y;
	int		cur;
	int		bayervalue = 2;
	t_color color;
	
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			color.r = (pix[cur] & 0x0000FF);
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.b = pix[cur] >> 16;
			if((y / bayervalue) & 1)
				color.b = 0;
			else
				color.r = 0;
			if((x / bayervalue) & 1)
				color.g = 0;
			pix[cur] = RGB(color.r, color.g, color.b);
		}
	}
}
