/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_send_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 14:48:56 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 16:52:13 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

static void		receive_status(t_client *clients, char ok)
{
	if (ok == 'c')
		clients->status |= SEND_CAMERA;
	if (ok == 's')
		clients->status |= SEND_SPHERES;
	if (ok == 'p')
		clients->status |= SEND_PLANS;
	if (ok == 'y')
		clients->status |= SEND_CONES;
	if (ok == 'l')
		clients->status |= SEND_LIGHTS;
	if (ok == 'y')
		clients->status |= SEND_CYLINDERS;
	if (ok == 'z')
		clients->status |= SEND_AMBIANT;
	if (ok == 'k')
		clients->status |= SEND_KEYS;
	if (ok == 'h')
		clients->status |= SEND_HYPERBOLOID;
	if (ok == 'p')
		clients->status |= SEND_PARABOLOID;
	if (ok == 'o')
		clients->status |= SEND_TORUS;
	if (ok == 'm')
		clients->status |= SEND_MOEBIUS;
	if (ok == 't')
		clients->status |= SEND_TRIANGLE;
	if (ok == 'u')
		clients->status |= SEND_CUBE;
	if (ok == 'd')
		clients->status |= SEND_DISK;
}

int				send_informations(t_client *clients,
		char cmd, void *arg, size_t arg_size)
{
	char	ok;

	if (!send(clients->fd, &cmd, 1, 0))
		return (0);
	if (!send(clients->fd, &arg_size, 8, 0))
		return (0);
	if (arg_size)
	{
		if (!send(clients->fd, arg, arg_size, 0))
			return (0);
	}
	if (cmd == 'r' && clients->buffer == NULL)
		clients->buffer = ft_memalloc(clients->main_size);
	if (cmd == 'r' && (!clients->buffer || recv(clients->fd, clients->buffer,
					clients->main_size, MSG_WAITALL) == 0))
		return (0);
	if (recv(clients->fd, &ok, 1, 0) == 0)
		return (0);
	receive_status(clients, ok);
	return (1);
}

int				send_informations_all(t_cluster *cluster,
		char cmd, void *arg, size_t arg_size)
{
	t_client	*clients;
	int			nbr_clients;
	int			clients_alive;

	clients_alive = 0;
	nbr_clients = 0;
	clients = cluster->client_list;
	if (clients != NULL)
	{
		if (cmd == 'r')
			clients_alive = send_buffer_clients(cluster, clients);
		if (clients_alive)
			clients_alive = send_informations(clients, cmd, arg, arg_size);
		if (!clients_alive)
			return (1);
		return (0);
	}
	return (1);
}
