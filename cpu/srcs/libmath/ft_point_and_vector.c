/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_and_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:44:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 13:15:05 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

/*
** Calcul Vector btw two point
*/

t_vec3d		point_to_vector(t_3point a, t_3point b)
{
	t_vec3d	new;

	new = new_3dvector(b.x - a.x, b.y - a.y, b.z - a.z);
	return (new);
}

/*
** Calcul distance btw two points
*/

double		distance_btw_3points(t_3point a, t_3point b)
{
	t_vec3d	new;

	new = point_to_vector(a, b);
	return (vector_square_root(new));
}

t_3point	point_scalaire(t_3point a, double coeff)
{
	t_3point	new;

	new.x = a.x * coeff;
	new.y = a.y * coeff;
	new.z = a.z * coeff;
	return (new);
}

t_vec3d		point_vect_sub(t_3point a, t_vec3d b)
{
	t_vec3d	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

t_vec3d		point_vect_add(t_3point a, t_vec3d b)
{
	t_vec3d	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}
