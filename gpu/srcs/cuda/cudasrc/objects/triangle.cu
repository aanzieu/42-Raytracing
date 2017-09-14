/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:00:12 by huweber           #+#    #+#             */
/*   Updated: 2017/08/24 18:01:19 by huweber          ###   ########.fr       */
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

  // t_vec3d t = - X|V / D|V
  // P = C + V1*p + V2*q
  // P - C = V1*p + V2*q
  // [ Px-Cx ] = [ V1.x V2.x ] * [ p ]
  // [ Py-Cy ]   [ V1.y V2.y ]   [ q ]
  __host__ __device__ int   hit_triangle(t_triangle triangle, t_ray ray,
    t_intersection intersection_tmp)
  {
    t_vec3d v[4];
    double  det;
    double   res[3];

    v[0] = vector_substract(triangle.v1, triangle.pos);
  	v[1] = vector_substract(triangle.v2, triangle.pos);
  	v[2] = vector_cross(ray.dir, v[1]);
  	det = vector_dot(v[0], v[2]);
  	if (det <= 0 || intersection_tmp.id == triangle.id)
  		return (0);
  	det = 1 / det;
  	v[3] = vector_substract(ray.origin, triangle.pos);
  	res[0] = vector_dot(v[3], v[2]) * det;
    if (res[0] > 0 && res[0] < 1)
  	{
  		v[3] = vector_cross(v[3], v[0]);
  		res[1] = vector_dot(ray.dir, v[3]) * det;
  		if (res[1] > 0 && (res[0] + res[1]) < 1)
  		{
  			res[2] = vector_dot(v[1], v[3]) * det;
  			if (res[2] > 0.000001)
  				return (res[2]);
  		}
  	}
    return (-1);
  }

  __host__ __device__ int		get_triangle(t_triangle triangle, t_ray ray,
      t_intersection *intersection_tmp)
  {
    int     t;
    t_vec3d n;

    if (intersection_tmp->id == triangle.id)
      return (0);
    t = hit_triangle(triangle, ray, *intersection_tmp);
    if (t > 0)
    {
      intersection_tmp->t = t;
      n = triangle.up;
      n = vector_normalize(n);
      if (vector_dot(n, ray.dir) < 0)
        n = vector_scalar(n, -1);
      intersection_tmp->normal_v = n;
      return (1);
    }
    return (0);
  }

// __host__ __device__ int   hit_triangle(t_triangle triangle, t_ray ray,
//   t_intersection intersection_tmp)
// {
//   t_vec3d v[4];
//   double  det;
//   double   res[3];
//
//   v[0] = vector_substract(triangle.v1, triangle.pos);
// 	v[1] = vector_substract(triangle.v2, triangle.pos);
// 	v[2] = vector_cross(ray.dir, v[1]);
// 	det = vector_dot(v[0], v[2]);
// 	if (det <= 0 || intersection_tmp.id == triangle.id)
// 		return (0);
// 	det = 1 / det;
// 	v[3] = vector_substract(ray.origin, triangle.pos);
// 	res[0] = vector_dot(v[3], v[2]) * det;
//   if (res[0] > 0 && res[0] < 1)
// 	{
// 		v[3] = vector_cross(v[3], v[0]);
// 		res[1] = vector_dot(ray.dir, v[3]) * det;
// 		if (res[1] > 0 && (res[0] + res[1]) < 1)
// 		{
// 			res[2] = vector_dot(v[1], v[3]) * det;
// 			if (res[2] > 0.000001)
// 				return (res[2]);
// 		}
// 	}
//   return (-1);
// }
//
// __host__ __device__ int		get_triangle(t_triangle triangle, t_ray ray,
//     t_intersection *intersection_tmp)
// {
//   int     t;
//   t_vec3d n;
//
//   if (intersection_tmp->id == triangle.id)
//     return (0);
//   t = hit_triangle(triangle, ray, *intersection_tmp);
//   if (t > 0)
//   {
//     intersection_tmp->t = t;
//     n = triangle.up;
//     n = vector_normalize(n);
//     if (vector_dot(n, ray.dir) < 0)
//       n = vector_scalar(n, -1);
//     intersection_tmp->normal_v = n;
//     return (1);
//   }
//   return (0);
// }

__host__ __device__ void   get_closest_triangle(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.triangles_len)
	{
		if (get_triangle(world.triangles[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->type = 't';
				intersection->t = intersection_tmp->t;
				intersection->id = world.triangles[i].id;
				intersection->reflection_coef = world.triangles[i].reflection_coef;
				intersection->reflection_coef = world.triangles[i].reflection_coef;
        intersection->transparence_coef = world.triangles[i].transparence_coef;
				intersection->color = world.triangles[i].color;
				intersection->chess = world.triangles[i].chess;
				intersection->pos =
					vector_add(ray.origin, vector_scalar(ray.dir, intersection->t));
				intersection->normal_v = intersection_tmp->normal_v;
			}
		}
		i++;
	}
}
