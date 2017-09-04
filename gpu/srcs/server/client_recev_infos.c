/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_recev_infos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:38:13 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 17:25:31 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

static void		updated_objs_next(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'l')
	{
		free_obj(cluster->world, 'l');
		if (n == 0)
			return ;
		cluster->world->lights = (t_light*)malloc(sizeof(t_light) * n);
		ft_bzero(cluster->world->lights, n);
		ft_memcpy(cluster->world->lights, data->data, data->used);
		cluster->world->lights_len = n;
	}
	if (cmd == 'n')
	{
		free_obj(cluster->world, 'n');
		if (n == 0)
			return ;
		cluster->world->cones = (t_cone*)malloc(sizeof(t_cone) * n);
		ft_bzero(cluster->world->cones, n);
		ft_memcpy(cluster->world->cones, data->data, data->used);
		cluster->world->cones_len = n;
	}
}

void			updated_objs(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 's')
	{
		free_obj(cluster->world, 's');
		if (n == 0)
			return ;
		cluster->world->spheres = (t_sphere*)malloc(sizeof(t_sphere) * n);
		ft_bzero(cluster->world->spheres, n);
		ft_memcpy(cluster->world->spheres, data->data, data->used);
		cluster->world->spheres_len = n;
	}
	if (cmd == 'p')
	{
		free_obj(cluster->world, 'p');
		if (n == 0)
			return ;
		cluster->world->planes = (t_plane*)malloc(sizeof(t_plane) * n);
		ft_bzero(cluster->world->planes, n);
		ft_memcpy(cluster->world->planes, data->data, data->used);
		cluster->world->planes_len = n;
	}
	updated_objs_next(data, cmd, n, cluster);
}
