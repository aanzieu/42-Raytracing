#include <cuda.h>
#include <float.h>

extern "C" {
  #include "../../../../includes/vectors.h"
  #include "../../../../includes/rt.h"
  #include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ static t_color apply_marble(t_world world, t_vec3d pos,\
	t_color color, t_perlin perlin, int *p)
{
	double		x, y, z, coef;
	t_color		color2;
	int				level;

	coef = 0;
	level = 1;
	x = pos.x * perlin.scale * 100;
	y = pos.y * perlin.scale * 100;
	z = pos.z * perlin.scale * 100;
	while (level++ < 10)
	 	coef +=  (1.0f / level) * fabs(apply_noise(world,
		 	level * 0.05 * x, level * 0.15 * y, level * 0.05 * z, p));
	coef = 0.5f * sin((x + y) * 0.05f + coef) + 0.5f;
  color2 = (t_color){color.r / 2, color.g / 2, color.b / 2};
	return (color_add(color_scalar(color, coef),
			color_scalar(color2, (1.0f - coef))));
}

__host__ __device__ static t_color apply_wood(t_world world, t_vec3d pos,\
	t_color color, t_perlin perlin, int *p)
{
	double		x, y, z, grain;
	t_color		color2;

	x = pos.x * perlin.scale * 10;
	y = pos.y * perlin.scale * 10;
	z = pos.z * perlin.scale * 10;
	grain = apply_noise(world, x, y, z, p) * 5;
	grain = grain - (int)grain;
  color2 = (t_color){color.r / 2, color.g / 2, color.b / 2};
	return (color_add(color_scalar(color, grain),
		color_scalar(color2, (1.0f - grain))));
}

__host__ __device__ void 	apply_noise_dist(t_world world,\
				t_intersection *intersection, t_perlin perlin)
{
	if (perlin.pre_set == MARBLE)
		intersection->color = apply_marble(world, intersection->pos,\
			 intersection->color, perlin, world.p);
	else if (perlin.pre_set == WOOD)
		intersection->color = apply_wood(world, intersection->pos,\
			 intersection->color, perlin, world.p);
  if (perlin.is_set == 1)
		intersection->normal_v = normal_perturbation(world,
			intersection->normal_v, intersection->pos, perlin, world.p);
}
