/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 16:19:30 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/20 15:35:28 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_H
# define CLUSTER_H

#include <pthread.h>
#include "rt.h"
#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>

# define FIND_PORT 60000
# define MAX_CLIENTS 4

typedef struct		s_client
{
	int				fd;
	int				*buffer;
	struct s_client	*next;
	char			status;
}					t_client;

typedef struct		s_cluster
{
	t_client		*client_list;
	int				sockfd;
	pthread_t		client_thread;
	struct s_world	*world;
}					t_cluster;

void client_loop(int sockfd, t_cluster *cl);
int client_init(char *host_ip);
#endif
