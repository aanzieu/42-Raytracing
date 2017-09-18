/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
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

__host__ __device__ t_vec3d	new_vector(double x, double y, double z)
{
	// t_vec3d	var;
	//
	// var.x = x;
	// var.y = y;
	// var.z = z;
	return ((t_vec3d){x, y, z});
}

__host__ __device__ t_vec3d	vector_add(t_vec3d vect1, t_vec3d vect2)
{
	// vect1.x += vect2.x;
	// vect1.y += vect2.y;
	// vect1.z += vect2.z;
	return ((t_vec3d){vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z});
}

__host__ __device__ t_vec3d	vector_substract(t_vec3d vect1, t_vec3d vect2)
{
	// vect1.x -= vect2.x;
	// vect1.y -= vect2.y;
	// vect1.z -= vect2.z;
	return ((t_vec3d){vect1.x - vect2.x, vect1.y - vect2.y, vect1.z - vect2.z});
}

__host__ __device__ t_vec3d	vector_scalar(t_vec3d vect1, double scalar)
{
	// vect1.x *= scalar;
	// vect1.y *= scalar;
	// vect1.z *= scalar;
	return ((t_vec3d){vect1.x * scalar, vect1.y * scalar, vect1.z * scalar});
}

__host__ __device__ t_vec3d	vector_normalize(t_vec3d vect1)
{
	double length;

	length = vector_length(vect1);
	// vect1.x /= length;
	// vect1.y /= length;
	// vect1.z /= length;
	return ((t_vec3d){vect1.x / length, vect1.y / length, vect1.z / length});
}
