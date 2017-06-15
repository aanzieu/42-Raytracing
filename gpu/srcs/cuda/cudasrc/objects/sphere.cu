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
	#include "../../../../includes/rtv1.h"
	#include "../../../../includes/vectors.h"
}

__host__ __device__ t_vec3d	get_normal_sphere(t_sphere sphere, t_intersection intersection)
{
	t_vec3d normal;

	normal = vector_normalize(vector_calculate(sphere.pos,
															intersection.pos));
	return (normal);
}

__host__ __device__ void	get_determinant_sphere(t_sphere sphere, t_ray ray, t_2deg *equation)
{
	equation->a = pow(ray.dir.x, 2) + pow(ray.dir.y, 2) + pow(ray.dir.z, 2);
	equation->b = 2 * (ray.dir.x * (ray.origin.x - sphere.pos.x) +
				ray.dir.y * (ray.origin.y - sphere.pos.y) +
				ray.dir.z * (ray.origin.z - sphere.pos.z));
	equation->c = (pow((ray.origin.x - sphere.pos.x), 2) +
			pow((ray.origin.y - sphere.pos.y), 2) +
			pow((ray.origin.z - sphere.pos.z), 2)) -
			pow(sphere.radius, 2);
	equation->det = pow(equation->b, 2) - (4 * (equation->a) * (equation->c));
}

/*
**	On envoie le rayon et la structure qui contient la sphere et la fonction
**	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
**	avec la sphere
*/

__host__ __device__ double		get_sphere(t_sphere sphere, t_ray ray, t_intersection *intersection_tmp)
{
	t_2deg	equation;
	float	t1;
	float	t2;

	get_determinant_sphere(sphere, ray, &equation);
	if (equation.det >= 0)
	{
		t1 = ((-1) * equation.b + sqrt(equation.det)) / (2 * equation.a);
		t2 = ((-1) * equation.b - sqrt(equation.det)) / (2 * equation.a);
		if (t1 <= t2 && t1 > 0.0000001)
		{
			intersection_tmp->t = t1;
			intersection_tmp->type = 's';
			return (1);
		}
		else if (t2 > 0.0000001)
		{
			intersection_tmp->t = t2;
			intersection_tmp->type = 's';
			return (1);
		}
	}
	return (0);
}

__host__ __device__ double	get_closest_sphere(t_world world, t_ray ray,
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
				intersection->pos = vector_add(ray.origin,
					vector_scalar(ray.dir, intersection_tmp->t));
				intersection->normal_v = get_normal_sphere(world.spheres[i],
														*intersection);
			}
		}
		i++;		
	}
	return (0);
}
