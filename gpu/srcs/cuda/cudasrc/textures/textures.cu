#include <cuda.h>
#include <stdio.h>
#include <float.h>

extern "C" {
  #include "../../../../includes/vectors.h"
  #include "../../../../includes/rt.h"
  #include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ t_color 	handle_reflection(t_world world, t_ray ray,
															t_intersection *intersection)
{
	int				i;
	int				depth;
	t_color		color = (t_color){0, 0, 0};

	i = 0;
	int j = 0;
	depth = intersection->reflection_coef < MAX_DEPTH ? intersection->reflection_coef : MAX_DEPTH;
	while(i < depth && j < depth)
	{
		intersection->t = DBL_MAX;
		intersection->type = '0';
		ray.origin = intersection->pos;
		ray.dir = vector_normalize(vector_substract(ray.dir,
			vector_scalar(intersection->normal_v,
				2 * vector_dot(ray.dir, intersection->normal_v))));
		get_closest_intersection(world, ray, intersection);
		if (intersection->type != '0')
		{
			color_add(&color, *intersection->color);
			if (intersection->reflection_coef == 0)
				i++;
		}
		else
		{
			color = (t_color){0, 0, 0};
			*intersection->color = (t_color){0, 0, 0};
			return (color);
		}
		i++;
		j++;
	}
	*intersection->color = color;
	return (color);
}

__host__ __device__ t_color 	handle_refraction_transparence(t_world world,
																			t_ray ray, t_intersection *intersection)
{
	double			calc[3];
	double			ref_coef;
	t_color			color;

	intersection->t = DBL_MAX;
	intersection->type = '0';
	color = *intersection->color;
 	ref_coef = intersection->refraction_coef;
	if (ref_coef > 1)
	{
		calc[0] = vector_dot(intersection->normal_v, ray.dir);
		calc[1] = sqrt(1 - (ref_coef * ref_coef) * (1 - (calc[0] * calc[0])));
		if (calc[0] > 0)
			calc[2] = (ref_coef * calc[0] - calc[1]);
		else
			calc[2] = (ref_coef * calc[0] + calc[1]);
	 	ray.dir = vector_normalize(vector_add(
			vector_scalar(ray.dir, ref_coef),
			vector_scalar(intersection->normal_v, calc[2])));
	}
	ray.origin = intersection->pos;
	if (get_closest_intersection(world, ray, intersection))
	{
		color = *intersection->color;
		// color_scalar(&color, ref_coef);
		// color_add(&color, *intersection->color);
	}
	else
		color = (t_color){0, 0, 0};
	*intersection->color = color;
	return (color);
}

__host__ __device__ t_color chess_effect(t_intersection *intersection)
{
	float			x;
	float			y;
	t_color		color;

  if (intersection->type == 'p')
	{
		if (((int)((intersection->pos.x + 450) * CHESS_PATTERN) ^
					(int)((intersection->pos.y + 450) * CHESS_PATTERN) ^
					(int)((intersection->pos.z + 450) * CHESS_PATTERN)) % 2 == 0)
		{
			color = *intersection->chess;
			intersection->color = intersection->chess;
		}
		else
			color = *intersection->color;
	}
	else
	{
		x = atan2(intersection->normal_v.z, intersection->normal_v.x) / M_PI + 1;
	  y = acos(intersection->normal_v.y) / M_PI;
		if ((fmodf(x * CHESS_PATTERN, 1) > 0.5) ^
				(fmodf(y * CHESS_PATTERN, 1) > 0.5) == 0)
		{
			color = *intersection->chess;
			intersection->color =	intersection->chess;
		}
		else
			color = *intersection->color;
	}

	return (color);
}
