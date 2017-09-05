#include <cuda.h>
#include <stdio.h>
#include <float.h>

extern "C" {
  #include "../../../../includes/vectors.h"
  #include "../../../../includes/rt.h"
  #include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ inline t_color color_cpy(t_color res)
{
  return ((t_color){res.r, res.g, res.b});
}

__host__ __device__ t_color 	handle_reflection(t_world world, t_ray ray,
  t_intersection *intersection)
{
	int				    	i;
	int			     		depth;
  t_color         color;
	t_intersection  intersection_tmp;

  i = 0;
  depth = intersection->reflection_coef < MAX_DEPTH ?
		intersection->reflection_coef : MAX_DEPTH;
  while (i < depth)
  {
    intersection_tmp.t = DBL_MAX;
    intersection_tmp.type = '0';
		intersection_tmp.id = intersection->id;
		intersection_tmp.pos = intersection->pos;
    ray.origin = intersection_tmp.pos;
    ray.dir = vector_normalize(vector_substract(ray.dir,
            vector_scalar(intersection->normal_v,
                    2 * vector_dot(ray.dir, intersection->normal_v))));
    get_closest_intersection(world, ray, &intersection_tmp);
    if (intersection_tmp.type != '0')
		{
			if (intersection_tmp.chess.r != -1)
				color = handle_chess(ray, &intersection_tmp);
			color = intersection_tmp.color;
			color = color_scalar(color, 0.6);
		}
    else
    {
      color = new_color(0, 0, 0);
      intersection->color = color;
      return (color);
    }
    i++;
  }
	intersection->color = color;
  return (color);
}

__host__ __device__ t_color 	handle_transparence(t_world world,
  t_ray ray, t_intersection *intersection)
{
  t_intersection  intersection_tmp;

  intersection_tmp.t = DBL_MAX;
  intersection_tmp.id = intersection->id;
  intersection_tmp.pos = intersection->pos;
  intersection_tmp.depth = intersection->depth + 1;
  return (ray_tracer_depth(world, ray, intersection_tmp));
  // intersection_tmp.type = '0';
  // ray.origin = intersection->pos;
  // ori = color_scalar(intersection->color, intersection->transparence_coef);
  // if (get_closest_intersection(world, ray, &intersection_tmp) == 1)
  // {
  //  res = intersection->color;
  //  intersection->color = intersection_tmp.color;
  //  intersection->id = intersection_tmp.id;
  //  intersection->t = DBL_MAX;
  //  intersection->depth += 1;
  // }
  //  else
  //    res = ori;
  //  return (res);
}

__host__ __device__ t_color 	handle_refraction(t_world world,
  t_ray ray, t_intersection *intersection)
{
  double tmp;
  double cosi, etai, etat, eta, k;
  t_vec3d n, dirtmp;
  t_intersection inter;
  t_color color;

  inter.t = DBL_MAX;
  inter.type = '0';
  inter.id = intersection->id;
	color = intersection->color;
  etat = intersection->refraction_coef;
  etai = 1; ///////////
  n = intersection->normal_v;
  if (vector_dot(ray.dir, n) < -1)
    cosi = -1;
  else if (cosi > 1)
    cosi = 1;
  if (cosi < 0)
    cosi = -cosi;
  else
  {
    tmp = etai;
    etai = etat;
    etat = tmp;
    n = vector_scalar(intersection->normal_v, -1);
  }
  eta = etai / etat;
  k = 1 - eta * eta * (1 - cosi * cosi);
  if (k < 0)
    return (color);
  else
  {
    ray.origin = intersection->pos;
    dirtmp = ray.dir;
    ray.dir = vector_add(vector_scalar(dirtmp, eta), vector_scalar(n, (eta * cosi - sqrt(k))));
    ray.dir = vector_normalize(ray.dir);
    if (get_closest_intersection(world, ray, &inter))
      return (inter.color);
  }
//  return (k < 0 ? 0 : eta * ray.dir + (eta * cosi - sqrt(k)) * n);
	return (color);
}
//   // double			calc[3];
// 	// double			ref_coef;
//   //
// 	// t_color			color;
// 	calc[0] = -vector_dot(intersection->normal_v, ray.dir);
// 	calc[1] = sqrt(1 - (ref_coef * ref_coef) * (1 - (calc[0] * calc[0])));
// 	if (calc[0] < 0)
// 		calc[2] = (ref_coef * calc[0] - calc[1]);
// 	else
// 		calc[2] = (ref_coef * calc[0] + calc[1]);
//  	ray.dir = vector_normalize(vector_add(
// 		vector_scalar(ray.dir, ref_coef),
// 		vector_scalar(intersection->normal_v, calc[2])));
// 	ray.origin = intersection->pos;
// 	if (get_closest_intersection(world, ray, intersection))
// 	{
// //		color = intersection->color;
// 	// 	color_scalar(&color, ref_coef);
// 	 	color = color_add(color, intersection->color);
//   }
// 	else
// 		color = (t_color){0, 0, 0};
//}

__host__ __device__ t_color handle_chess(t_ray ray,
  t_intersection *intersection)
{
	float			x;
	float			y;
	t_color		color;
  t_vec3d   pos;

  pos = vector_calculate(intersection->pos, intersection->normal_v);
  pos = vector_calculate(ray.origin, pos);
  if (intersection->type == 'p')
	{
		if (((int)((pos.x + 4500) * CHESS_PATTERN) ^
					(int)((pos.y + 4500) * CHESS_PATTERN) ^
					(int)((pos.z + 4500) * CHESS_PATTERN)) % 2 == 0)
		{
			color = intersection->chess;
			intersection->color = intersection->chess;
		}
	else
		color = intersection->color;
  }
	else
	{
		x = atan2(intersection->normal_v.z, intersection->normal_v.x) / M_PI + 1;
	  y = acos(intersection->normal_v.y) / M_PI;
		if ((fmodf(x * CHESS_PATTERN, 1) > 0.5) ^
				(fmodf(y * CHESS_PATTERN, 1) > 0.5) == 0)
		{
			color = intersection->chess;
			intersection->color =	intersection->chess;
		}
		else
			color = intersection->color;
	}

	return (color);
}
