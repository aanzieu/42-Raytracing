/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 14:53:17 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 16:39:38 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/cluster.h>

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
	t_client	*tmp;

	tmp = cluster->client_list;
	while (tmp)
	{
		free(tmp->buffer);
		tmp->buffer = NULL;
		tmp = tmp->next;
	}
}
