/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include "../../../includes/rtv1.h"
}
#include "../../../frameworks/SDL2.framework/Headers/SDL.h"
#include "../cudaheader/gpu_rt.cuh"
#include "../../../includes/display.h"
#include <math.h>
#include <float.h>
#include <cuda.h>

__host__ __device__ void	get_ray_direction(t_world world, t_ray *ray, int x, int y)
{
	t_vec3d dir_point;

	dir_point = vector_substract(
							vector_add(
								world.viewplane.up_left,
								vector_scalar(
									world.camera.right_v,
									world.viewplane.x_indent * x)),
							vector_scalar(
								world.camera.up_v,
								world.viewplane.y_indent * y));
	ray->dir = vector_normalize(
				vector_calculate(
					world.camera.pos,
					dir_point));
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
}

__host__ __device__ double		get_closest_intersection(t_world world, t_ray ray,
										t_intersection *intersection)
{
	t_intersection	intersection_tmp;

	intersection_tmp.t = DBL_MAX;
	intersection_tmp.type = '0';
	
	get_closest_sphere(world, ray, intersection, &intersection_tmp);
	get_closest_plane(world, ray, intersection, &intersection_tmp);
	get_closest_cone(world, ray, intersection, &intersection_tmp);
	get_closest_cylinder(world, ray, intersection, &intersection_tmp);
	if (intersection_tmp.type == '0')
		return (0);
	else
		return (1);
}

__host__ __device__ int		ray_tracer(t_world world, int x, int y)
{
	t_ray			ray;
	t_intersection	intersection;

	intersection.t = DBL_MAX;
	intersection.type = '0';
	get_up_left(&world);
	get_ray_direction(world, &ray, x, y);
	get_closest_intersection(world, ray, &intersection);
	if (intersection.type != '0')
	{
		if (get_shadow(world, intersection, world.lights[0]) == 1)
			return (BLACK);
		else
			return (get_light_at(world.lights[0], intersection));
	}
		return (BLACK);
}
