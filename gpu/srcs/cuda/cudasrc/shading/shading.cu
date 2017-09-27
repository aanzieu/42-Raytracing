/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include "rt.h"
	#include "gpu_rt.h"
	#include <equation.h>
	#include <time.h>
}
#include <float.h>

__host__ __device__ t_color	direct_light(t_world world, t_color color,\
	t_light light, t_ray ray)
{
	t_vec3d	light_vector;
	t_color	direct_light;
	double 	angle;

	direct_light = new_color(10, 10, 10);
	light_vector = light.dir_v;
	angle = vector_dot(vector_scalar(world.camera.dir_v, -1), light_vector);
	direct_light = color_scalar(direct_light, angle);
	return (color_add(color, direct_light));
}

__host__ __device__ static double  get_distributed_shadow(t_world world,\
	t_light light, t_intersection collision)
{
	t_intersection	collision_tmp;
	t_light			box[9];
	t_ray				shadow;
	double			dist_intersection, coef;
	int 				i, j;

	i = 0;
	coef = 0;
	shadow.origin = collision.pos;
	while (i++ < 3)
	{
		j = 0;
		while (j++ < 3)
		{
			new_intersection(&collision_tmp);
			box[i].pos = (t_vec3d){light.pos.x + (0.05 * i), light.pos.y,
					light.pos.z + (0.05 * j)};
			shadow.dir = vector_calculate(collision.pos, box[i].pos);
			if (get_closest_intersection(world, shadow, &collision_tmp) == 1)
			{
				dist_intersection = vector_length(vector_calculate(collision.pos,
					collision_tmp.pos));
				if (dist_intersection < vector_length(shadow.dir))
					coef += collision_tmp.transparence_coef > 0 ?
						collision_tmp.transparence_coef : 1;
			}
		}
	}
	return (coef <= 0 ? 0 : 0.0000001 + (1 - (coef / 9)));
}

__host__ __device__ double		get_shadow(t_world world, t_light light,
	t_intersection collision)
{
	t_intersection	collision_tmp;
	t_ray				shadow;
	double			dist_light;
	double			dist_intersection;

	if (light.type == LIGHT_BOX)
		return (get_distributed_shadow(world, light, collision));
	collision_tmp.t = DBL_MAX;
	collision_tmp.type = '0';
	shadow.dir = vector_calculate(collision.pos, light.pos);
	shadow.origin = collision.pos;
	dist_light = vector_length(shadow.dir);
	collision_tmp.id = -1;
	if (get_closest_intersection(world, shadow, &collision_tmp) == 1)
	{
		dist_intersection = vector_length(vector_calculate(collision.pos,
												collision_tmp.pos));
		if (dist_intersection < dist_light)
			return (collision_tmp.transparence_coef > 0 ? collision_tmp.transparence_coef : -1);
	}
	return (0);
}

__host__ __device__ t_color	specular_light(t_world world, t_color color,\
	t_vec3d ray, t_intersection intersection, t_vec3d light_vector, t_light light)
{
	t_vec3d reflected_vector;
	t_vec3d raypos_tmp;
	double	specular_angle;

	raypos_tmp = vector_scalar(intersection.normal_v, 2 * vector_dot(ray, intersection.normal_v));
	reflected_vector = vector_substract(ray, raypos_tmp);
	reflected_vector = vector_normalize(reflected_vector);
	specular_angle = pow(vector_dot(light_vector, reflected_vector), 150);
	light.color = color_scalar(light.color, specular_angle);
	light.color = color_scalar(light.color, 0);
	//light.color = color_scalar(light.color, intersection.reflection_coef);
	light.color = color_scalar(light.color, light.intensity_coef);
	return (color_add(color, light.color));
}

__host__ __device__ t_vec3d	get_light_vector(t_world world, t_intersection intersection, t_light light)
{
	if (world.light_type == 1)
		return(vector_normalize(vector_calculate(intersection.pos, light.pos)));
	else
		return(light.dir_v);
}

__host__ __device__	t_color	get_light_at(t_world world, t_color color,\
	t_light light, t_intersection intersection, t_ray ray)
{
	t_vec3d		light_vector;
	t_color		tmp;
	double		angle, shadow_coef;

	tmp =  new_color(0, 0, 0);
	light_vector = get_light_vector(world, intersection, light);
	angle = vector_dot(intersection.normal_v, light_vector);
	shadow_coef = get_shadow(world, light, intersection);
	if (angle > 0 && shadow_coef >= 0)
	{
		tmp = color_add(color, intersection.color);
		tmp = color_scalar(tmp, angle);
		tmp = color_scalar(tmp, light.intensity_coef);
		if (shadow_coef > 0)
			tmp = color_scalar(tmp, shadow_coef);
		color = color_add(color, tmp);
		color = specular_light(world, color, ray.dir, intersection, light_vector, light);
	}
	return (color);
}
