/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
#include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ t_vec3d		get_normal_cone(t_cone cone, t_ray ray,
		t_intersection intersection)
{
	t_vec3d axis_v;
	t_vec3d	normal_v;
	t_vec3d	x;
	double	m;
	double	k;

	k = cone.half_angle;
	x = vector_substract(ray.origin, cone.pos);
	axis_v = vector_normalize(vector_calculate(cone.pos, cone.up));
	m = vector_dot(ray.dir, vector_scalar(axis_v, intersection.t))
		+ vector_dot(x, axis_v);
	normal_v = vector_normalize(
			vector_substract(
				vector_substract(
					intersection.pos, cone.pos),
				vector_scalar(
					vector_scalar(
						axis_v, m), 1 + (k * k))));
	return (normal_v);
}

__host__ __device__ static int		limit_cone(t_cone cone, t_ray ray,
		t_intersection *intersection_tmp, t_vec3d axis_v, t_vec3d x, t_eq eq)
{
	double b[2];
	double k;

	k = cone.half_angle;
	b[0] = vector_dot(ray.dir, vector_scalar(axis_v, eq.res[0]))
	 	+ vector_dot(x, axis_v);
	b[1] = vector_dot(ray.dir, vector_scalar(axis_v, eq.res[1]))
	 	+ vector_dot(x, axis_v);
	intersection_tmp->pos = vector_add(ray.origin,
		vector_scalar(ray.dir, eq.res[0]));
	intersection_tmp->normal_v = vector_normalize(vector_substract(
		vector_substract(intersection_tmp->pos, cone.pos),
		vector_scalar(vector_scalar(axis_v, b[0]), 1 + (k * k))));
	if (cone.height <= 0)
		return (1);
	if ((b[0] > 0 && b[0] < cone.height) || (b[1] > 0 && b[1] < cone.height))
		if (b[0] > 0 && b[0] < cone.height)
			return (1);
	return (0);
}

__host__ __device__ static int		get_cone(t_cone cone, t_ray ray,
	t_intersection *intersection_tmp)
{
	t_vec3d axis_v;
	t_vec3d	normal;
	t_vec3d x;
	t_eq		eq;
	double	k;

	if (intersection_tmp->id == cone.id)
		return (0);
	normal = vector_normalize(vector_calculate(cone.pos, cone.up));
	x = vector_calculate(cone.pos, ray.origin);
	k = cone.half_angle;
	eq.a = vector_dot(ray.dir, ray.dir)
		- (1 + k * k) * pow(vector_dot(ray.dir, normal), 2);
	eq.b = 2 * (vector_dot(ray.dir, x)
			- (1 + k * k) * (vector_dot(ray.dir, normal) * vector_dot(x, normal)));
	eq.c = vector_dot(x, x)
		- (1 + k * k) * pow(vector_dot(x, normal), 2);
	second_degres(&eq);
	if(eq.res[0] != NOT_A_SOLUTION)
	{
		intersection_tmp->t = eq.res[0];
		x = vector_substract(ray.origin, cone.pos);
		axis_v = vector_normalize(vector_calculate(cone.pos, cone.up));
		if (limit_cone(cone, ray, intersection_tmp, axis_v, x, eq) == 1)
			return (1);
	}
	intersection_tmp->t = -1.0;
	return (0);
}

__host__ __device__ void			get_closest_cone(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.cones_len)
	{
		if (get_cone(world.cones[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->type = 'x';
				intersection->id = world.cones[i].id;
				intersection->t = intersection_tmp->t;
				intersection->reflection_coef = world.cones[i].reflection_coef;
				intersection->refraction_coef = world.cones[i].refraction_coef;
				intersection->transparence_coef = world.cones[i].transparence_coef;
				intersection->color = world.cones[i].color;
				intersection->chess = world.cones[i].chess;
				intersection->pos = intersection_tmp->pos;
				intersection->normal_v = intersection_tmp->normal_v;
			}
		}
		i++;
	}
}
