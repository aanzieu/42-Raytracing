/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_buff_infos_next.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 14:33:55 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 14:41:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

int			send_buffer_obj_next3(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	if ((clients->status & SEND_PARABOLOID) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'b', NULL)))
			return (0);
		send_informations(clients, 'b', buffer,
				cluster->world->paraboloids_len * sizeof(t_paraboloid));
		free(buffer);
	}
	if ((clients->status & SEND_DISK) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'd', NULL)))
			return (0);
		send_informations(clients, 'd', buffer,
				cluster->world->disks_len * sizeof(t_disk));
		free(buffer);
	}
	if ((clients->status & SEND_TORUS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'o', NULL)))
			return (0);
		send_informations(clients, 'o', buffer,
				cluster->world->torus_len * sizeof(t_torus));
		free(buffer);
	}
	return (1);
}

int			send_buffer_obj_next2(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	if ((clients->status & SEND_CONES) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'x', NULL)))
			return (0);
		send_informations(clients, 'x', buffer,
				cluster->world->cones_len * sizeof(t_cone));
		free(buffer);
	}
	if ((clients->status & SEND_CYLINDERS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'y', NULL)))
			return (0);
		send_informations(clients, 'y', buffer,
				cluster->world->cylinders_len * sizeof(t_cylinder));
		free(buffer);
	}
	if ((clients->status & SEND_HYPERBOLOID) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'h', NULL)))
			return (0);
		send_informations(clients, 'h', buffer,
				cluster->world->hyperboloids_len * sizeof(t_hyperboloid));
		free(buffer);
	}
	return (send_buffer_obj_next3(cluster, clients, buffer));
}

int			send_buffer_obj_next(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	if ((clients->status & SEND_MOEBIUS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'm', NULL)))
			return (0);
		send_informations(clients, 'm', buffer,
				cluster->world->mobius_len * sizeof(t_mobius));
		free(buffer);
	}
	if ((clients->status & SEND_TRIANGLE) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 't', NULL)))
			return (0);
		send_informations(clients, 't', buffer,
				cluster->world->triangles_len * sizeof(t_triangle));
		free(buffer);
	}
	if ((clients->status & SEND_CUBE) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'u', NULL)))
			return (0);
		send_informations(clients, 'u', buffer,
				cluster->world->cubes_len * sizeof(t_cube));
		free(buffer);
	}
	return (send_buffer_obj_next2(cluster, clients, buffer));
}

int			send_buffer_obj(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	if ((clients->status & SEND_PLANS) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'p', NULL)))
			return (0);
		send_informations(clients, 'p', buffer,
				cluster->world->planes_len * sizeof(t_plane));
		free(buffer);
	}
	if ((clients->status & SEND_SPHERES) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 's', NULL)))
			return (0);
		send_informations(clients, 's', buffer,
				cluster->world->spheres_len * sizeof(t_sphere));
		free(buffer);
	}
	if ((clients->status & SEND_H_CUBE) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'e', NULL)))
			return (0);
		send_informations(clients, 'e', buffer,
				cluster->world->h_cubes_len * sizeof(t_h_cube));
		free(buffer);
	}
	return (send_buffer_obj_next(cluster, clients, buffer));
}
