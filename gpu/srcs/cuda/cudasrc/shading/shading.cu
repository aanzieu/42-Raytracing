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
	#include "../../../../includes/rtv1.h"
}
#include <float.h>

__host__ __device__ int		get_shadow(t_world world, t_intersection collision, t_light light)
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

__host__ __device__ double		get_light_at(t_light light, t_intersection intersection)
{
	t_vec3d	light_vector;
	double	angle;
	t_color	color_def;

	color_def.r = 0;
	color_def.g = 0;
	color_def.b = 0;	
	light_vector = vector_normalize(vector_calculate(intersection.pos,
														light.pos));
	angle = vector_dot(intersection.normal_v, light_vector);
	if (angle <= 0)
		return (BLACK);
	else
	{
		color_add(&color_def, *intersection.color);
		color_scalar(&color_def, angle);		
		// color_def  = get_color(angle * intersection.color->r,
				// angle * intersection.color->g, angle * intersection.color->b);
			return (get_color(color_def.r, color_def.g, color_def.b));
	}
}