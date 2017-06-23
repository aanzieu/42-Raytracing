/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_sepia.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 09:21:32 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 09:21:52 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

/* Convert  marroon on r,g,b and */
void		sepia_effect(int *pix)
{
	int		i;
	int		j;
	int		tmp;
	int		cur;
	t_color	tmpx;
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
			tmp = (((double)color.r * 0.393  + (double)color.g * 0.769 + (double)color.b) * 0.189) * 1.8;
			tmpx.r = tmp > 255 ? 255 : tmp;
			tmp = (((double)color.r *0.349  + (double)color.g * 0.686 + (double)color.b) * 0.168) * 1.8;
			tmpx.g = tmp > 255 ? 255 : tmp;
			tmp =(((double)color.r * 0.272  + (double)color.g * 0.534 + (double)color.b) * 0.131) * 1.8;
			tmpx.b = tmp > 255 ? 255 : tmp;
			color.r = tmpx.r;
			color.g = tmpx.g;
			color.b = tmpx.b;
			pix[cur] = color.r * 256 * 256 + color.g * 256 + color.b;
			++j;
		}++i;
	}
}
