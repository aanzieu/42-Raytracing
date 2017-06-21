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
	#include <rt.h>
	#include <vectors.h>
	#include <gpu_rt.h>
}

__host__ __device__ t_vec3d	get_normal_cone(t_cone cone, t_ray ray, t_intersection intersection)
{
	t_vec3d axis_v;
	t_vec3d	normal_v;
	t_vec3d	x;
	double	m;
	double	k;

	k = tan(deg_to_radians(cone.half_angle));
	x = vector_substract(ray.origin, cone.pos);
	axis_v = vector_normalize(vector_calculate(cone.pos, cone.up));
	m = vector_dot(ray.dir, axis_v) * intersection.t + vector_dot(x, axis_v);
	normal_v = vector_normalize(
				vector_substract(
					vector_substract(
						intersection.pos,
						cone.pos),
					vector_scalar(
						vector_scalar(
							axis_v,
							m),
						1 + (k * k))));
	return (normal_v);
}

__host__ __device__ void	get_determinant_cone(t_cone cone, t_camera camera, t_ray ray,
														t_2deg *equation)
{
	t_vec3d	normal;
	t_vec3d	x;
	double	k;

	normal = vector_normalize(vector_calculate(cone.pos,
														cone.up));
	x = vector_substract(ray.origin, cone.pos);
	k = tan(deg_to_radians(cone.half_angle));
	equation->a = vector_dot(ray.dir, ray.dir) - (1 + k * k) *
										pow(vector_dot(ray.dir, normal), 2);
	equation->b = 2 * (vector_dot(ray.dir, x) - (1 + k * k) *
						(vector_dot(ray.dir, normal) * vector_dot(x, normal)));
	equation->c = vector_dot(x, x) - (1 + k * k) *
							pow(vector_dot(x, normal), 2);
	equation->det = pow(equation->b, 2) - (4 * (equation->a) * (equation->c));
}

__host__ __device__ int		get_cone(t_cone cone, t_camera camera, t_ray ray,
									t_intersection *intersection_tmp)
{
	t_2deg	equation;
	double	t1;
	double	t2;

	get_determinant_cone(cone, camera, ray, &equation);
	if (equation.det >= 0)
	{
		t1 = ((-1) * equation.b + sqrt(equation.det)) / (2 * equation.a);
		t2 = ((-1) * equation.b - sqrt(equation.det)) / (2 * equation.a);
		if (t1 <= t2 && t1 > 0.0000001)
		{
			intersection_tmp->t = t1;
			intersection_tmp->type = 'x';
			return (1);
		}
		else if (t2 > 0.0000001)
		{
			intersection_tmp->t = t2;
			intersection_tmp->type = 'x';
			return (1);
		}
	}
	return (0);
}

__host__ __device__ void	get_closest_cone(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.cones_len)
	{
		if (get_cone(world.cones[i], world.camera, ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflexion_coef = world.cones[i].reflexion_coef;
				intersection->color = &world.cones[i].color;
				intersection->pos = vector_add(ray.origin,
					vector_scalar(ray.dir, intersection_tmp->t));
				intersection->normal_v = get_normal_cone(world.cones[i], ray,
														*intersection);
			}
		}
		i++;
	}
}
