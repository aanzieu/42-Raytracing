/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobius.c                                           :+:      :+:    :+:   */
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

__host__ __device__ static void	get_normal_mobius(t_intersection *inter,
		t_mobius m, t_ray ray)
{
	t_vec3d ret;
	t_vec3d real;

	real = vector_substract(inter->pos, m.pos);
	ret.x = -2 * m.radius * real.z + 2 * real.x * real.y - 4 * real.x * real.z;
	ret.y = -(m.radius * m.radius) + real.x * real.x + 3 * real.y * real.y - 4
		* real.y * real.z + real.z * real.z;
	ret.z = -2 * m.radius * real.x - 2 * real.x * real.x - 2 * real.y * real.y
		+ 2 * real.y * real.z;
	inter->normal_v = vector_normalize(ret);;
}

__host__ __device__ static int	get_mobius(t_mobius m, t_ray ray,
		t_intersection *intersection_tmp)
{
	double	s[4];
	t_eq	d;

	d.a = m.radius;
	d.b = ray.origin.x;
	d.c = ray.dir.x;
	d.d = ray.origin.y;
	d.e = ray.dir.y;
	d.f = ray.origin.z;
	d.g = ray.dir.z;

	s[3] = d.c * d.c * d.e + d.e * d.e * d.e - 2 * d.c * d.c * d.g - 2 * d.e *
			d.e * d.g + d.e * d.g * d.g;
	s[0] = (d.b * d.b * d.d + d.d * d.d * d.d - 2 * d.b * d.b *
			d.f - 2 * d.d * d.d * d.f + d.d * d.f * d.f - 2 * d.b * d.f * d.a -
			d.d * d.a * d.a) / s[3];
	s[1] = (d.e * d.b * d.b - 2 * d.g * d.b * d.b + 2 * d.c * d.b * d.d + 3 *
			d.e * d.d * d.d - 2 * d.g * d.d * d.d - 4 * d.c * d.b * d.f - 4 *
			d.e * d.d * d.f + 2 * d.g * d.d * d.f + d.e * d.f * d.f - 2 * d.g *
			d.b * d.a - 2 * d.c * d.f * d.a - d.e * d.a * d.a) / s[3];
	s[2] = (2 * d.c * d.e * d.b - 4 * d.c * d.g * d.b + d.c * d.c * d.d + 3 *
			d.e * d.e * d.d - 4 * d.e * d.g * d.d + d.g * d.g * d.d - 2 * d.c *
			d.c * d.f - 2 * d.e * d.e * d.f + 2 * d.e * d.g * d.f - 2 * d.c *
			d.g * d.a) / s[3];
	d.res[0] = solver_n_degree(s, 4, m, ray);
	if(d.res[0] != NOT_A_SOLUTION)
	{
		intersection_tmp->t = d.res[0];
//		intersection_tmp->type = 'm';
		return(1);
	}
	intersection_tmp->t = -1.0;
	return(0);
}

__host__ __device__ void		get_closest_mobius(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.mobius_len)
	{
		if (get_mobius(world.mobius[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t
					&& intersection_tmp->t != -1)
			{
				intersection->type = 'm';
				intersection->pos = vector_add(ray.origin,
						vector_scalar(ray.dir, intersection_tmp->t));
				intersection->t = intersection_tmp->t;
		
				intersection->id_save = world.mobius[i].id;
				intersection->id = world.mobius[i].id;				
				intersection->reflection_coef = world.mobius[i].reflection_coef;
				intersection->refraction_coef = world.mobius[i].refraction_coef;
				intersection->transparence_coef = world.mobius[i].transparence_coef;
				intersection->color = world.mobius[i].color;
				get_normal_mobius(intersection, world.mobius[i], ray);
			}
		}
		i++;
	}
}
