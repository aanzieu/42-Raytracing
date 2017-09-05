
extern "C" {
	#include "../../../../includes/rt.h"
	#include "../../cudaheader/gpu_rt.h"
	#include <vectors.h>
	#include <equation.h>
}

__host__ __device__ t_vec3d	get_normal_hyperboloid(t_hyperboloid hyper,
	t_ray ray, t_intersection intersection)
{
	t_vec3d	normal_v;
	t_vec3d	x;
	t_vec3d	v;
	double	m;

	x = vector_calculate(hyper.top, ray.origin);
	v = vector_normalize(hyper.normal);
	m = vector_dot(ray.dir, vector_scalar(v, intersection.t))
		+ vector_dot(x, v);
	normal_v = vector_normalize(vector_substract(vector_calculate(hyper.top,
		intersection.pos),
				vector_scalar(v, m + hyper.radius)));
	return (normal_v);
}

__host__ __device__ int		get_hyperboloid(t_hyperboloid hyper, t_ray ray,
		t_intersection *intersection_tmp)
{
	t_eq	eq;
	t_vec3d tmp;

	if (intersection_tmp->id == hyper.id)
		return (0);
	tmp = vector_calculate(hyper.top, ray.origin);
	eq.a = ((ray.dir.x * ray.dir.x) / 4.0) - ((ray.dir.y * ray.dir.y) / 3.0) +
		(ray.dir.z * ray.dir.z);
	eq.b = ((2.0 * ray.dir.x * tmp.x) / 4.0) -
		((2.0 * tmp.y * ray.dir.y) / 3.0) + (2.0 * tmp.z * ray.dir.z);
	eq.c = ((tmp.x * tmp.x) / 4.0) - ((tmp.y * tmp.y) / 3.0)
		+ tmp.z * tmp.z - 1.0;
	second_degres(&eq);
	if(eq.res[0] != NOT_A_SOLUTION)
	{
		intersection_tmp->t = eq.res[0];
		return (1);
	}
//	intersection_tmp->t = -1.0;
	return (0);
}

__host__ __device__ void	get_closest_hyperboloid(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.hyperboloids_len)
	{
		if (get_hyperboloid(world.hyperboloids[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->type = 'h';
				intersection->id = world.hyperboloids[i].id;
				intersection->t = intersection_tmp->t;
				intersection->reflection_coef = world.hyperboloids[i].reflection_coef;
				intersection->refraction_coef = world.hyperboloids[i].refraction_coef;
				intersection->transparence_coef = world.hyperboloids[i].transparence_coef;
				intersection->color = world.hyperboloids[i].color;
				intersection->chess = world.hyperboloids[i].chess;
				intersection->pos = vector_add(ray.origin,
						vector_scalar(ray.dir, intersection_tmp->t));
				intersection->normal_v = get_normal_hyperboloid(world.hyperboloids[i], ray,
						*intersection);
			}
		}
		i++;
	}
}
