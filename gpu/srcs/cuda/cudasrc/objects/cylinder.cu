/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/04/25 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <rt.h>
	#include <gpu_rt.h>
	#include <equation.h>
}
#include <float.h>

__host__ __device__ int		limit_cylinder(t_cylinder cylinder, t_ray ray,
		t_intersection *intersection_tmp, t_vec3d axis, t_vec3d x, t_eq eq)
{
	double b[2];

	b[0] = vector_dot(ray.dir, axis) * eq.res[0] + vector_dot(x, axis);
	b[1] = vector_dot(ray.dir, axis) * eq.res[1] + vector_dot(x, axis);
	intersection_tmp->normal_v = vector_normalize(
		vector_substract(vector_substract(
				intersection_tmp->pos, cylinder.pos), vector_scalar(axis, b[0])));
	if (cylinder.height <= 0)
		return (1);
	if ((b[0] > 0 && b[0] < cylinder.height)
		|| (b[1] > 0 && b[1] < cylinder.height))
		return (1);
	return (0);
}

__host__ __device__ int		get_cylinder(t_world world, t_cylinder cylinder,
							t_ray ray, t_intersection *intersection_tmp)
{
	t_eq		eq;
	t_vec3d axis;
	t_vec3d x;

 	if (intersection_tmp->id == cylinder.id)
		return (0);
	axis = vector_normalize(vector_substract(cylinder.up, cylinder.pos));
	x = vector_substract(ray.origin, cylinder.pos);
	eq.a = vector_dot(ray.dir, ray.dir) - pow(vector_dot(ray.dir, axis), 2);
	eq.b = 2 * (vector_dot(ray.dir, x) - (vector_dot(ray.dir, axis)
		* vector_dot(x, axis)));
	eq.c = vector_dot(x, x) - pow(vector_dot(x, axis), 2)
		- pow(cylinder.radius, 2);
	second_degres(&eq);
	if (eq.res[0] != NOT_A_SOLUTION)
	{
		intersection_tmp->t = eq.res[0];
		intersection_tmp->pos = vector_add(ray.origin,
			vector_scalar(ray.dir, intersection_tmp->t));
		x = vector_substract(ray.origin, cylinder.pos);
		// intersection_tmp->normal_v = vector_normalize(
		// 	vector_substract(vector_substract(
		// 			intersection_tmp->pos, cylinder.pos),
		// 			vector_scalar(axis, b[0])));
		if (limit_cylinder(cylinder, ray, intersection_tmp, axis, x, eq))
			return (1);
	}
 	intersection_tmp->t = -1;
	return (-1);
}

__host__ __device__ void	get_closest_cylinder(t_world world, t_ray ray,
				t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.cylinders_len)
	{
		if (get_cylinder(world, world.cylinders[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t > 0)
			{
				intersection->id = world.cylinders[i].id;
				intersection->id_save = world.cylinders[i].id;
				intersection->t = intersection_tmp->t;
				intersection->type = 'y';
				intersection->reflection_coef = world.cylinders[i].reflection_coef;
				intersection->refraction_coef = world.cylinders[i].refraction_coef;
				intersection->transparence_coef = world.cylinders[i].transparence_coef;
				intersection->color = world.cylinders[i].color;
				intersection->chess = world.cylinders[i].chess;
				intersection->pos = intersection_tmp->pos;
				intersection->normal_v = intersection_tmp->normal_v;
			}
		}
		i++;
	}
}
