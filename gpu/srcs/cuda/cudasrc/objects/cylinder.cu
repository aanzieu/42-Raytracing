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

__host__ __device__ static void		get_normal_cylinder(t_cylinder cylinder,\
		t_intersection *intersection_tmp)
{
	t_vec3d		pos;
	double		tmp;

	pos = vector_substract(intersection_tmp->pos,\
		vector_add(cylinder.pos, cylinder.up));
	tmp = vector_dot(cylinder.up, pos) / vector_dot(cylinder.up, cylinder.up);
	pos = vector_add(vector_add(cylinder.pos, cylinder.up),\
		vector_scalar(cylinder.up, tmp));
	intersection_tmp->normal_v = vector_normalize(\
		vector_substract(intersection_tmp->pos, pos));
}

__host__ __device__ static double	limit_cylinder_next(t_eq eq,\
		t_cylinder cyl, t_ray ray)
{
	t_vec3d pos[2];
	t_vec3d caps[2];

	pos[0] = vector_add(ray.origin, vector_scalar(ray.dir, eq.res[0]));
	pos[1] = vector_add(cyl.pos, vector_scalar(cyl.up, cyl.height));
	caps[0] = vector_substract(pos[0], cyl.pos);
	caps[1] = vector_substract(pos[0], pos[1]);
	if (vector_dot(cyl.up, caps[0]) > SURFACE_TOLERANCE\
		&& vector_dot(cyl.up, caps[1]) < SURFACE_TOLERANCE)
		return (eq.res[0]);
	eq.res[0] = ((vector_dot(cyl.up, cyl.pos) -\
				vector_dot(cyl.up, ray.origin)) / vector_dot(cyl.up, ray.dir));
	eq.res[1] = ((vector_dot(cyl.up, pos[1]) -\
				vector_dot(cyl.up, ray.origin)) / vector_dot(cyl.up, ray.dir));
	if (eq.res[0] < eq.res[1] && eq.res[0] > SURFACE_TOLERANCE)
	{
		pos[0] = vector_add(ray.origin, vector_scalar(ray.dir, eq.res[0]));
		caps[0] = vector_substract(pos[0], cyl.pos);
		if (sqrt(vector_dot(caps[0], caps[0])) < cyl.radius)
			return (eq.res[0]);
	}
	else if (eq.res[1] < eq.res[0] && eq.res[1] > SURFACE_TOLERANCE)
	{
		pos[0] = vector_add(ray.origin, vector_scalar(ray.dir, eq.res[1]));
		caps[1] = vector_substract(pos[0], pos[1]);
		if (sqrt(vector_dot(caps[1], caps[1])) < cyl.radius)
			return (eq.res[1]);
	}
	return (-1);
}
__host__ __device__ static int limit_cylinder(t_eq eq, t_cylinder cylinder,\
		t_ray ray, t_intersection *intersection_tmp)
{
	double	t_save;

	if (eq.res[1] > eq.res[0])
		eq.res[1] = eq.res[0];
	t_save = eq.res[1];
	if (cylinder.height > 0)
		if ((eq.res[1] = limit_cylinder_next(eq, cylinder, ray)) == -1)
			return (-1);
	intersection_tmp->t = eq.res[0] == t_save ? eq.res[1] : eq.res[0];
	intersection_tmp->pos = vector_add(ray.origin,
		vector_scalar(ray.dir, intersection_tmp->t));
	if (intersection_tmp->t == t_save)
		get_normal_cylinder(cylinder, intersection_tmp);
	else
		intersection_tmp->normal_v = (t_vec3d){0, 1, 0};
	return (1);
}
__host__ __device__ int		get_cylinder(t_world world, t_cylinder cylinder,\
		t_ray ray, t_intersection *intersection_tmp)
{
	t_eq		eq;
	t_vec3d x;
	t_vec3d axis_v[2];

 	if (intersection_tmp->id == cylinder.id)
		return (0);
	x = vector_substract(ray.origin, cylinder.pos);
	cylinder.up = vector_normalize(cylinder.up);
	axis_v[0] = vector_scalar(cylinder.up, vector_dot(ray.dir, cylinder.up));
	axis_v[0] = vector_substract(ray.dir, axis_v[0]);
	axis_v[1] = vector_scalar(cylinder.up, vector_dot(x, cylinder.up));
	axis_v[1] = vector_substract(x, axis_v[1]);
	eq.a = vector_dot(axis_v[0], axis_v[0]);
	eq.b = 2 * vector_dot(axis_v[0], axis_v[1]);
	eq.c = vector_dot(axis_v[1], axis_v[1]) - cylinder.radius * cylinder.radius;
	second_degres(&eq);
	if (eq.res[0] != NOT_A_SOLUTION)
		return (limit_cylinder(eq, cylinder, ray, intersection_tmp));
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
				apply_noise_dist(world, intersection, world.cylinders[i].perlin);
			}
		}
		i++;
	}
}
