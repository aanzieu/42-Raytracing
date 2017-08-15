extern "C" {
#include "../../../../includes/rt.h"
#include "../../cudaheader/gpu_rt.h"
#include <vectors.h>
#include <equation.h>
#include <float.h>
#include <math.h>
}

// __host__ __device__ int hitbox_torus(t_torus to, t_ray ray)
// {
// 	t_intersection inter;
//
// 	if (get_sphere(to.outer, ray, &inter) == 0)
// 		if (get_sphere(to.inner, ray, &inter) == 1)
// 			return (-1);
// 	return (1);
// }

__host__ __device__ int	get_torus(t_torus to, t_ray ray, t_intersection *inter)
{
	double	a[5], equ[7];//, roots[5];
	double t;

	ray.origin = vector_calculate(to.pos, ray.origin);
	equ[0] = 4.0 * to.radius_big * to.radius_big;
	equ[1] = equ[0] * (ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y);
	equ[2] = 2.0 * equ[0] * (ray.origin.x * ray.dir.x + ray.origin.y * ray.dir.y);
	equ[3] = equ[0] * (ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y);
	equ[4] = vector_magnitude(ray.dir);
	equ[5] = 2.0 * vector_dot(ray.origin, ray.dir);
	equ[6] = vector_magnitude(ray.origin) + to.radius_big * to.radius_big -
						to.radius_small * to.radius_small;
	a[0] = equ[4] * equ[4];
	a[1] = 2.0 * equ[4] * equ[5];
	a[2] = 2.0 * equ[4] * equ[6] + equ[5] * equ[5] - equ[1];
	a[3] = 2.0 * equ[5] * equ[6] - equ[2];
	a[4] = equ[6] * equ[6] - equ[3];
	if ((t = solver_n_degree3(a, 4)) > 0)
	{
		inter->t = t;
		inter->id = to.id;
		inter->type = 't';
		return (1);
	}
	inter->t = -1.0;
	return (0);
}

__host__ __device__ t_vec3d get_normal_torus(t_intersection *intersection,
		t_torus to, t_ray ray)
{
	t_vec3d			normal;

	t_vec3d pos = vector_substract(intersection->pos, to.pos);
	double a = 1.0 - (to.radius_big / sqrt(pos.x * pos.x + pos.y * pos.y));
	normal.x = a * pos.x;
	normal.y = a * pos.y;
	normal.z = pos.z;
	normal = vector_normalize(normal);
	return (normal);
}

__host__ __device__ void	get_closest_torus(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.torus_len)
	{
		if (get_torus(world.torus[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflection_coef = world.torus[i].reflection_coef;
				intersection->reflection_coef = world.torus[i].reflection_coef;
				intersection->id = intersection_tmp->id;
				intersection->color = &world.torus[i].color;
				intersection->chess = &world.torus[i].chess;
				intersection->pos =
					vector_add(ray.origin, vector_scalar(ray.dir, intersection->t));
				intersection->normal_v =
					get_normal_torus(intersection, world.torus[i], ray);
			}
		}
		i++;
	}
}
