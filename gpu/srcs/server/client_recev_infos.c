/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_recev_infos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:38:13 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 13:24:17 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

void		updated_objs_next2(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'u')
	{
		free_obj(cluster->world, 'u');
		if (n == 0)
			return ;
		if (!(cluster->world->cubes = (t_cube*)malloc(sizeof(t_cube) * n)))
			show_error("malloc cubes error cluster\n");
		ft_bzero(cluster->world->cubes, n);
		ft_memcpy(cluster->world->cubes, data->data, data->used);
		cluster->world->cubes_len = n;
	}
	if (cmd == 'y')
	{
		free_obj(cluster->world, 'y');
		if (n == 0)
			return ;
		if (!(cluster->world->cylinders =
					(t_cylinder*)malloc(sizeof(t_cylinder) * n)))
			show_error("malloc cylinders error cluster\n");
		ft_bzero(cluster->world->cylinders, n);
		ft_memcpy(cluster->world->cylinders, data->data, data->used);
		cluster->world->cylinders_len = n;
	}
	updated_objs_next3(data, cmd, n, cluster);
}

void		updated_objs_next(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'h')
	{
		free_obj(cluster->world, 'h');
		if (n == 0)
			return ;
		if (!(cluster->world->hyperboloids =
					(t_hyperboloid*)malloc(sizeof(t_hyperboloid) * n)))
			show_error("malloc hyperboloids error cluster\n");
		ft_bzero(cluster->world->hyperboloids, n);
		ft_memcpy(cluster->world->hyperboloids, data->data, data->used);
		cluster->world->hyperboloids_len = n;
	}
	if (cmd == 'l')
	{
		free_obj(cluster->world, 'l');
		if (n == 0)
			return ;
		if (!(cluster->world->lights = (t_light*)malloc(sizeof(t_light) * n)))
			show_error("malloc light error cluster\n");
		ft_bzero(cluster->world->lights, n);
		ft_memcpy(cluster->world->lights, data->data, data->used);
		cluster->world->lights_len = n;
	}
	updated_objs_next2(data, cmd, n, cluster);
}

void		updated_objs(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 's')
	{
		free_obj(cluster->world, 's');
		if (n == 0)
			return ;
		if (!(cluster->world->spheres =
					(t_sphere*)malloc(sizeof(t_sphere) * n)))
			show_error("erreur malloc spheres cluster\n");
		ft_bzero(cluster->world->spheres, n);
		ft_memcpy(cluster->world->spheres, data->data, data->used);
		cluster->world->spheres_len = n;
	}
	if (cmd == 'p')
	{
		free_obj(cluster->world, 'p');
		if (n == 0)
			return ;
		if (!(cluster->world->planes =
					(t_plane*)malloc(sizeof(t_plane) * n)))
			show_error("erreur malloc spheres cluster\n");
		ft_bzero(cluster->world->planes, n);
		ft_memcpy(cluster->world->planes, data->data, data->used);
		cluster->world->planes_len = n;
	}
	updated_objs_next(data, cmd, n, cluster);
}
