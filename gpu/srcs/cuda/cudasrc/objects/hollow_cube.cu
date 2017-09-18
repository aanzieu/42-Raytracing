/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_cube.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:29:36 by huweber           #+#    #+#             */
/*   Updated: 2017/08/23 19:29:39 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <rt.h>
	#include "gpu_rt.h"
	#include <vectors.h>
}

/*
**	On envoie le rayon et la structure qui contient le h_cube et la fonction
**	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
**	avec le plan
*/

__host__ __device__ t_vec3d get_normal_hollow_cube(t_intersection *intersection,
		t_h_cube cu)
{
  t_vec3d norm;
  t_vec3d pos;

  pos = vector_substract(intersection->pos, cu.pos);
	norm.x = 4. * pow(pos.x, 3) - 10. * pos.x;
  norm.y = 4. * pow(pos.y, 3) - 10. * pos.y;
  norm.z = 4. * pow(pos.z, 3) - 10. * pos.z;
	return (vector_normalize(norm));
}

__host__ __device__ int	get_hollow_cube(t_h_cube cu, t_ray ray,
		t_intersection *intersection_tmp)
{
	double	a[5];
	double	roots[4];
	double	res = DBL_MAX;
	double	nb_roots = 0;
	int			i = 0;

	if (intersection_tmp->id == cu.id)
		return (0);
	ray.origin = vector_calculate(cu.pos, ray.origin);
  a[0] = (pow(ray.dir.x, 4) + pow(ray.dir.y, 4) + pow(ray.dir.z, 4));
  a[1] = (4 * (pow(ray.dir.x, 3) * ray.origin.x + pow(ray.dir.y, 3)
          * ray.origin.y + pow(ray.dir.z, 3) * ray.origin.z));
  a[2] = (6 * (pow(ray.dir.x, 2) * pow(ray.origin.x, 2) + pow(ray.dir.y, 2)
          * pow(ray.origin.y, 2) + pow(ray.dir.z, 2) * pow(ray.origin.z, 2))
          - 5 * vector_magnitude(ray.dir));
  a[3] = (4 * (pow(ray.origin.x, 3) * ray.dir.x + pow(ray.origin.y, 3)
          * ray.dir.y + pow(ray.origin.z, 3) * ray.dir.z)
          - 10 * (vector_dot(ray.dir, ray.origin)));
  a[4] = (pow(ray.origin.x, 4) + pow(ray.origin.y, 4)
          + pow(ray.origin.z, 4) - 5 * (vector_magnitude(ray.origin))  + 11.8);
	if ((nb_roots = solve_quartic(a, roots)) > 0)
	{
		while (i < nb_roots)
		{
			if (roots[i] < res && roots[i] > 0.1)//SURFACE_TOLERANCE)
				res = roots[i];
			i++;
		}
		if (res != DBL_MAX)
		{
			intersection_tmp->t = res;
			return (1);
		}
	}
	return (0);
}

__host__ __device__ void	get_closest_hollow_cube(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.h_cubes_len)
	{
		if (get_hollow_cube(world.h_cubes[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->id = world.h_cubes[i].id;
				intersection->id_save = world.h_cubes[i].id;
				intersection->t = intersection_tmp->t;
				intersection->type = 'u';
				intersection->reflection_coef = world.h_cubes[i].reflection_coef;
				intersection->reflection_coef = world.h_cubes[i].reflection_coef;
				intersection->transparence_coef = world.h_cubes[i].transparence_coef;
				intersection->color = world.h_cubes[i].color;
				intersection->chess = world.h_cubes[i].chess;
				intersection->pos =
					vector_add(ray.origin, vector_scalar(ray.dir, intersection->t));
				intersection->normal_v =
					get_normal_hollow_cube(intersection, world.h_cubes[i]);
			}
		}
		i++;
	}
}
