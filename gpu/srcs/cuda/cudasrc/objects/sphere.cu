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

/*
**	On envoie le rayon et la structure qui contient la sphere et la fonction
**	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
**	avec la sphere
*/

__host__ __device__ double			get_sphere(t_sphere sphere,
		t_ray ray, t_intersection *intersection_tmp)
{
	t_vec3d	x;
	t_eq	eq;

	if (sphere.id == intersection_tmp->id)
		return (0);
	x = vector_calculate(sphere.pos, ray.origin);
	eq.a = vector_dot(ray.dir, ray.dir);
	eq.b = 2 * vector_dot(ray.dir, x);
	eq.c = vector_dot(x, x) - pow(sphere.radius, 2);
	second_degres(&eq);
	if(eq.res[0] != NOT_A_SOLUTION)
	{
		// tfar = eq.res[1] < eq.res[2] ? eq.res[2] : eq.res[1];
		// printf("%f\n", sphere.transparence_coef);
		intersection_tmp->id = sphere.id;
		intersection_tmp->t = eq.res[0];
		// intersection_tmp->t1 = eq.res[0];//tnear; //intersection_tmp->t;
		// intersection_tmp->t2 = eq.res[1];//tfar;
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
		if (get_sphere(world.spheres[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->type = 's';
				intersection->t = intersection_tmp->t;
				intersection->id = world.spheres[i].id;
				intersection->id_save = world.spheres[i].id;
				intersection->reflection_coef = world.spheres[i].reflection_coef;
				intersection->refraction_coef = world.spheres[i].refraction_coef;
				intersection->transparence_coef = world.spheres[i].transparence_coef;
				intersection->color = world.spheres[i].color;
				intersection->chess = world.spheres[i].chess;
				intersection->pos = vector_add(ray.origin, vector_scalar(ray.dir,
					intersection_tmp->t));
				intersection->normal_v = vector_normalize(
					vector_calculate(world.spheres[i].pos, intersection->pos));
			}
		}
		i++;
	}
}
