/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.cu                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:29:36 by huweber           #+#    #+#             */
/*   Updated: 2017/08/24 18:02:22 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
#include "../../../../includes/rt.h"
#include "../../cudaheader/gpu_rt.h"
#include <vectors.h>
#include <equation.h>
#include <float.h>
#include <math.h>
}

__host__ __device__ int	get_cube(t_cube cu, t_ray ray,
								 t_intersection *intersection_tmp)
{
	// double bound[2];
	//
	(void)cu;
	(void)ray;
	(void)intersection_tmp;
	return (0);
}

__host__ __device__ void	get_closest_cube(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.cubes_len)
	{
		if (get_cube(world.cubes[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = 't';
				intersection->reflection_coef = world.cubes[i].reflection_coef;
				intersection->reflection_coef = world.cubes[i].reflection_coef;
				intersection->transparence_coef = world.cubes[i].transparence_coef;
				intersection->id = intersection_tmp->id;
				intersection->color = world.cubes[i].color;
				intersection->chess = world.cubes[i].chess;
				intersection->pos =
					vector_add(ray.origin, vector_scalar(ray.dir, intersection->t));
				intersection->normal_v = intersection_tmp->normal_v;
			}
		}
		i++;
	}
}
