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

void		updated_objs_next3(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'o')
	{
		free_obj(cluster->world, 'o');
		if (n == 0)
			return ;
		if(!(cluster->world->torus = (t_torus*)malloc(sizeof(t_torus) * n)))
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
		if(!(cluster->world->mobius = (t_mobius*)malloc(sizeof(t_mobius) * n)))
			show_error("malloc mobius error cluster\n");			
		ft_bzero(cluster->world->mobius, n);
		ft_memcpy(cluster->world->mobius, data->data, data->used);
		cluster->world->mobius_len = n;
	}
	if (cmd == 't')
	{
		free_obj(cluster->world, 't');
		if (n == 0)
			return ;
		if(!(cluster->world->triangles = (t_triangle*)malloc(sizeof(t_triangle) * n)))
			show_error("malloc triangle error cluster\n");			
		ft_bzero(cluster->world->triangles, n);
		ft_memcpy(cluster->world->triangles, data->data, data->used);
		cluster->world->triangles_len = n;
	}
}


void		updated_objs_next2(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 'u')
	{
		free_obj(cluster->world, 'u');
		if (n == 0)
			return ;
		if(!(cluster->world->cubes = (t_cube*)malloc(sizeof(t_cube) * n)))
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
		if(!(cluster->world->cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * n)))
			show_error("malloc cylinders error cluster\n");			
		ft_bzero(cluster->world->cylinders, n);
		ft_memcpy(cluster->world->cylinders, data->data, data->used);
		cluster->world->cylinders_len = n;
	}
	if (cmd == 'd')
	{
		free_obj(cluster->world, 'd');
		if (n == 0)
			return ;
		if(!(cluster->world->disks = (t_disk*)malloc(sizeof(t_disk) * n)))
			show_error("malloc disks error cluster\n");			
		ft_bzero(cluster->world->disks, n);
		ft_memcpy(cluster->world->disks, data->data, data->used);
		cluster->world->disks_len = n;
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
		if(!(cluster->world->hyperboloids = (t_hyperboloid*)malloc(sizeof(t_hyperboloid) * n)))
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
		if(!(cluster->world->lights = (t_light*)malloc(sizeof(t_light) * n)))
			show_error("malloc light error cluster\n");
		ft_bzero(cluster->world->lights, n);
		ft_memcpy(cluster->world->lights, data->data, data->used);
		cluster->world->lights_len = n;
	}
	if (cmd == 'x')
	{
		free_obj(cluster->world, 'x');
		if (n == 0)
			return ;
		if(!(cluster->world->cones = (t_cone*)malloc(sizeof(t_cone) * n)))
			show_error("malloc cones error cluster\n");			
		ft_bzero(cluster->world->cones, n);
		ft_memcpy(cluster->world->cones, data->data, data->used);
		cluster->world->cones_len = n;
	}
	updated_objs_next2(data, cmd, n, cluster);
}

void			updated_objs(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 's')
	{
		free_obj(cluster->world, 's');
		if (n == 0)		
			return ;
		if(!(cluster->world->spheres = (t_sphere*)malloc(sizeof(t_sphere) * n)))
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
		if(!(cluster->world->planes = (t_plane*)malloc(sizeof(t_plane) * n)))
			show_error("erreur malloc spheres cluster\n");
		ft_bzero(cluster->world->planes, n);
		ft_memcpy(cluster->world->planes, data->data, data->used);
		cluster->world->planes_len = n;
	}
	if (cmd == 'b')
	{
		free_obj(cluster->world, 'b');
		if (n == 0)
			return ;
		if(!(cluster->world->paraboloids = (t_paraboloid*)malloc(sizeof(t_paraboloid) * n)))
			show_error("malloc paraboloids error cluster\n");			
		ft_bzero(cluster->world->paraboloids, n);
		ft_memcpy(cluster->world->paraboloids, data->data, data->used);
		cluster->world->paraboloids_len = n;
	}
	updated_objs_next(data, cmd, n, cluster);
}
