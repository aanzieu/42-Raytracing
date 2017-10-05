/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/03/17 14:07:23 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include <rt.h>
	#include <gpu_rt.h>
	#include <vectors.h>
}
#include <math.h>
#include <vectors.h>

__host__ __device__ void	rotate(t_vec3d *point, double degrees, char axis)
{
	t_vec3d tmp;

	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;
	degrees = (-1) * deg_to_radians(degrees);
	if (axis == 'z')
	{
		point->x = tmp.x * cos(degrees) - tmp.y * sin(degrees);
		point->y = tmp.x * sin(degrees) + tmp.y * cos(degrees);
	}
	else if (axis == 'x')
	{
		point->y = tmp.y * cos(degrees) - tmp.z * sin(degrees);
		point->z = tmp.y * sin(degrees) + tmp.z * cos(degrees);
	}
	else if (axis == 'y')
	{
		point->z = tmp.z * cos(degrees) - tmp.x * sin(degrees);
		point->x = tmp.z * sin(degrees) + tmp.x * cos(degrees);
	}
}

__host__ __device__ void	cam_rot(t_camera *camera, double degrees, char axis)
{
	degrees = (-1) * deg_to_radians(degrees);
	if (axis == 'z')
	{
		camera->look_at.z -= camera->pos.z;
		camera->look_at.y -= camera->pos.y;
		rotate(&camera->look_at, degrees, 'z');
		camera->look_at.z += camera->pos.z;
		camera->look_at.y += camera->pos.y;
		get_camera_axes(camera);
	}
	else if (axis == 'x')
	{
		camera->look_at.z -= camera->pos.z;
		camera->look_at.y -= camera->pos.y;
		rotate(&camera->look_at, degrees, 'x');
		camera->look_at.z += camera->pos.z;
		camera->look_at.y += camera->pos.y;
		get_camera_axes(camera);
	}
	else if (axis == 'y')
	{
		camera->look_at.z -= camera->pos.z;
		camera->look_at.x -= camera->pos.x;
		rotate(&camera->look_at, degrees, 'y');
		camera->look_at.z += camera->pos.z;
		camera->look_at.x += camera->pos.x;
		get_camera_axes(camera);
	}
}
