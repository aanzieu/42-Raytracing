/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include "../../../../includes/rtv1.h"
	#include "../../cudaheader/gpu_rt.cuh"
}

__host__ __device__ void	get_camera_axes(t_camera *camera)
{
	t_vec3d tmp;

	tmp = new_vector(0, 1, 0);
	camera->dir_v = vector_normalize(
						vector_calculate(
							camera->pos,
							camera->look_at));
	camera->right_v = vector_normalize(
						vector_cross(
							vector_normalize(tmp),
							camera->dir_v));
	camera->up_v = vector_normalize(
					vector_cross(
						camera->dir_v,
						camera->right_v));
}
