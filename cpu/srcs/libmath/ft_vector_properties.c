/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_properties.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:19:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/26 10:40:23 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

/*
** Normalize vector
*/

inline double		vector_square_root(t_vec3d v)
{
	return (sqrtf((powf(v.x, 2)) + (powf(v.y, 2)) + (powf(v.z, 2))));
}

inline t_vec3d		vector_normalize(t_vec3d v)
{
	t_vec3d	norm;
	double	id;

	id = vector_square_root(v);
	norm = new_3dvector(v.x / id, v.y / id, v.z / id);
	return (norm);
}

/*
** Find cos angle btw two vector after normalize them
*/

inline double		vector_dotproduct(t_vec3d a, t_vec3d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

/*
** Find orthogonal vector with two vector coplanaire
*/

inline t_vec3d		vector_crossproduct(t_vec3d a, t_vec3d b)
{
	t_vec3d	cross;

	cross = new_3dvector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
	return (cross);
}
