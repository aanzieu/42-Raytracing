/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_buff_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:04:43 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 16:52:15 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

static void			*dup_data_obj(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

	if (cmd == 's')
	{
		size = sizeof(t_sphere) * cluster->world->spheres_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->spheres, size);
	}
	if (cmd == 'p')
	{
		size = sizeof(t_plane) * cluster->world->planes_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->planes, size);
	}
	if (cmd == 'n')
	{
		size = sizeof(t_cone) * cluster->world->cones_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cones, size);
	}
	return (ret);
}

static void			*dup_data(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

	if (cmd == 'c')
	{
		size = sizeof(t_camera);
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, &cluster->world->camera, sizeof(t_camera));
	}
	if (cmd == 'l')
	{
		size = sizeof(t_light) * cluster->world->lights_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->lights, size);
	}
	return (ret);
}

static int			send_buffer_obj_next(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	if ((clients->status & SEND_CONES) == 0)
	{
		if (!(buffer = dup_data_obj(cluster, 'n', NULL)))
			return (0);
		send_informations(clients, 'n', buffer,
				cluster->world->cones_len * sizeof(t_cone));
		free(buffer);
	}
	return (1);
}

static int			send_buffer_obj(t_cluster *cluster,
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
	return (send_buffer_obj_next(cluster, clients, buffer));
}

int					send_buffer_clients(t_cluster *cluster, t_client *clients)
{
	void	*buffer;

	buffer = NULL;
	if ((clients->status & SEND_CAMERA) == 0)
	{
		if (!(buffer = dup_data(cluster, 'c', NULL)))
			return (0);
		send_informations(clients, 'c', buffer, sizeof(t_camera));
		free(buffer);
	}
	if ((clients->status & SEND_LIGHTS) == 0)
	{
		if (!(buffer = dup_data(cluster, 'l', NULL)))
			return (0);
		send_informations(clients, 'l',
				buffer, cluster->world->lights_len * sizeof(t_light));
		free(buffer);
	}
	return (send_buffer_obj(cluster, clients, buffer));
}
