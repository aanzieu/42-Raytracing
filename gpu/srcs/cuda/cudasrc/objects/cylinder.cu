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
}
#include <float.h>

__host__ __device__ t_vec3d	get_normal_cylinder(t_cylinder cylinder, t_camera camera, t_ray ray,
												t_intersection intersection)
{
	t_vec3d axis_v;
	t_vec3d	normal_v;
	t_vec3d	x;
	double	m;

	x = vector_substract(ray.origin, cylinder.pos);
	axis_v = vector_normalize(vector_calculate(cylinder.pos, cylinder.up));
	m = vector_dot(ray.dir, axis_v) * intersection.t + vector_dot(x, axis_v);
	normal_v = vector_normalize(
				vector_substract(
					vector_substract(
						intersection.pos,
						cylinder.pos),
					vector_scalar(
						axis_v,
						m)));
	return (normal_v);
}

__host__ __device__ void	get_determinant_cylinder(t_cylinder cylinder, t_camera camera,
												t_ray ray, t_2deg *equation)
{
	t_vec3d	normal_v;
	t_vec3d	x;

	normal_v = vector_normalize(vector_calculate(cylinder.pos, cylinder.up));
	x = vector_substract(ray.origin, cylinder.pos);
	equation->a = vector_dot(ray.dir, ray.dir) -
		pow(vector_dot(ray.dir, normal_v), 2);
	equation->b = 2 * (vector_dot(ray.dir, x) -
		(vector_dot(ray.dir, normal_v) * vector_dot(x, normal_v)));
	equation->c = vector_dot(x, x) -
		pow(vector_dot(x, normal_v), 2) - pow(cylinder.radius, 2);
	equation->det = pow(equation->b, 2) - (4 * (equation->a) * (equation->c));
}

__host__ __device__ int		get_cylinder(t_cylinder cylinder, t_camera camera, t_ray ray,
											t_intersection *intersection_tmp)
{
	t_2deg	equation;
	double	t1;
	double	t2;

	get_determinant_cylinder(cylinder, camera, ray, &equation);
	if (equation.det >= 0)
	{
		t1 = ((-1) * equation.b + sqrt(equation.det)) / (2 * equation.a);
		t2 = ((-1) * equation.b - sqrt(equation.det)) / (2 * equation.a);
		if (t1 <= t2 && t1 > 0.0000001)
		{
			intersection_tmp->t = t1;
			intersection_tmp->type = 'c';
			return (1);
		}
		else if (t2 > 0.0000001)
		{
			intersection_tmp->t = t2;
			intersection_tmp->type = 'c';
			return (1);
		}
	}
	return (0);
}

__host__ __device__ void	get_closest_cylinder(t_world world, t_ray ray,
				t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.cylinders_len)
	{
		if (get_cylinder(world.cylinders[i], world.camera, ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->color = &world.cylinders[i].color;
				intersection->pos = vector_add(ray.origin,
					vector_scalar(ray.dir, intersection->t));
				intersection->normal_v = get_normal_cylinder(world.cylinders[i],
											world.camera, ray, *intersection);
			}
		}
		i++;
	}
}
