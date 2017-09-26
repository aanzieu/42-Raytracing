/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*     Updated: 2017/06/29 14:26:47 by huweber          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

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

__host__ __device__ void	get_ray_direction(t_world world, t_ray *ray,
	int x, int y)
{
	t_vec3d dir_point;

	dir_point = vector_substract(
								vector_add(world.viewplane_aa.up_left,
									vector_scalar(world.camera.right_v,
										world.viewplane_aa.x_indent * x)),
								vector_scalar(world.camera.up_v, world.viewplane_aa.y_indent * y));
	ray->dir_point = dir_point;
	ray->dir = vector_calculate(world.camera.pos, dir_point);
	ray->origin = world.camera.pos;
}

/*
** Get the top-left point in virtual space of the viewplane
*/

__host__ __device__ void	get_up_left(t_world *world)
{
	world->viewplane.up_left = vector_substract(
									vector_add(
										vector_add(
											world->camera.pos,
											world->camera.dir_v),
										vector_scalar(
											world->camera.up_v,
											world->viewplane.height / 2.0f)),
									vector_scalar(
										world->camera.right_v,
										world->viewplane.width / 2.0f));
	world->viewplane_aa.up_left = vector_substract(

									vector_add(
										vector_add(
											world->camera.pos,
											world->camera.dir_v),
										vector_scalar(
											world->camera.up_v,
											world->viewplane_aa.height / 2.0f)),
									vector_scalar(
										world->camera.right_v,
										world->viewplane_aa.width / 2.0f));
}

__host__ __device__ double		get_closest_intersection(t_world world, t_ray ray,
										t_intersection *intersection)
{
	t_intersection	intersection_tmp;
	intersection_tmp.t = DBL_MAX;
	intersection_tmp.type = '0';
	intersection_tmp.id = intersection->id;
	get_closest_sphere(world, ray, intersection, &intersection_tmp);
	// get_closest_mobius(world, ray, intersection, &intersection_tmp);
	// get_closest_torus(world, ray, intersection, &intersection_tmp);
	get_closest_plane(world, ray, intersection, &intersection_tmp);
	// get_closest_disk(world, ray, intersection, &intersection_tmp);
	// get_closest_cone(world, ray, intersection, &intersection_tmp);
	// get_closest_cube(world, ray, intersection, &intersection_tmp);
	// get_closest_hollow_cube(world, ray, intersection, &intersection_tmp);
	// get_closest_cylinder(world, ray, intersection, &intersection_tmp);
	// get_closest_paraboloid(world, ray, intersection, &intersection_tmp);
	// get_closest_hyperboloid(world, ray, intersection, &intersection_tmp);
	// get_closest_triangle(world, ray, intersection, &intersection_tmp);
	if (intersection->type == '0')
		return (0);
	return (1);
}

__host__ __device__ t_color apply_materials_cpu(t_world world, t_ray ray,
	t_intersection intersection, t_color color)
{
	if (intersection.transparence_coef > 0)
		color = color_add(color_scalar(color, 1 - intersection.transparence_coef),
		color_scalar(handle_transparence_cpu(world, ray, &intersection),
		intersection.transparence_coef));
	if (intersection.reflection_coef > 0)
		color = color_add(color_scalar(color, 1 - intersection.reflection_coef),
		color_scalar(handle_reflection_cpu(world, ray, &intersection),
		intersection.reflection_coef));
	if (intersection.refraction_coef > 0)
		color = color_add(color, handle_refraction_cpu(world, ray, &intersection));
	if (intersection.chess.r >= 0)
		color = color_add(color, handle_chess(ray, intersection));
	return (color);
}

__host__ __device__ t_color		ray_tracer_depth_cpu(t_world world, t_ray ray,\
				t_intersection intersection)
{
	t_color					color;
	int							i;

	i = 0;
	color = new_color(0, 0, 0);
	if (intersection.depth > MAX_DEPTH)
		return (color);
	get_closest_intersection(world, ray, &intersection);
	if (intersection.type == '0')
		return ((t_color){0, 0, 0});
	if(world.keys.light_none == 0)
		color = intersection.color;
	if(world.keys.light_none == 1 && world.mode == 0)
		color = apply_materials_cpu(world, ray, intersection, color);
	color = color_multiply(color, world.ambient.color);
	color = color_scalar(color, world.ambient.intensity);
	if(world.keys.select == 1)
		cartoon_effect(world, &color, world.lights[i], intersection, ray);
	while (i < world.lights_len && world.keys.light_none == 1)
	{
		if (get_light_box(world.lights[i], intersection, ray) == 1)
			color = color_scalar(color_divide(
				color_add((t_color){0.5, 0.5, 0.5}, world.lights[i].color), 2),
				0.5 + 0.5 / world.lights[i].intensity_coef);
		color = get_light_at(world, color, world.lights[i], intersection, ray);
		if (world.keys.pad_9 == 1)
			cartoon_effect(world, &color, world.lights[i], intersection, ray);
		i++;
	}
	return (color);
}

__host__ __device__ int		ray_tracer_cpu(t_world world, int x, int y)
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
			color = color_add(color, ray_tracer_depth_cpu(world, ray, intersection));
			j++;
		}
		i++;
	}
	color = color_divide(color, world.aa * world.aa);
	return (get_color(color));
}
