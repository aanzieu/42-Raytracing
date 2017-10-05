/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/09/19 12:56:58 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

t_color				remove_color_channel(t_color color, char filter)
{
	if (filter == 'c')
		color.r = 0;
	else if (filter == 'r')
	{
		color.g = 0;
		color.b = 0;
	}
	return (color);
}

void				filter_anaglyph(t_world *world, t_color *buffer, int size,
		char filter)
{
	int		i;
	t_color	color;

	i = 0;
	(void)filter;
	(void)world;
	while (i < size)
	{
		color = int_to_rgb(world->a_h[i]);
		buffer[i] = remove_color_channel(color, filter);
		i++;
	}
}

/*
**	Move camera and redraw for right eye
*/

void				redraw_right_eye(t_world *world)
{
	world->camera.pos = vector_add(world->camera.pos,
	vector_scalar(world->camera.right_v, 0.1));
	get_camera_axes(&world->camera);
	get_viewplane(world);
	launch_cpu(world);
	world->camera.pos = vector_add(world->camera.pos,
	vector_scalar(world->camera.right_v, -0.1));
	get_camera_axes(&world->camera);
	get_viewplane(world);
}

void				anaglyph(t_world *world)
{
	t_color *red;
	t_color	*cyan;
	t_color	color;
	int		size;
	int		i;

	i = -1;
	color = new_color(0, 0, 0);
	size = world->viewplane.x_res * world->viewplane.y_res;
	red = (t_color *)malloc(size * sizeof(t_color));
	cyan = (t_color *)malloc(size * sizeof(t_color));
	filter_anaglyph(world, red, size, 'r');
	redraw_right_eye(world);
	filter_anaglyph(world, cyan, size, 'c');
	while (++i < size)
	{
		color = color_add(color, red[i]);
		color = color_add(color, cyan[i]);
		world->a_h[i] = rgb_to_int(color);
		color = color_scalar(color, 0);
	}
	free(red);
	free(cyan);
}
