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

__host__ __device__ t_vec3d		get_normal_cone(t_cone cone,
		t_intersection *intersection_tmp)
{
	t_vec3d axis_v;
	t_vec3d	normal_v;
	t_vec3d	x;
	double	k;

	k = cone.half_angle;
	axis_v = vector_substract(intersection_tmp->pos, \
		vector_add(cone.pos, cone.up));
	axis_v = vector_scalar(cone.up, \
		vector_dot(cone.up, axis_v) / vector_dot(cone.up, cone.up));
	x = vector_add(axis_v, cone.up);
	normal_v = vector_substract(intersection_tmp->pos, cone.pos);
	x = vector_scalar(vector_normalize(x), vector_length(normal_v) / cos(k));
	normal_v = vector_normalize(vector_substract(normal_v, x));
	return (normal_v);
}

__host__ __device__ static double	limit_cone_next(t_eq eq,\
		t_cone cone, t_ray ray, t_intersection *intersection_tmp)
{
	t_vec3d pos[2];
	t_vec3d lim[2];

	pos[0] = vector_add(ray.origin, vector_scalar(ray.dir, eq.res[0]));
	pos[1] = vector_add(cone.pos, vector_scalar(cone.up, cone.height));
	lim[0] = vector_substract(pos[0], cone.pos);
	lim[1] = vector_substract(pos[0], pos[1]);
	if (vector_dot(cone.up, lim[0]) > SURFACE_TOLERANCE \
		&& vector_dot(cone.up, lim[1]) < SURFACE_TOLERANCE)
		return (eq.res[0]);
	return (-1);
}

__host__ __device__ static int limit_cone(t_eq eq, t_cone cone,\
		t_ray ray, t_intersection *intersection_tmp)
{
	double	t_save;

	if (eq.res[1] > eq.res[0])
		eq.res[1] = eq.res[0];
	t_save = eq.res[1];
	if (cone.height > 0)
		if ((eq.res[1] = limit_cone_next(eq, cone, ray, intersection_tmp)) == -1)
			return (-1);
	intersection_tmp->t = eq.res[1] == t_save ? eq.res[0] : eq.res[1];
	intersection_tmp->pos = vector_add(ray.origin,
		vector_scalar(ray.dir, intersection_tmp->t));
	intersection_tmp->normal_v = get_normal_cone(cone, intersection_tmp);
	return (1);
}

__host__ __device__ static int		get_cone(t_cone cone, t_ray ray,\
	t_intersection *intersection_tmp)
{
	t_eq		eq;
	t_vec3d x;
	t_vec3d axis_v[2];
	double 	k;

	if (intersection_tmp->id == cone.id)
		return (0);

	axis_v[0] = vector_substract(ray.origin, vector_add(cone.pos, cone.up));
	axis_v[1] = vector_cross(axis_v[0], cone.up);
	axis_v[0] = vector_cross(ray.dir, cone.up);
	x = vector_substract(ray.origin, cone.pos);
	k = cone.half_angle;
	eq.a = pow(cos(k), 2) * vector_dot(axis_v[0], axis_v[0]) - \
		pow(sin(k), 2) * pow(vector_dot(ray.dir, cone.up), 2);
	eq.b = pow(cos(k), 2) * vector_dot(axis_v[0], axis_v[1]) * 2 - \
		2 * pow(sin(k), 2) * vector_dot(ray.dir, cone.up) * vector_dot(x, cone.up);
	eq.c = pow(cos(k), 2) * vector_dot(axis_v[1], axis_v[1]) - \
		pow(sin(k), 2) * pow(vector_dot(x, cone.up), 2);
	second_degres(&eq);
	if(eq.res[0] != NOT_A_SOLUTION)
		return (limit_cone(eq, cone, ray, intersection_tmp));
	intersection_tmp->t = -1.0;
	return (0);
}

__host__ __device__ void			get_closest_cone(t_world world, t_ray ray,\
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
				intersection->id_save = world.cones[i].id;
				intersection->t = intersection_tmp->t;
				intersection->reflection_coef = world.cones[i].reflection_coef;
				intersection->refraction_coef = world.cones[i].refraction_coef;
				intersection->transparence_coef = world.cones[i].transparence_coef;
				intersection->color = world.cones[i].color;
				intersection->chess = world.cones[i].chess;
				intersection->pos = intersection_tmp->pos;
				intersection->normal_v = intersection_tmp->normal_v;
				if(world.on == 1){
				apply_noise_dist(world, intersection, world.cones[i].perlin);}
			}
		}
		i++;
	}
}