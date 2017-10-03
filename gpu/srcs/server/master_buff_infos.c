/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_buff_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:04:43 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 14:38:59 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

static void			*dup_data_next(t_cluster *cluster, char cmd, void *ret)
{
	size_t	size;

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
	return (dup_data_next(cluster, cmd, ret));
}

int					send_buffer_clients_next(t_cluster *cluster,
		t_client *clients, void *buffer)
{
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
	return (send_buffer_obj(cluster, clients, buffer));
}

int					send_buffer_clients(t_cluster *cluster, t_client *clients)
{
	void	*buffer;

	buffer = NULL;
	if ((clients->status & SEND_CAMERA) == 0)
	{
		if (!(buffer = dup_data(cluster, 'c', NULL)))
			return (0);
		if(!send_informations(clients, 'c', buffer, sizeof(t_camera)))
		{
			free(buffer);
			return(0);
		}
		free(buffer);
	}
	if ((clients->status & SEND_AMBIANT) == 0)
	{
		if (!(buffer = dup_data(cluster, 'z', NULL)))
			return (0);
		send_informations(clients, 'z', buffer, sizeof(t_ambient));
		free(buffer);
	}
	return (send_buffer_clients_next(cluster, clients, buffer));
}
