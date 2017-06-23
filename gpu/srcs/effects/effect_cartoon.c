/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_cartoon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:24:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:25:36 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

static int	limit_color(int col)
{
	if (col <= 0)
		return (0);
	else if (col > 0 && col <= 50)
		return (25);
	else if (col > 50 && col <= 100)
		return (75);
	else if (col > 100 && col <= 200)
		return (150);
	else if (col > 200 && col < 250)
		return (225);
	else if (col >= 255)
		return (255);
	return (col);
}

void		shell_shading_effect(int *pix)
{
	int		i;
	int		j;
	int		cur;
	t_color	color;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cur = i * WIN_WIDTH + j;
			color.r = pix[cur] >> 16;
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.b = (pix[cur] & 0x0000FF);
			pix[cur] = RGB(limit_color(color.r), limit_color(color.g), limit_color(color.b));
			j++;
		}
		i++;
	}
}
