/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <vectors.h>
	#include <gpu_rt.h>
}
#include <math.h>

__host__ __device__ t_vec3d	vector_calculate(t_vec3d vect1, t_vec3d vect2)
{
	return (vector_substract(vect2, vect1));
}

__host__ __device__ t_vec3d	vector_cross(t_vec3d vect1, t_vec3d vect2)
{
	t_vec3d tmp;

	tmp.x = vect1.y * vect2.z - vect1.z * vect2.y;
	tmp.y = vect1.z * vect2.x - vect1.x * vect2.z;
	tmp.z = vect1.x * vect2.y - vect1.y * vect2.x;
	return (tmp);
}

__host__ __device__ double	vector_dot(t_vec3d vect1, t_vec3d vect2)
{
	double result;

	result = vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z;
	return (result);
}

__host__ __device__ double	vector_length(t_vec3d vect1)
{
	double length;

	length = sqrt(pow(vect1.x, 2) + pow(vect1.y, 2) + pow(vect1.z, 2));
	return (length);
}
