/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:13:53 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/06 11:32:34 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

/*
** Charle's Relation, vector sum AB + BC = AC
*/

inline t_vec3d		vector_sum(t_vec3d a, t_vec3d b)
{
	return (new_3dvector(a.x + b.x, a.y + b.y, a.z + b.z));
}

/*
** Charle's Relation, vector sub AB - CD = AB + (-CD) // opposite 2sd Vector
*/

inline t_vec3d		vector_sub(t_vec3d a, t_vec3d b)
{
	return (new_3dvector(a.x - b.x, a.y - b.y, a.z - b.z));
}

/*
** Return new vector multiply with a number
*/

inline t_vec3d		vector_scalaire(t_vec3d a, double b)
{
	return (new_3dvector(a.x * b, a.y * b, a.z * b));
}

/*
** Return opposite vector
*/

inline t_vec3d		vector_neg(t_vec3d v)
{
	return (new_3dvector(v.x * -1, v.y * -1, v.z * -1));
}

/*
 ** Return coordonate of point
*/

inline t_3point		vector_to_point(t_vec3d m, t_3point a)
{
	return (new_3point(m.x + a.x, m.y + a.y, m.z + a.z));
}
