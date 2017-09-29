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

__host__ __device__ double get_indice(t_intersection inter)
{
	if (inter.reflection_coef > 0)
		return (inter.reflection_coef);
	if (inter.transparence_coef > 0)
		return (inter.transparence_coef);
	return (0);
}

__host__ __device__ t_color apply_materials_gpu(t_world world, t_ray ray,
	t_intersection intersection, t_color color)
{
	t_color tmp = color;
	int			flag = 0, i = 0;
	double 	indice;

	indice = get_indice(intersection);
	while (flag == 0 && intersection.depth < MAX_DEPTH)
	{
		flag = 1;
		if (intersection.transparence_coef > 0)
			tmp = handle_transparence_gpu(world, &ray, &intersection, &flag);
		if (intersection.reflection_coef > 0)
			tmp = handle_reflection_gpu(world, &ray, &intersection, &flag);
		if (intersection.refraction_coef > 0)
			tmp = handle_refraction_gpu(world, &ray, &intersection, &flag);
		if (intersection.chess.r >= 0)
				tmp = handle_chess(ray, intersection);
		if (flag == 0)
		{
			i = 0;
			tmp = color_multiply(tmp, world.ambient.color);
			tmp = color_scalar(tmp, world.ambient.intensity);
			while (i < world.lights_len)
			{
				tmp = get_light_at(world, tmp, world.lights[i], intersection, ray);
				i++;
			}
		}
	}
	if (indice > 0 && indice < 1)
		return (color_scalar(tmp, indice));
	else
		return (tmp);
}

__host__ __device__ t_color		ray_tracer_depth_gpu(t_world world, t_ray ray,
				t_intersection intersection)
{
	t_color					color;
	int							i;

	i = 0;
	color = new_color(0, 0, 0);
	get_closest_intersection(world, ray, &intersection);
	if (intersection.type == '0')
		return ((t_color){0, 0, 0});
	// color = apply_materials_gpu(world, ray, intersection, color);
	color = intersection.color;
	color = color_multiply(color, world.ambient.color);
	color = color_scalar(color, world.ambient.intensity);
	if(world.keys.light_none == 0)
		color = intersection.color;
	if(world.keys.select == 1)
		cartoon_effect(world, &color, intersection, ray);
	while (i < world.lights_len && world.keys.light_none == 1)
	{
		color = get_light_at(world, color, world.lights[i], intersection, ray);
		if (world.keys.pad_0 == 6)
			cartoon_effect(world, &color, intersection, ray);
		i++;
	}
	return (color);
}

__host__ __device__ int		ray_tracer_gpu(t_world world, int x, int y)
{
	t_ray      			ray;
	t_color					color = (t_color){0, 0, 0};
	t_intersection	intersection;
	int i = 0, j = 0, xx = 0, yy = 0;

	while (i < world.aa)
	{
		j = 0;
		yy = y + i;
		while (j < world.aa)
		{
			xx = x + j;
			new_intersection(&intersection);
			ray.dir = (t_vec3d){0, 0, 0};
			ray.origin = (t_vec3d){0, 0, 0};
			get_up_left(&world);
			get_ray_direction(world, &ray, xx, yy);
			color = color_add(color, ray_tracer_depth_gpu(world, ray, intersection));
			j++;
		}
		i++;
	}
	color = color_divide(color, world.aa * world.aa);
	return (get_color(color));
}
