/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/04/26 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <rt.h>
	#include "gpu_rt.h"
	#include <vectors.h>
}

__host__ __device__ t_vec3d	get_normal_sphere(t_sphere sphere, t_intersection intersection)
{
	t_vec3d normal;

	normal = vector_normalize(vector_calculate(sphere.pos,
															intersection.pos));
	return (normal);
}

__host__ __device__ void	get_determinant_sphere(t_sphere s, t_ray r, t_2deg *equation)
{
	t_vec3d x;

	x = vector_calculate(s.pos, r.origin);
	equation->a = vector_dot(r.dir, r.dir);
	equation->b = 2 * vector_dot(r.dir, x);
	equation->c = vector_dot(x, x) - pow(s.radius, 2);
	equation->det = pow(equation->b, 2) - (4 * (equation->a) * (equation->c));
}

/*
**	On envoie le rayon et la structure qui contient la sphere et la fonction
**	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
**	avec la sphere
*/

__host__ __device__ static int	get_sphere(t_sphere sphere, t_ray ray, t_intersection *intersection_tmp)
{
	t_2deg	equation;
	double	t1;
	double	t2;

	get_determinant_sphere(sphere, ray, &equation);
	if (equation.det >= 0)
	{
		t1 = ((-1) * equation.b + sqrt(equation.det)) / (2 * equation.a);
		t2 = ((-1) * equation.b - sqrt(equation.det)) / (2 * equation.a);
		if (t1 <= t2 && t1 > 0)
		{
			intersection_tmp->t = t1;
			intersection_tmp->type = 's';
			return (1);
		}
		else if (t2 > 0)
		{
			intersection_tmp->t = t2;
			intersection_tmp->type = 's';
			return (1);
		}
	}
	return (0);
}

__host__ __device__ void	get_closest_sphere(t_world world, t_ray ray,
				t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.spheres_len)
	{
		if(get_sphere(world.spheres[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->color = &world.spheres[i].color;
				intersection->pos = vector_add(vector_scalar(ray.dir, intersection_tmp->t), ray.origin);
				intersection->normal_v = get_normal_sphere(world.spheres[i],
														*intersection);
			}
		}
		i++;		
	}
}
