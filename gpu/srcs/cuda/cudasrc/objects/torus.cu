
extern "C" {
	#include <rt.h>
	#include "gpu_rt.h"
	#include <vectors.h>
}

/*
**	On envoie le rayon et la structure qui contient le torus et la fonction
**	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
**	avec le plan
*/

__host__ __device__ int		get_torus(t_torus torus, t_ray ray, t_intersection *intersection_tmp)
{
  (void)torus;
  (void)ray;
  (void)intersection_tmp;
  return (0);
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
				intersection->id = world.torus[i].id;
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflection_coef = world.torus[i].reflection_coef;
				intersection->refraction_coef = world.torus[i].refraction_coef;
				intersection->color = &world.torus[i].color;
				intersection->pos = vector_add(ray.origin,
				vector_scalar(ray.dir, intersection->t));
				intersection->normal_v = intersection_tmp->normal_v;
			}
		}
		i++;
	}
}
