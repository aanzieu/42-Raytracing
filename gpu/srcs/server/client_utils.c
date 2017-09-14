/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:06:39 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 17:25:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

void			free_obj_next(t_world *world, char cmd)
{
	if (cmd == 'y')
	{
		if(world->cylinders != NULL)
			free(world->cylinders);
		world->cylinders = NULL;
		world->cylinders_len = 0;
	}
	if (cmd == 'd')
	{
		if(world->disks != NULL)
			free(world->disks);
		world->disks = NULL;
		world->disks_len = 0;
	}
	if (cmd == 'h')
	{
		if(world->hyperboloids != NULL)
			free(world->hyperboloids);
		world->hyperboloids = NULL;
		world->hyperboloids_len = 0;
	}
	if (cmd == 'b')
	{
		if(world->paraboloids != NULL)
			free(world->paraboloids);
		world->paraboloids = NULL;
		world->paraboloids_len = 0;
	}
	if (cmd == 'o')
	{
		if(world->torus != NULL)
			free(world->torus);
		world->torus = NULL;
		world->torus_len = 0;
	}
	if (cmd == 'm')
	{
		if(world->mobius != NULL)
			free(world->mobius);
		world->mobius = NULL;
		world->mobius_len = 0;
	}
	if (cmd == 't')
	{
		if(world->triangles != NULL)
			free(world->triangles);
		world->triangles = NULL;
		world->triangles_len = 0;
	}
	if (cmd == 'u')
	{
		if(world->cubes != NULL)
			free(world->cubes);
		world->cubes = NULL;
		world->cubes_len = 0;
	}
}

void				free_obj(t_world *world, char cmd)
{
	if (cmd == 's')
	{
		if(world->spheres != NULL)
			free(world->spheres);
		world->spheres = NULL;
		world->spheres_len = 0;
	}
	if (cmd == 'p')
	{
		if(world->planes != NULL)
			free(world->planes);
		world->planes = NULL;
		world->planes_len = 0;
	}
	if (cmd == 'x')
	{
		if(world->cones != NULL)
			free(world->cones);
		world->cones = NULL;
		world->cones_len = 0;
	}
	if (cmd == 'l')
	{
		if(world->lights != NULL)
			free(world->lights);
		world->lights= NULL;
		world->lights_len = 0;
	}
	free_obj_next(world, cmd);
}

int					data_grow(t_data *data, size_t size)
{
	void	*new;
	size_t	new_total;

	new_total = data->total * size * 1.618;
	new = ft_memalloc(new_total);
	ft_memcpy(new, data->data, data->used);
	free(data->data);
	data->data = new;
	data->total = new_total;
	return (1);
}

int					data_recv(t_data *data, size_t size)
{
	if (!size)
		return (0);
	if (!data->total)
	{
		data->data = ft_memalloc(size);
		data->total = size;
		data->used = 0;
	}
	if (data->total >= data->used + size)
		return (1);
	if (data->total == 1)
		data->total++;
	return (data_grow(data, size));
}
