/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_send_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:48:56 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/26 14:57:49 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

int		send_informations(t_client *clients, char cmd, void *arg, size_t arg_size)
{
	char	ok;
	size_t	main_size;

	main_size = sizeof(int) * (WIN_WIDTH * (clients->offsets.y_max - clients->offsets.y_min));
	if(!send(clients->fd, &cmd, 1, 0))
		return(0);
	if(!send(clients->fd, &arg_size, 8, 0))
		return(0);
	if(arg_size)
	{
		if(!send(clients->fd, arg, arg_size, 0))
			return(0);
	}
	if (cmd == 'r' && clients->buffer == NULL)
		clients->buffer = ft_memalloc(main_size);
	if (cmd == 'r' && (!clients->buffer || recv(clients->fd, clients->buffer, main_size, MSG_WAITALL) == 0))
		return(0);
	if (recv(clients->fd, &ok, 1, 0) == 0)
		return(0);
	if (ok == 'c')
		clients->status |= SEND_CAMERA;
	if (ok == 's')
		clients->status |= SEND_SPHERES;
	if (ok == 'p')
		clients->status |= SEND_PLANS;
	if (ok == 'n')
		clients->status |= SEND_CONES;
	if (ok == 'l')
		clients->status |= SEND_LIGHTS;
	return(1);
}

void			*dup_data(t_cluster *cluster, char cmd)
{
	void	*ret;
	size_t	size;

	ret = NULL;
	if(cmd == 'c')
	{
		ret = ft_memalloc(sizeof(t_camera));
		if(ret != NULL)
			ret = ft_memcpy(ret, &cluster->world->camera, sizeof(t_camera));
	}
	if(cmd == 's')
	{
		size = sizeof(t_sphere) * cluster->world->spheres_len;
		ret = ft_memalloc(size);
		if(ret != NULL)
			ret = ft_memcpy(ret, cluster->world->spheres, size);
	}
	if(cmd == 'p')
	{
		size = sizeof(t_plane) * cluster->world->planes_len;
		ret = ft_memalloc(size);
		if(ret != NULL)
			ret = ft_memcpy(ret, cluster->world->planes, size);
	}
	if(cmd == 'n')
	{
		size = sizeof(t_cone) * cluster->world->cones_len;
		ret = ft_memalloc(size);
		if(ret != NULL)
			ret = ft_memcpy(ret, cluster->world->cones, size);
	}
	if(cmd == 'l')
	{
		size = sizeof(t_light) * cluster->world->lights_len;
		ret = ft_memalloc(size);
		if(ret != NULL)
			ret = ft_memcpy(ret, cluster->world->lights, size);
	}
	return(ret);
}

static		int send_buffer_clients(t_cluster *cluster, t_client *clients)
{
	void	*buffer;

	buffer = NULL;
	if ((clients->status & SEND_CAMERA) == 0)
	{
		if (!(buffer = dup_data(cluster, 'c')))
			return (0);
		send_informations(clients, 'c', buffer, sizeof(t_camera));
	}
	if ((clients->status & SEND_SPHERES) == 0)
	{
		if (!(buffer = dup_data(cluster, 's')))
			return (0);
		send_informations(clients, 's', buffer, cluster->world->spheres_len * sizeof(t_sphere));
	}
	if ((clients->status & SEND_PLANS) == 0)
	{
		if (!(buffer = dup_data(cluster, 'p')))
			return (0);
		send_informations(clients, 'p', buffer, cluster->world->planes_len * sizeof(t_plane));
	}
	if ((clients->status & SEND_CONES) == 0)
	{
		if (!(buffer = dup_data(cluster, 'n')))
			return (0);
		send_informations(clients, 'n', buffer, cluster->world->cones_len * sizeof(t_cone));
	}
	if ((clients->status & SEND_LIGHTS) == 0)
	{
		if (!(buffer = dup_data(cluster, 'l')))
			return (0);
		send_informations(clients, 'l', buffer, cluster->world->lights_len * sizeof(t_light));
	}
	free(buffer);
	return (1);
}

int				send_informations_all(t_cluster *cluster, char cmd, void *arg, size_t arg_size)
{
	t_client	*clients;
	int			nbr_clients;
	int			clients_alive = 0;

	nbr_clients = 0;
	clients = cluster->client_list;
	if(clients != NULL)
	{
		if (cmd == 'r')
			clients_alive = send_buffer_clients(cluster, clients);
		if(clients_alive)
			clients_alive = send_informations(clients, cmd, arg, arg_size);
		if (!clients_alive)
			return (1);
		return(0);
	}
	return(1);
}
