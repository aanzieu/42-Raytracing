/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:32:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 13:52:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

static void		*sd_cli(void *arg)
{
	t_cluster	*cluster;
	int			err;

	cluster = (t_cluster *)arg;
	if ((err = (send_informations_all(cluster, 'r', NULL, 0)) == 1))
		cluster->client_list->remove = 'o';
	pthread_exit(0);
}

int				launch_client(t_cluster *cluster, t_client *client)
{
	t_cluster				tab[cluster->nbr_clients];
	int						i;
	void					*status;
	int						err;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	i = -1;
	while (++i < cluster->nbr_clients)
	{
		tab[i].client_list = client;
		tab[i].th = i;
		tab[i].world = cluster->world;
		tab[i].y_min = client->offsets.y_min;
		tab[i].y_max = client->offsets.y_max;
		if (pthread_create(&cluster->world->thread[i], NULL, &sd_cli, &tab[i]))
			ft_putendl_fd("Error : Can't init thread_cluster\n", 1);
		client = client->next;
	}
	i = -1;
	while (++i < cluster->nbr_clients)
		if ((err = pthread_join(cluster->world->thread[i], &status)))
			ft_putendl_fd(strerror(err), 1);
	pthread_mutex_unlock(&mutex);
	return (0);
}

static void		send_offsets(t_client *clients, t_cluster *cluster, int nbr)
{
	t_offsets	offsets;

	offsets.y_min = 0;
	while (nbr--)
	{
		if (clients)
		{
			offsets.y_min = nbr * (double)WIN_HEIGHT / cluster->nbr_clients;
			offsets.y_max = offsets.y_min + (double)WIN_HEIGHT /
				cluster->nbr_clients;
			offsets.render_factor = cluster->world->render_factor;
			offsets.aa = cluster->world->aa;
			offsets.mode = cluster->world->mode;
			offsets.ob_save = cluster->world->ob_save;
			offsets.id_save = cluster->world->id_save;
			clients->offsets.y_min = offsets.y_min;
			clients->offsets.y_max = offsets.y_max;
			clients->main_size = sizeof(int)
				* (clients->ww
						* (clients->offsets.y_max - clients->offsets.y_min));
			send_informations(clients, 'w', &offsets, sizeof(offsets));
			clients = clients->next;
		}
	}
}

int				cluster_stratege(t_cluster *cluster)
{
	int			nbr;
	t_client	*clients;

	cluster->nbr_clients = 0;
	clients = cluster->client_list;
	while (clients != NULL && (cluster->nbr_clients++ | MAX_CLIENTS))
		clients = clients->next;
	clients = cluster->client_list;
	if ((nbr = cluster->nbr_clients) == 0)
		return (0);
	send_offsets(clients, cluster, nbr);
	return (1);
}
