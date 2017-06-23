/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
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

__host__ __device__ int		get_disk(t_disk disk, t_ray ray,
										t_intersection *intersection_tmp)
{
	t_vec3d	radius_v;
	t_plane	plane;

	plane.pos = disk.pos;
	plane.up = disk.up;
	if (get_plane(plane, ray, intersection_tmp) == 1)
	{
		intersection_tmp->pos = vector_add(ray.origin,
		vector_scalar(ray.dir, intersection_tmp->t));
		radius_v = vector_calculate(disk.pos, intersection_tmp->pos);
		if (vector_dot(radius_v, radius_v) <= disk.radius_squared)
		{
			intersection_tmp->type = 'd';
			return (1);
		}
	}
	return (0);
}

__host__ __device__ void	get_closest_disk(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.disks_len)
	{
		if (get_disk(world.disks[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflexion_coef = world.disks[i].reflexion_coef;
				intersection->color = &world.disks[i].color;
				intersection->pos = intersection_tmp->pos;
				intersection->normal_v = intersection_tmp->normal_v;
			}
		}
		i++;		
	}
}