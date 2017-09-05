/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_calcul_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 08:10:47 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 09:10:15 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_color	color_scalar(double scalar, t_color c1)
{
	t_color	c2;

	c2 = new_color(c1.r * scalar, c1.g * scalar,
		c1.b * scalar, 0);
	return (c2);
}

t_color	color_sub(t_color c1, t_color c2)
{
	t_color	rslt;

	rslt = new_color(c1.r - c2.r, c1.g - c2.g,
		c1.b - c2.b, 0);
	return (rslt);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	rslt;

	rslt = new_color(c1.r + c2.r, c1.g + c2.g,
		c1.b + c2.b, 0);
	return (rslt);
}

t_color	color_multiply(t_color c1, t_color c2)
{
	t_color	rslt;

	rslt = new_color(c1.r * c2.r, c1.g * c2.g,
		c1.b * c2.b, 0);
	return (rslt);
}
