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
	#include <rt.h>
	#include <gpu_rt.h>
}

__host__ __device__ void	move_forward(t_world *world)
{
	translate(&world->camera.pos, 0, 0, 1);
	translate(&world->camera.look_at, 0, 0, 1);
	world->redraw = 1;
//	get_camera_axes(&world->camera);
}

__host__ __device__ void	move_backward(t_world *world)
{
	translate(&world->camera.pos, 0, 0, -1);
	translate(&world->camera.look_at, 0, 0, -1);
	world->redraw = 1;
	//get_camera_axes(&world->camera);
}

__host__ __device__ void	move_left(t_world *world)
{
	translate(&world->camera.pos, -1, 0, 0);
	translate(&world->camera.look_at, -1, 0, 0);
	world->redraw = 1;
	//get_camera_axes(&world->camera);
}

__host__ __device__ void	move_right(t_world *world)
{
	translate(&world->camera.pos, 1, 0, 0);
	translate(&world->camera.look_at, 1, 0, 0);
	world->redraw = 1;
	//get_camera_axes(&world->camera);
}

__host__ __device__ void	move_down(t_world *world)
{
	translate(&world->camera.pos, 0, -1, 0);
	translate(&world->camera.look_at, 0, -1, 0);
	world->redraw = 1;
	//get_camera_axes(&world->camera);
}


__host__ __device__ void	move_up(t_world *world)
{
	translate(&world->camera.pos, 0, 1, 0);
	translate(&world->camera.look_at, 0, 1, 0);
	world->redraw = 1;
	//get_camera_axes(&world->camera);
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
