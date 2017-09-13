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
		printf("valeur de SIZE SPHERE LEN BUFF INFO %zu\n", size);
	}
	if (cmd == 'p')
	{
		size = sizeof(t_plane) * cluster->world->planes_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->planes, size);
	}
	if (cmd == 'x')
	{
		size = sizeof(t_cone) * cluster->world->cones_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cones, size);
	}
	if (cmd == 'y')
	{
		size = sizeof(t_cylinder) * cluster->world->cylinders_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->cylinders, size);
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
	if (cmd == 'z')
	{
		size = sizeof(t_ambient);
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, &cluster->world->ambient, sizeof(t_ambient));
	}
	if (cmd == 'k')
	{
		size = sizeof(t_keys);
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, &cluster->world->keys, sizeof(t_keys));
	}
	if (cmd == 'l')
	{
		size = sizeof(t_light) * cluster->world->lights_len;
		if ((ret = ft_memalloc(size)) != NULL)
			ret = ft_memcpy(ret, cluster->world->lights, size);
	}
	return (ret);
}

int			send_buffer_obj_next(t_cluster *cluster,
		t_client *clients, void *buffer)
{
	(void)cluster;
	(void)clients;
	(void)buffer;
	// if ((clients->status & SEND_CONES) == 0)
	// {
	// 	if (!(buffer = dup_data_obj(cluster, 'x', NULL)))
	// 		return (0);
	// 	send_informations(clients, 'x', buffer,
	// 			cluster->world->cones_len * sizeof(t_cone));
	// 	free(buffer);
	// 	// return (1);
	// }
	// if ((clients->status & SEND_CYLINDERS) == 0)
	// {
	// 	if (!(buffer = dup_data_obj(cluster, 'y', NULL)))
	// 		return (0);
	// 	send_informations(clients, 'y', buffer,
	// 			cluster->world->cylinders_len * sizeof(t_cylinder));
	// 	free(buffer);
	// 	// return(1);
	// }
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
	// if ((clients->status & SEND_SPHERES) == 0)
	// {
	// 	if (!(buffer = dup_data_obj(cluster, 's', NULL)))
	// 		return (0);
	// 	send_informations(clients, 's', buffer,
	// 			cluster->world->spheres_len * sizeof(t_sphere));
	// 	free(buffer);
	// }
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
	if ((clients->status & SEND_AMBIANT) == 0)
	{
		if (!(buffer = dup_data(cluster, 'z', NULL)))
			return (0);
		send_informations(clients, 'z', buffer, sizeof(t_ambient));
		free(buffer);
	}
	if ((clients->status & SEND_KEYS) == 0)
	{
		if (!(buffer = dup_data(cluster, 'k', NULL)))
			return (0);
		send_informations(clients, 'k', buffer, sizeof(t_keys));
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
	if ((clients->status & SEND_SPHERES) == 0)// && cluster->world->spheres_len != 0)

	{
		if (!(buffer = dup_data_obj(cluster, 's', NULL)))
			return (0);
		printf("jenvoie information de spheres 's' avec spheres_len = %lu\n", cluster->world->spheres_len * sizeof(t_sphere));
		send_informations(clients, 's', buffer,
				cluster->world->spheres_len * sizeof(t_sphere));
		free(buffer);
	}
	if(buffer != NULL)
		printf("buffer pas vide\n");
	// free(buffer);
	return (send_buffer_obj(cluster, clients, buffer));
}
