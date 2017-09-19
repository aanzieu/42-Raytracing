#include <cuda.h>
#include <stdio.h>
#include <float.h>

extern "C" {
  #include "../../../../includes/vectors.h"
  #include "../../../../includes/rt.h"
  #include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ t_color 	handle_reflection_gpu(t_world world, t_ray *ray,
  t_intersection *intersection, int *flag)
{
  t_intersection  intersection_tmp;
  t_ray           ray_tmp;

  new_intersection(&intersection_tmp);
  intersection_tmp.id = intersection->id;
  intersection_tmp.depth = intersection->depth + 1;
  ray_tmp.origin = intersection->pos;
  ray_tmp.dir = vector_normalize(vector_substract(ray->dir,
    vector_scalar(intersection->normal_v,
    2 * vector_dot(ray->dir, intersection->normal_v))));
  get_closest_intersection(world, ray_tmp, &intersection_tmp);
	if (intersection_tmp.type == '0')
		return ((t_color){0, 0, 0});
	else
  {
    *intersection = intersection_tmp;
    *ray = ray_tmp;
    *flag = 0;
		return (intersection_tmp.color);
  }
}

__host__ __device__ t_color 	handle_transparence_gpu(t_world world,
  t_ray *ray, t_intersection *intersection, int *flag)
{
  t_intersection  intersection_tmp;
  t_ray           ray_tmp;

  new_intersection(&intersection_tmp);
  intersection_tmp.id = intersection->id;
  intersection_tmp.pos = intersection->pos;
  intersection_tmp.depth = intersection->depth + 1;
  ray_tmp.origin = intersection->pos;
  ray_tmp.dir = ray->dir;
  get_closest_intersection(world, ray_tmp, &intersection_tmp);
	if (intersection_tmp.type == '0')
		return ((t_color){0, 0, 0});
  else
  {
    *intersection = intersection_tmp;
    *ray = ray_tmp;
    *flag = 0;
		return (intersection_tmp.color);
  }
}

__host__ __device__ t_color 	handle_refraction_gpu(t_world world,
  t_ray *ray, t_intersection *intersection, int *flag)
{
  t_intersection  intersection_tmp;
  t_ray           ray_tmp;
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
  ray_tmp.origin = intersection->pos;
  cosi = clamp(-1, 1, vector_dot(ray->dir, intersection->normal_v));
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
  ray_tmp.dir = vector_add(vector_scalar(ray->dir, eta),
      vector_scalar(n, (eta * cosi - sqrt(k))));
  if (get_closest_intersection(world, ray_tmp, &intersection_tmp) == 0)
		return ((t_color){0, 0, 0});
  else
  {
    *intersection = intersection_tmp;
    *ray = ray_tmp;
    *flag = 0;
    return (intersection_tmp.color);
  }
}
