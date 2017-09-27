extern "C" {
	#include <rt.h>
	#include "gpu_rt.h"
	#include "object.h"
	#include "vectors.h"
}
#include "../../../frameworks/SDL2.framework/Headers/SDL.h"
#include "../../../includes/display.h"
#include <math.h>
#include <float.h>
#include <cuda.h>

__host__ __device__ int get_light_box(t_light light,\
	t_intersection intersection, t_ray ray)
{
	t_cube					light_box;
	t_intersection 	intersection_tmp;

	if (light.type != LIGHT_BOX)
		return (0);
	new_intersection(&intersection_tmp);
	intersection_tmp.t = intersection.t;
	light_box.min = light.pos;
	light_box.max = (t_vec3d){light.pos.x + 0.85, light.pos.y + 0.12,\
		light.pos.z + 0.85};
	if (get_cube(light_box, ray, &intersection_tmp) == 1)
		if (intersection_tmp.t < intersection.t && \
				intersection_tmp.t > SURFACE_TOLERANCE)
		return (1);
	return (0);
}

__host__ __device__ void new_intersection(t_intersection *new_i)
{
	new_i->id = -1;
	new_i->t = DBL_MAX;
	new_i->type = '0';
	new_i->depth = 0;
	new_i->transparence_coef = -1;
	new_i->refraction_coef = -1;
	new_i->reflection_coef = -1;
	new_i->chess = (t_color){-1, -1, -1};
	new_i->color = (t_color){0, 0, 0};
	new_i->pos = (t_vec3d){0, 0, 0};
	new_i->normal_v = (t_vec3d){0, 0, 0};
}

__host__ __device__ void	cartoon_effect(t_world world, t_color *color,
	t_light lights, t_intersection intersection, t_ray ray)
{
	if(world.keys.select == 1 && intersection.id_save == world.id_save)
	{
		if(vector_dot(intersection.normal_v, ray.dir) > -0.3 && intersection.type != 'p'
			&& vector_dot(intersection.normal_v, ray.dir) < 0.0000001)
		{
			color->r = 1;
			color->g = 1;
			color->b = 1;
		}
	}
	else if (world.keys.pad_0 == 6)
	{
		if(vector_dot(intersection.normal_v, ray.dir) > -0.3 && intersection.type != 'p'
			&& vector_dot(intersection.normal_v, ray.dir) < 0.0000001)
		{
			color->r = 0;
			color->g = 0;
			color->b = 0;
		}
	}
}
