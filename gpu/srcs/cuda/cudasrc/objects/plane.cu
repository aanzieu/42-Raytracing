/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/04/25 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <rt.h>
	#include "gpu_rt.h"
	#include <vectors.h>
}

/*
**	On envoie le rayon et la structure qui contient le plan et la fonction
**	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
**	avec le plan
*/

__host__ __device__ int		get_plane(t_plane plane, t_ray ray, t_intersection *intersection_tmp)
{
	double	t;
	double	denominator;
	t_vec3d	x;
	double	n;


	intersection_tmp->normal_v = vector_normalize(
		vector_calculate(plane.pos, plane.up));
	denominator = vector_dot(ray.dir, intersection_tmp->normal_v);
	if (denominator != 0 && intersection_tmp->id != plane.id)
	{
		x = vector_scalar(vector_calculate(plane.pos, ray.origin), -1);
		n = vector_dot(x, intersection_tmp->normal_v);
		t = n / denominator;
		if (t > 0.0000001)
		{
			intersection_tmp->t = t;
			intersection_tmp->type = 'p';
			if (denominator > 0)
				intersection_tmp->normal_v =
					vector_scalar(intersection_tmp->normal_v, -1);
			if (plane.refraction_coef != 0 || plane.reflection_coef != 0)
				intersection_tmp->id = plane.id;
			return (1);
		}
	}
	return (0);
}

__host__ __device__ void	get_closest_plane(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.planes_len)
	{
		if (get_plane(world.planes[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->id = world.planes[i].id;
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflection_coef = world.planes[i].reflection_coef;
				intersection->refraction_coef = world.planes[i].refraction_coef;
				intersection->color = &world.planes[i].color;
				intersection->chess = &world.planes[i].chess;
				intersection->pos = vector_add(ray.origin,
				vector_scalar(ray.dir, intersection->t));
				intersection->normal_v = intersection_tmp->normal_v;
			}
		}
		i++;
	}
}
