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

__host__ __device__ void	get_ray_direction(t_world world, t_ray *ray, int x, int y)
{
	t_vec3d dir_point;

	dir_point = vector_substract(
								vector_add(world.viewplane.up_left, vector_scalar(world.camera.right_v, world.viewplane.x_indent * x)),
								vector_scalar(world.camera.up_v, world.viewplane.y_indent * y));
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
}

__host__ __device__ double		get_closest_intersection(t_world world, t_ray ray,
										t_intersection *intersection)
{
	t_intersection	intersection_tmp;

	intersection_tmp.t = DBL_MAX;
	intersection_tmp.type = '0';
	intersection_tmp.id = intersection->id;
	get_closest_sphere(world, ray, intersection, &intersection_tmp);
	get_closest_plane(world, ray, intersection, &intersection_tmp);
	get_closest_disk(world, ray, intersection, &intersection_tmp);
	get_closest_cone(world, ray, intersection, &intersection_tmp);
	get_closest_cylinder(world, ray, intersection, &intersection_tmp);
	get_closest_paraboloid(world, ray, intersection, &intersection_tmp);
	get_closest_hyperboloid(world, ray, intersection, &intersection_tmp);
	if (intersection->type == '0')
		return (0);
	else
		return (1);
}

__host__ __device__ void	cartoon_effect(t_world world, t_color *color, t_light lights, t_intersection intersection, t_ray ray)
{
	if(vector_dot(intersection.normal_v, ray.dir) > -0.3 && intersection.type != 'p'
			&& vector_dot(intersection.normal_v, ray.dir) < 0.0000001)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
}

__host__ __device__ void	direct_light(t_world world, t_color *color, t_light light, t_ray ray)
{
	t_vec3d	light_vector;
	t_color	direct_light;
	double 	angle;

	direct_light = new_color(10, 10, 10);
	light_vector = light.dir_v;
	angle = vector_dot(vector_scalar(world.camera.dir_v, -1), light_vector);
	color_scalar(&direct_light, angle);
	color_add(color, direct_light);
}

__host__ __device__ t_color 	handle_reflection(t_world world, t_ray ray,
															t_intersection *intersection)
{
	int					i;
	int					depth;
  t_color			color;

  i = 0;
  color = new_color(0, 0, 0);
  depth = intersection->reflection_coef < MAX_DEPTH ?
		intersection->reflection_coef : MAX_DEPTH;
  while (i < depth)
  {
    intersection->t = DBL_MAX;
    intersection->type = '0';
    ray.origin = intersection->pos;
    ray.dir = vector_normalize(vector_substract(ray.dir,
            vector_scalar(intersection->normal_v,
                    2 * vector_dot(ray.dir, intersection->normal_v))));
    get_closest_intersection(world, ray, intersection);
    if (intersection->type != '0')
      color = *intersection->color;
    else
    {
      color = new_color(0, 0, 0);
      intersection->color = &color;
      return (color);
    }
    i++;
  }
  return (color);
}

__host__ __device__ int		ray_tracer(t_world world, int x, int y)
{
	t_ray      			ray;
	t_intersection	intersection;
	t_color					color;
	int							i;

	i = 0;
	color = new_color(0, 0, 0);
	intersection.t = DBL_MAX;
	intersection.type = '0';
	intersection.id = -1;

	get_up_left(&world);
	get_ray_direction(world, &ray, x, y);
	get_closest_intersection(world, ray, &intersection);

	if (intersection.type == '0')
		return (0);
	if(world.keys.light_none == 1){
	if (intersection.reflection_coef == 0 && intersection.refraction_coef == 0)
		color = *intersection.color;
	if (intersection.reflection_coef != 0)
		color_add(&color, handle_reflection(world, ray, &intersection));
	if (intersection.refraction_coef != 0)
		color_add(&color, handle_refraction_transparence(world, ray, &intersection));
	if (intersection.chess->r != -1)
		color_add(&color, chess_effect(&intersection));
	}
	color_multiply(&color, world.ambient.color);
	color_scalar(&color, world.ambient.intensity);
	if (world.keys.light_none == 0)
		color = *intersection.color;
	while (i < world.lights_len && world.keys.light_none == 1)
	{
		get_light_at(world, &color, world.lights[i], intersection, ray);
		if (world.keys.pad_9 == 1)
			cartoon_effect(world, &color, world.lights[i], intersection, ray);
		i++;
	}
	return (get_color(color));
}
