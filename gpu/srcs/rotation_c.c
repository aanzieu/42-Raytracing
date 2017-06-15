/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

void	rotate_c(t_vec3d *point, double degrees, char axis)
{
	t_vec3d tmp;

	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;
	degrees = (-1) * deg_to_radians(degrees);
	if (axis == 'z')
	{
		point->x = tmp.x * cos(degrees) - tmp.y * sin(degrees);
		point->y = tmp.x * sin(degrees) + tmp.y * cos(degrees);
	}
	else if (axis == 'x')
	{
		point->y = tmp.y * cos(degrees) - tmp.z * sin(degrees);
		point->z = tmp.y * sin(degrees) + tmp.z * cos(degrees);
	}
	else if (axis == 'y')
	{
		point->z = tmp.z * cos(degrees) - tmp.x * sin(degrees);
		point->x = tmp.z * sin(degrees) + tmp.x * cos(degrees);
	}
}
