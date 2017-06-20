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
}
#include "gpu_rt.h"
#include <float.h>

__host__ __device__ int		get_shadow(t_world world, t_light light,
													t_intersection collision)
{
	t_intersection	collision_tmp;
	t_ray			shadow;
	double			dist_light;
	double			dist_intersection;

	collision_tmp.t = DBL_MAX;
	collision_tmp.type = '0';
	shadow.dir = vector_calculate(collision.pos, light.pos);
	shadow.origin = collision.pos;
	dist_light = vector_length(shadow.dir);
	if (get_closest_intersection(world, shadow, &collision_tmp) == 1)
	{
		dist_intersection = vector_length(vector_calculate(collision.pos,
												collision_tmp.pos));
		if (dist_intersection < dist_light)
			return (1);
	}
	return (0);
}

__host__ __device__	void	get_light_at(t_world world, t_color *color,
									t_light light, t_intersection intersection)
{
	t_vec3d	light_vector;
	t_color	tmp;
	double	angle;	

	tmp =  new_color(0, 0, 0);
	light_vector = vector_normalize(vector_calculate(intersection.pos,
														light.pos));
	angle = vector_dot(intersection.normal_v, light_vector);
	color_add(color, *intersection.color);
	color_scalar(color, world.indexes.ambient);
	if (angle > 0 && get_shadow(world, light, intersection) == 0)
	{
		color_add(&tmp, *intersection.color);
		color_scalar(&tmp, angle);				
		color_add(color, tmp);
	}
}
