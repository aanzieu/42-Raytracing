/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:04:32 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 18:07:27 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_color	int_to_rgb(int color)
{
	t_color	rgb_color;

	if (color > 16777215)
		color = 16777215;
	rgb_color.b = color & 255;
	rgb_color.g = (color >> 8) & 255;
	rgb_color.r = (color >> 16) & 255;
	return (rgb_color);
}
