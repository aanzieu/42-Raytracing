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

void		updated_objs_next(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	// (void)data;
	// (void)cmd;
	// (void)cluster;
	// (void)n;
	if (cmd == 'l')
	{
		printf("NBR DE LIGHTS avant Free %d\n", cluster->world->lights_len);
		free_obj(cluster->world, 'l');
		printf("free cluster lights ok\n");
		if (n == 0){
			printf("pas de lights\n");
		
			return ;
		}
		if(!(cluster->world->lights = (t_light*)malloc(sizeof(t_light) * n)))
			show_error("malloc light error cluster\n");
		ft_bzero(cluster->world->lights, n);
		ft_memcpy(cluster->world->lights, data->data, data->used);
		cluster->world->lights_len = n;
		printf("NBR DE LIGHTS apres Malloc %d\n", cluster->world->lights_len);
		printf("cluster lights ok \n");
	}
	// if (cmd == 'x')
	// {
	// 	free_obj(cluster->world, 'x');
	// 	if (n == 0)
	// 		return ;
	// 	cluster->world->cones = (t_cone*)malloc(sizeof(t_cone) * n);
	// 	ft_bzero(cluster->world->cones, n);
	// 	ft_memcpy(cluster->world->cones, data->data, data->used);
	// 	cluster->world->cones_len = n;
	// }
	// if (cmd == 'y')
	// {
	// 	free_obj(cluster->world, 'y');
	// 	if (n == 0)
	// 		return ;
	// 	cluster->world->cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * n);
	// 	ft_bzero(cluster->world->cylinders, n);
	// 	ft_memcpy(cluster->world->cylinders, data->data, data->used);
	// 	cluster->world->cylinders_len = n;
	// }
}

void			updated_objs(t_data *data, char cmd,
		short n, t_cluster *cluster)
{
	if (cmd == 's')
	{
		free_obj(cluster->world, 's');
		printf("NBR DE SPHERES avant Free %d\n", cluster->world->spheres_len);
		printf("free cluster spheres ok\n");		
		if (n == 0){
			printf("pas de spheres\n");
		
			return ;
		}
		printf("VALEUR DE N = %d", n);
		if(!(cluster->world->spheres = (t_sphere*)malloc(sizeof(t_sphere) * n)))
			show_error("erreur malloc spheres cluster\n");
		ft_bzero(cluster->world->spheres, n);
		ft_memcpy(cluster->world->spheres, data->data, data->used);
		cluster->world->spheres_len = n;
		printf("NBR DE SPHERES apres Free %d\n", cluster->world->spheres_len);
		printf("cluster spheres ok \n");
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
	updated_objs_next(data, cmd, n, cluster);
}
