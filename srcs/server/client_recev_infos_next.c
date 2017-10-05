/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_recev_infos_next.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 13:21:35 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 13:23:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

void		updated_objs_next6(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'x')
	{
		free_obj(cluster->world, 'x');
		if (n == 0)
			return ;
		if (!(cluster->world->cones = (t_cone*)malloc(sizeof(t_cone) * n)))
			show_error("malloc cones error cluster\n");
		ft_bzero(cluster->world->cones, n);
		ft_memcpy(cluster->world->cones, data->data, data->used);
		cluster->world->cones_len = n;
	}
}

void		updated_objs_next5(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'b')
	{
		free_obj(cluster->world, 'b');
		if (n == 0)
			return ;
		if (!(cluster->world->paraboloids =
					(t_paraboloid*)malloc(sizeof(t_paraboloid) * n)))
			show_error("malloc paraboloids error cluster\n");
		ft_bzero(cluster->world->paraboloids, n);
		ft_memcpy(cluster->world->paraboloids, data->data, data->used);
		cluster->world->paraboloids_len = n;
	}
	if (cmd == 'd')
	{
		free_obj(cluster->world, 'd');
		if (n == 0)
			return ;
		if (!(cluster->world->disks = (t_disk*)malloc(sizeof(t_disk) * n)))
			show_error("malloc disks error cluster\n");
		ft_bzero(cluster->world->disks, n);
		ft_memcpy(cluster->world->disks, data->data, data->used);
		cluster->world->disks_len = n;
	}
	updated_objs_next6(data, cmd, n, cluster);
}

void		updated_objs_next4(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'e')
	{
		free_obj(cluster->world, 'e');
		if (n == 0)
			return ;
		if (!(cluster->world->h_cubes =
					(t_h_cube*)malloc(sizeof(t_h_cube) * n)))
			show_error("malloc h_cubes error cluster\n");
		ft_bzero(cluster->world->h_cubes, n);
		ft_memcpy(cluster->world->h_cubes, data->data, data->used);
		cluster->world->h_cubes_len = n;
	}
	if (cmd == 't')
	{
		free_obj(cluster->world, 't');
		if (n == 0)
			return ;
		if (!(cluster->world->triangles =
					(t_triangle*)malloc(sizeof(t_triangle) * n)))
			show_error("malloc triangle error cluster\n");
		ft_bzero(cluster->world->triangles, n);
		ft_memcpy(cluster->world->triangles, data->data, data->used);
		cluster->world->triangles_len = n;
	}
	updated_objs_next5(data, cmd, n, cluster);
}

void		updated_objs_next3(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'o')
	{
		free_obj(cluster->world, 'o');
		if (n == 0)
			return ;
		if (!(cluster->world->torus =
					(t_torus*)malloc(sizeof(t_torus) * n)))
			show_error("malloc torus error cluster\n");
		ft_bzero(cluster->world->torus, n);
		ft_memcpy(cluster->world->torus, data->data, data->used);
		cluster->world->torus_len = n;
	}
	if (cmd == 'm')
	{
		free_obj(cluster->world, 'm');
		if (n == 0)
			return ;
		if (!(cluster->world->mobius = (t_mobius*)malloc(sizeof(t_mobius) * n)))
			show_error("malloc mobius error cluster\n");
		ft_bzero(cluster->world->mobius, n);
		ft_memcpy(cluster->world->mobius, data->data, data->used);
		cluster->world->mobius_len = n;
	}
	updated_objs_next4(data, cmd, n, cluster);
}
