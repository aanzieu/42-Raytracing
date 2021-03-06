#include <cuda.h>
#include <float.h>

extern "C" {
  #include "../../../../includes/vectors.h"
  #include "../../../../includes/rt.h"
  #include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ t_color 	handle_reflection_cpu(t_world world, t_ray ray,
  t_intersection *intersection)
{
  t_intersection  intersection_tmp;

  new_intersection(&intersection_tmp);
  intersection_tmp.id = intersection->id;
  intersection_tmp.depth = intersection->depth + 1;
  ray.origin = intersection->pos;
  ray.dir = vector_normalize(vector_substract(ray.dir,
    vector_scalar(intersection->normal_v,
    2 * vector_dot(ray.dir, intersection->normal_v))));
  return (ray_tracer_depth_cpu(world, ray, intersection_tmp));
}

__host__ __device__ t_color 	handle_transparence_cpu(t_world world,
  t_ray ray, t_intersection *intersection)
{
  t_intersection  intersection_tmp;

  new_intersection(&intersection_tmp);
  intersection_tmp.id = intersection->id;
  intersection_tmp.pos = intersection->pos;
  intersection_tmp.depth = intersection->depth + 1;
  ray.origin = intersection->pos;
  return (ray_tracer_depth_cpu(world, ray, intersection_tmp));
}

__host__ __device__ t_color 	handle_refraction_cpu(t_world world,
  t_ray ray, t_intersection *intersection)
{
  t_intersection  intersection_tmp;
  double          etai;
  double          cosi;
  double          eta;
  double          etat;
  double          k;
  t_vec3d         n;

  new_intersection(&intersection_tmp);
  intersection_tmp.id = intersection->id;
  intersection_tmp.pos = intersection->pos;
  intersection_tmp.depth = intersection->depth + 1;
  ray.origin = intersection->pos;
  cosi = clamp(-1, 1, vector_dot(ray.dir, intersection->normal_v));
  etai = 1.0;
  etat = intersection->refraction_coef + 1.;
  n = intersection->normal_v;
  if (cosi < 0)
    cosi = -cosi;
  else
  {
    swap_double(&etai, &etat);
    n = vector_scalar(n, -1);
  }
  eta = etai / etat;
  k = 1.0 - eta * eta * (1.0 - cosi * cosi);
  if (k < 0)
    return (intersection->color);
  ray.dir = vector_add(vector_scalar(ray.dir, eta),
      vector_scalar(n, (eta * cosi - sqrt(k))));
  return (ray_tracer_depth_cpu(world, ray, intersection_tmp));
}

__host__ __device__ t_vec3d tabs(t_vec3d v)
{
  return ((t_vec3d){fabs(v.x), fabs(v.y), fabs(v.z)});
}

__host__ __device__ t_color handle_chess(t_ray ray,
  t_intersection intersection)
{
	float		x;
	float		y;
	t_color		color;
  t_vec3d   pos;

  pos = vector_calculate(intersection.pos, intersection.normal_v);
  pos = vector_calculate(ray.origin, pos);
  if (intersection.type == 'p')
  {
    if (fabs(intersection.normal_v.z) == 1)
      swap_double(&pos.y, &pos.z);
    else if (fabs(intersection.normal_v.x) == 1)
      swap_double(&pos.x, &pos.y);
		if (((int)((pos.x + 4500) * CHESS_PATTERN) ^
					(int)((pos.z + 4500) * CHESS_PATTERN)) % 2 == 0)
			color = intersection.chess;
	else
		color = intersection.color;
  }
	else
	{
		x = atan2(intersection.normal_v.z, intersection.normal_v.x) / M_PI + 1;
	  y = acos(intersection.normal_v.y) / M_PI;
		if ((fmodf(x * CHESS_PATTERN, 1) > 0.5) ^
        (fmodf(y * CHESS_PATTERN, 1) > 0.5) == 0)
			color = intersection.chess;
		else
			color = intersection.color;
	}
	return (color);
}
