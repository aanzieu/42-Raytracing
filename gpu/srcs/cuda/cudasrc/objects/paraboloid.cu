/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <rt.h>
	#include "gpu_rt.h"
	#include <vectors.h>
	#include <equation.h>
}

__host__ __device__ t_vec3d	get_normal_paraboloid(t_paraboloid para, t_ray ray,
	t_intersection intersection)
{
	t_vec3d	normal_v;
	t_vec3d	x;
	t_vec3d	v;
	double	m;

	x = vector_calculate(para.top, ray.origin);
	v = vector_normalize(para.normal);
	m = vector_dot(ray.dir, vector_scalar(v, intersection.t))
		+ vector_dot(x, v);
	normal_v = vector_normalize(vector_substract(vector_calculate(para.top, intersection.pos),
				vector_scalar(v, m + para.distance)));
	return (normal_v);
}

__host__ __device__ int		get_paraboloid(t_paraboloid para, t_ray ray,
									t_intersection *intersection_tmp)
{
	t_vec3d	x;
	t_vec3d	v;
	t_eq	eq;

	if (intersection_tmp->id == para.id)
		return (0);
	x = vector_calculate(para.top, ray.origin);
	v = vector_normalize(para.normal);
	eq.a = vector_dot(ray.dir, ray.dir)
		- (pow(vector_dot(ray.dir, v), 2));
	eq.b = 2 * (vector_dot(ray.dir, x)
			- (vector_dot(ray.dir, v)
				* ((vector_dot(x, v) + 2 * para.distance))));
	eq.c = vector_dot(x, x)
		- (vector_dot(x, v)
				* (vector_dot(x, v) + 4 * para.distance));
	second_degres(&eq);
	if(eq.res[0] != NOT_A_SOLUTION)
	{
		intersection_tmp->t = eq.res[0];
		return (1);
	}
//	intersection_tmp->t = -1.0;
	return (0);
}

__host__ __device__ void	get_closest_paraboloid(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.paraboloids_len)
	{
		if (get_paraboloid(world.paraboloids[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != 1)
			{
				intersection->t = intersection_tmp->t;
				intersection->id = world.paraboloids[i].id;
				intersection->id_save = world.paraboloids[i].id;
				intersection->type = 'b';
				intersection->reflection_coef = world.paraboloids[i].reflection_coef;
				intersection->refraction_coef = world.paraboloids[i].refraction_coef;
				intersection->transparence_coef = world.paraboloids[i].transparence_coef;
				intersection->color = world.paraboloids[i].color;
				intersection->chess = world.paraboloids[i].chess;
				intersection->pos = vector_add(ray.origin,
					vector_scalar(ray.dir, intersection_tmp->t));
				intersection->normal_v = get_normal_paraboloid(world.paraboloids[i], ray,
														*intersection);
				apply_noise_dist(world, intersection, world.paraboloids[i].perlin);
			}
		}
		i++;
	}
}
