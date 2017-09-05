/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_black_and_white.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:23:45 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:25:06 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

/*
** add r,g,b and divide by 3
*/

void		black_and_white_effect(int *pix)
{
	int		i;
	int		j;
	int		grey;
	int		cur;
	t_color	color;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cur = i * WIN_WIDTH + j;
			color.b = pix[cur] >> 16;
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.r = (pix[cur] & 0x0000FF);
			grey = ((double)color.r + (double)color.g + (double)color.b) / 3;
			color.r = grey;
			color.g = grey;
			color.b = grey;
			pix[cur] = RGB(color.r, color.g, color.b);
			j++;
		}
		i++;
	}
}
