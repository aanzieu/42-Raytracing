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

__host__ __device__ t_vec3d	get_normal_cube(t_cube cu, t_ray ray,
	t_intersection intersection)
{
	t_vec3d		normal;
	t_vec3d		c;
	t_vec3d		p;
	t_vec3d		d;
	double		bias;
	t_vec3d		vmin = cu.min;//(t_vec3d){-1, -1, -1};//cu.vec1;
	t_vec3d		vmax = cu.max;//(t_vec3d){1, 1, 1};//cu.vec2;

  c = vector_scalar(vector_add(vmin, vmax), 0.5f);
  p = vector_substract(intersection.pos, c);
  d = vector_scalar(vector_substract(vmin, vmax), 0.5f);
  bias = 1.000001f;

	normal.x = (p.x / fabs(d.x) * bias);
	normal.y = (p.y / fabs(d.y) * bias);
	normal.z = (p.z / fabs(d.z) * bias);
	normal = vector_normalize(normal);
//	normal = (t_vec3d){0, 0, 1};
	return (normal);
}

__host__ __device__ int			get_cube(t_cube cu, t_ray ray,
	t_intersection *intersection_tmp)
{
	t_vec3d		bounds[2];
	int				sign[3];
	t_vec3d		invdir;
	double		tmin, tmax, tymin, tymax, tzmin, tzmax, t;

	if (intersection_tmp->id == cu.id)
		return (-1);
	invdir.x = 1.0 / ray.dir.x;
	invdir.y = 1.0 / ray.dir.y;
	invdir.z = 1.0 / ray.dir.z;
	bounds[0] = cu.min;//(t_vec3d){-1, -1, -1};//cu.vec1;
	bounds[1] = cu.max;//(t_vec3d){1, 1, 1};//cu.vec2;
	sign[0] = (invdir.x < 0) ? 1 : 0;
	sign[1] = (invdir.y < 0) ? 1 : 0;
	sign[2] = (invdir.z < 0) ? 1 : 0;
	tmin = (bounds[sign[0]].x - ray.origin.x) * invdir.x;
	tmax = (bounds[1 - sign[0]].x - ray.origin.x) * invdir.x;
	tymin = (bounds[sign[1]].y - ray.origin.y) * invdir.y;
	tymax = (bounds[1 - sign[1]].y - ray.origin.y) * invdir.y;
	if ((tmin > tymax) || (tymin > tmax))
			return (-1);
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (bounds[sign[2]].z - ray.origin.z) * invdir.z;
	tzmax = (bounds[1 - sign[2]].z - ray.origin.z) * invdir.z;
	if ((tmin > tzmax) || (tzmin > tmax))
		return (-1);
	if (tzmin > tmin)
	tmin = tzmin;
	if (tzmax < tmax)
	tmax = tzmax;
	t = tmin;
	if (t <= 1.00000001)
	{
			t = tmax;
			if (t <= 1.00000001)
				return (-1);
	}
	intersection_tmp->t = t;
	return (1);
}

__host__ __device__ void	get_closest_cube(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
//printf("%f %f %f\n", world.cube[i].min.x, world.cube[i].min.y, world.cube[i].min.z);
	while (i < world.cubes_len)
	{
		if (get_cube(world.cubes[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = 'b';
				intersection->reflection_coef = world.cubes[i].reflection_coef;
				intersection->reflection_coef = world.cubes[i].reflection_coef;
				intersection->transparence_coef = world.cubes[i].transparence_coef;
				intersection->id = intersection_tmp->id;
				intersection->color = world.cubes[i].color;
				intersection->chess = world.cubes[i].chess;
				intersection->pos =
					vector_add(ray.origin, vector_scalar(ray.dir, intersection->t));
				intersection->normal_v =
					get_normal_cube(world.cubes[i], ray, *intersection);
			}
		}
		i++;
	}
}
