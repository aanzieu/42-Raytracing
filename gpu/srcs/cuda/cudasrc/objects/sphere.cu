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
	#include <gpu_rt.h>
	#include <vectors.h>
	#include <equation.h>
}

__host__ __device__ static t_vec3d			get_normal_sphere(t_sphere sphere,
		t_intersection intersection)
{
	t_vec3d normal;

	normal = vector_normalize(vector_calculate(sphere.pos, intersection.pos));
	return (normal);
}

/*
**	On envoie le rayon et la structure qui contient la sphere et la fonction
**	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
**	avec la sphere
*/

__host__ __device__ static double			get_sphere(t_sphere sphere,
		t_ray ray, t_intersection *intersection_tmp)
{
	t_vec3d	x;
	t_eq	eq;

	x = vector_calculate(sphere.pos, ray.origin);
	eq.a = vector_dot(ray.dir, ray.dir);
	eq.b = 2 * vector_dot(ray.dir, x);
	eq.c = vector_dot(x, x) - pow(sphere.radius, 2);
	eq.res = second_degres(eq.a, eq.b, eq.c);
	if(eq.res != NOT_A_SOLUTION && intersection_tmp->id != sphere.id)
	{
		intersection_tmp->t = eq.res;
		intersection_tmp->type = 's';
		if (sphere.refraxion_coef != 0)
			intersection_tmp->id = sphere.id;
		return (1);
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
		if (get_sphere(world.spheres[i], ray, intersection_tmp) == 1)// && intersection_tmp->id != intersection->id)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->id = intersection_tmp->id;
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflexion_coef = world.spheres[i].reflexion_coef;
				intersection->refraxion_coef = world.spheres[i].refraxion_coef;
				intersection->color = &world.spheres[i].color;
				intersection->pos = vector_add(ray.origin, vector_scalar(ray.dir,
							intersection_tmp->t));
				intersection->normal_v = get_normal_sphere(world.spheres[i],
														*intersection);
			}
		}
		i++;
	}
}
