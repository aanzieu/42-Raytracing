/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:32:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/26 15:16:28 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

static void			*sd_cli(void *arg)
{
	t_cluster	*cluster;
	int			err;

	cluster = (t_cluster *)arg;
	if ((err = (send_informations_all(cluster, 'r', NULL, 0)) == 1))
		cluster->client_list->remove = 'o';
	pthread_exit(0);
}

int					launch_client(t_cluster *cluster, t_client *client)
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

void				remove_client_if(t_cluster *cluster, t_client **alst,
		t_client *last, t_client *tmp)
{
	t_client	*current;

	current = *alst;
	while (current)
	{
		if (current->remove == 'o')
		{
			cluster->nbr_clients--;
			if (current == *alst)
				*alst = current->next;
			else
				last->next = current->next;
			tmp = current;
			current = current->next;
			free(tmp->buffer);
			ft_putstr_fd("Client Connexion Dead\n", 1);
			free(tmp);
		}
		else
		{
			last = current;
			current = current->next;
		}
	}
}

void				free_buffer(t_cluster *cluster)
{
	int			nbr_clients;
	t_client	*tmp;

	tmp = cluster->client_list;
	nbr_clients = cluster->nbr_clients;
	while (tmp)
	{
		free(tmp->buffer);
		tmp->buffer = NULL;
		tmp = tmp->next;
	}
}

int					cluster_stratege(t_cluster *cluster)
{
	int			nbr;
	t_offsets	offsets;
	t_client	*clients;

	cluster->nbr_clients = 0;
	clients = cluster->client_list;
	while (clients != NULL && (cluster->nbr_clients++ | MAX_CLIENTS))
		clients = clients->next;
	clients = cluster->client_list;
	if ((nbr = cluster->nbr_clients) == 0)
		return (0);
	offsets.y_min = 0;
	while (nbr--)
	{
		if (clients)
		{
			offsets.y_min = nbr * WIN_HEIGHT / cluster->nbr_clients;
			offsets.y_max = offsets.y_min + WIN_HEIGHT / cluster->nbr_clients;
			clients->offsets.y_min = offsets.y_min;
			clients->offsets.y_max = offsets.y_max;
			send_informations(clients, 'w', &offsets, sizeof(offsets));
			clients = clients->next;
		}
	}
	return (1);
}
