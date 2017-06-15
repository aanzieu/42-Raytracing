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
	#include "../../../../../includes/vectors.h"
}
#include <stdio.h>
#include <math.h>

__host__ __device__ t_vec3d	new_vector(double x, double y, double z)
{
	t_vec3d	var;

	var.x = x;
	var.y = y;
	var.z = z;
	return (var);
}

__host__ __device__ t_vec3d	vector_add(t_vec3d vect1, t_vec3d vect2)
{
	vect1.x += vect2.x;
	vect1.y += vect2.y;
	vect1.z += vect2.z;
	return (vect1);
}

__host__ __device__ t_vec3d	vector_substract(t_vec3d vect1, t_vec3d vect2)
{
	vect1.x += (-1) * vect2.x;
	vect1.y += (-1) * vect2.y;
	vect1.z += (-1) * vect2.z;
	return (vect1);
}

__host__ __device__ t_vec3d	vector_scalar(t_vec3d vect1, double scalar)
{
	vect1.x *= scalar;
	vect1.y *= scalar;
	vect1.z *= scalar;
	return (vect1);
}

__host__ __device__ t_vec3d	vector_normalize(t_vec3d vect1)
{
	double length;

	length = vector_length(vect1);
	vect1.x /= length;
	vect1.y /= length;
	vect1.z /= length;
	return (vect1);
}
