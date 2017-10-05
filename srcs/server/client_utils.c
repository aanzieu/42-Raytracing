/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:06:39 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 13:34:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

void			free_obj_next4(t_world *world, char cmd)
{
	if (cmd == 'b')
	{
		if (world->paraboloids != NULL)
			free(world->paraboloids);
		world->paraboloids = NULL;
		world->paraboloids_len = 0;
	}
}

void			free_obj_next3(t_world *world, char cmd)
{
	if (cmd == 'y')
	{
		if (world->cylinders != NULL)
			free(world->cylinders);
		world->cylinders = NULL;
		world->cylinders_len = 0;
	}
	if (cmd == 'd')
	{
		if (world->disks != NULL)
			free(world->disks);
		world->disks = NULL;
		world->disks_len = 0;
	}
	if (cmd == 'h')
	{
		if (world->hyperboloids != NULL)
			free(world->hyperboloids);
		world->hyperboloids = NULL;
		world->hyperboloids_len = 0;
	}
	free_obj_next4(world, cmd);
}

void			free_obj_next2(t_world *world, char cmd)
{
	if (cmd == 't')
	{
		if (world->triangles != NULL)
			free(world->triangles);
		world->triangles = NULL;
		world->triangles_len = 0;
	}
	if (cmd == 'u')
	{
		if (world->cubes != NULL)
			free(world->cubes);
		world->cubes = NULL;
		world->cubes_len = 0;
	}
	if (cmd == 'e')
	{
		if (world->h_cubes != NULL)
			free(world->h_cubes);
		world->h_cubes = NULL;
		world->h_cubes_len = 0;
	}
	free_obj_next3(world, cmd);
}

void			free_obj_next(t_world *world, char cmd)
{
	if (cmd == 'o')
	{
		if (world->torus != NULL)
			free(world->torus);
		world->torus = NULL;
		world->torus_len = 0;
	}
	if (cmd == 'm')
	{
		if (world->mobius != NULL)
			free(world->mobius);
		world->mobius = NULL;
		world->mobius_len = 0;
	}
	if (cmd == 'l')
	{
		if (world->lights != NULL)
			free(world->lights);
		world->lights = NULL;
		world->lights_len = 0;
	}
	free_obj_next2(world, cmd);
}

void			free_obj(t_world *world, char cmd)
{
	if (cmd == 's')
	{
		if (world->spheres != NULL)
			free(world->spheres);
		world->spheres = NULL;
		world->spheres_len = 0;
	}
	if (cmd == 'p')
	{
		if (world->planes != NULL)
			free(world->planes);
		world->planes = NULL;
		world->planes_len = 0;
	}
	if (cmd == 'x')
	{
		if (world->cones != NULL)
			free(world->cones);
		world->cones = NULL;
		world->cones_len = 0;
	}
	free_obj_next(world, cmd);
}
