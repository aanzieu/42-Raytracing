/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_negative.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:19:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 15:00:01 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

void			negative_color(int *pix)
{
	int		x;
	int		y;
	t_cl	color;
	int		cur;

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
			color.r ^= 0x00FFFFFF;
			color.g ^= 0x00FFFFFF;
			color.b ^= 0x00FFFFFF;
			pix[cur] = RGB(color.r, color.g, color.b);
		}
	}
}
