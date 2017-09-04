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

//
// __host__ __device__ t_vec3d	get_normal_cylinder(t_cylinder cylinder, t_ray ray,
// 												t_intersection intersection)
// {
// 	t_vec3d axis_v;
// 	t_vec3d	normal_v;
// 	t_vec3d	x;
// 	double	m;
//
// 	x = vector_substract(ray.origin, cylinder.pos);
// 	axis_v = vector_normalize(vector_calculate(cylinder.pos, cylinder.up));
// 	m = vector_dot(ray.dir, axis_v) * intersection.t + vector_dot(x, axis_v);
// 	normal_v = vector_normalize(
// 		vector_substract(
// 		vector_substract(intersection.pos, cylinder.pos),
// 					vector_scalar(axis_v, m)));
// 	return (normal_v);
// }
//
//
// __host__ __device__ int 	happend_cap(t_cylinder cylinder, t_ray ray, t_eq eq,
// 	t_intersection *intersection_tmp, t_vec3d normal_v, t_vec3d x)
// {
// 	double type;
//
// 	if (eq.res[1] > eq.res[2] && eq.res[2] > 0)
// 		eq.res[1] = eq.res[2];
// 	if (eq.res[1] < 0)
// 	{
// 	 	intersection_tmp->t = -1.0;
// 		return (-1);
// 	}
// 	type = inter_caps(cylinder, ray, eq.res);
// 	intersection_tmp->color = cylinder.color;
// 	if (eq.res[1] < 0 || type < 0)
// 	{
// 	 	intersection_tmp->t = -1.0;
// 		return (-1);
// 	}
// 	intersection_tmp->pos = vector_add(ray.origin, vector_scalar(ray.dir, type == 1 ? eq.res[1] : eq.res[2]));
// 	intersection_tmp->t = type == 1 ? eq.res[2] : eq.res[1];
// 	if (type == 1)
// 		intersection_tmp->normal_v = get_normal_cylinder(cylinder, ray, *intersection_tmp);
// 	else
// 		intersection_tmp->normal_v = vector_dot(ray.dir, normal_v) > 0 ? vector_scalar(normal_v, -1) : normal_v;
// 	return (1);
// }
//
// __host__ __device__ int 	limit_cylinder2(t_cylinder cylinder, t_ray ray,
// 	t_eq eq, t_intersection *intersection_tmp, t_vec3d normal_v, t_vec3d x)
// {
// 	double m1, m2, m3, maxm;
// 	t_plane p1, p2;
// 	t_intersection test;
// 	t_vec3d axis_v;
//
// 	maxm = cylinder.height;
// 	axis_v = vector_normalize(vector_calculate(cylinder.pos, cylinder.up));
// 	eq.res[1] = eq.res[1] > eq.res[2] && eq.res[2] > 0 ? eq.res[2] : eq.res[1];
// 	m1 = vector_dot(ray.dir, axis_v) * eq.res[1] + vector_dot(x, axis_v);
// 	m2 = vector_dot(ray.dir, axis_v) * eq.res[2] + vector_dot(x, axis_v);
// 	// if (m1 > 0 && m1 < cylinder.height)// && )
// 	// 	m3 = m1;
// 	// if (m2 < m3 && m2 > 0 && m2 < cylinder.height)
// 	// 	m3 = m2;
//
// 	// if (m3 < cylinder.height)
// 	// {
// 	// 	intersection_tmp->t = eq.res[0];
// 	// 	intersection_tmp->pos = vector_add(ray.origin, vector_scalar(ray.dir, intersection_tmp->t));
// 	// 	intersection_tmp->normal_v = get_normal_cylinder(cylinder, ray, *intersection_tmp);
// 	// 	return (1);
// 	// }
// 	m1 = m1 < m2 ? m1 : m2;
// 	if (m1 < 0 || m1 > cylinder.height)// || m2 < 0 || m2 > cylinder.height)
// 	{
// 	//		(C,-V) and the other by (C+V*maxm,V)
// 		p1.pos = cylinder.pos;
// 		p2.pos = vector_add(cylinder.pos, vector_scalar(normal_v, cylinder.height));
// 		p1.up = cylinder.up;//vector_scalar(normal_v, -1);
// 		p2.up = cylinder.up;//normal_v;
// 		test.t = DBL_MAX;
// 		test.id = intersection.id;
// 		if ((get_plane(p2, ray, &test) == 1))// || (get_plane2(p2, ray, &test) == 1))
// 		{
// 			intersection_tmp->t = test.t;
// 			intersection_tmp->normal_v = test.normal_v;
// 			return (1);
// 		}
// 	}
// 	else
// 	{
// 		intersection_tmp->t = eq.res[0];
// 		intersection_tmp->pos = vector_add(ray.origin, vector_scalar(ray.dir, intersection_tmp->t));
// 		intersection_tmp->normal_v = get_normal_cylinder(cylinder, ray, *intersection_tmp);
// 		return (1);
// 	}
// 	return (-1);
// }

__host__ __device__ int		limit_cylinder(t_cylinder cylinder, t_ray ray,
		t_intersection *intersection_tmp, t_vec3d axis, t_vec3d x, t_eq eq)
{
	double b[2];

	b[0] = vector_dot(ray.dir, axis) * eq.res[0] + vector_dot(x, axis);
	b[1] = vector_dot(ray.dir, axis) * eq.res[1] + vector_dot(x, axis);
	if ((b[0] > 0 && b[0] < cylinder.height)
		|| (b[1] > 0 && b[1] < cylinder.height))
	{
		if (b[0] > 0 && b[0] < cylinder.height)
		intersection_tmp->normal_v = vector_normalize(
			vector_substract(vector_substract(
					intersection_tmp->pos, cylinder.pos), vector_scalar(axis, b[0])));
		else
			if (b[1] > 0 && b[1] < cylinder.height)
				intersection_tmp->normal_v = (t_vec3d){0, 0, 0};
		if (cylinder.refraction_coef != 0 || cylinder.reflection_coef != 0)
			intersection_tmp->id = cylinder.id;
		return (1);
	}
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
				intersection->t = intersection_tmp->t;
				intersection->type = 'c';
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
