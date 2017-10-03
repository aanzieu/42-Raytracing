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

	if (intersection_tmp->id == disk.id)
		return (0);
	plane.pos = disk.pos;
	plane.up = disk.up;
	plane.id = disk.id;
	if (get_plane(plane, ray, intersection_tmp) == 1)
	{
		intersection_tmp->pos = vector_add(ray.origin,
		vector_scalar(ray.dir, intersection_tmp->t));
		radius_v = vector_calculate(disk.pos, intersection_tmp->pos);
		if (vector_dot(radius_v, radius_v) <= disk.radius_squared)
		{
		 	intersection_tmp->id = disk.id;
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
				intersection->id = world.disks[i].id;
				intersection->id_save = world.disks[i].id;
				intersection->t = intersection_tmp->t;
				intersection->type = 'd';
				intersection->reflection_coef = world.disks[i].reflection_coef;
				intersection->refraction_coef = world.disks[i].refraction_coef;
				intersection->transparence_coef = world.disks[i].transparence_coef;
				intersection->color = world.disks[i].color;
				intersection->chess = world.disks[i].chess;
				intersection->pos = intersection_tmp->pos;
				intersection->normal_v = intersection_tmp->normal_v;
				if(world.on == 1){
				apply_noise_dist(world, intersection, world.disks[i].perlin);}
			}
		}
		i++;
	}
}
