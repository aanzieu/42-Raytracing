/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 16:19:30 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/24 13:44:36 by aanzieu          ###   ########.fr       */
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

# define SEND_CAMERA 0
# define SEND_SPHERES 0
# define SEND_LIGHTS 0
# define SEND_PLANS 0

typedef struct		s_data
{
	void			*data;
	size_t			used;
	size_t			total;
}					t_data;

typedef struct		s_client
{
	int				fd;
	int				*buffer;
	struct s_client	*next;
	char			status;
}					t_client;

typedef struct		s_offsets
{
	int				y_min;
	int				y_max;
}					t_offsets;

typedef struct		s_cluster
{
	t_client		*client_list;
	int				sockfd;
	pthread_t		client_thread;
	struct s_world	*world;
	int				nbr_clients;
	t_offsets		offsets;
}					t_cluster;



int		serveur_address_serveur(char *ip, t_world *world);
void 	client_loop(int sockfd, t_cluster *cl, t_data *data);
int 	client_init(char *host_ip);
void	rt_cluster(t_world *world);

/*******************************************************************************
**                     MASTER CLUSTERING                                        	  **
*******************************************************************************/

void		send_informations_all(t_cluster *cluster, char cmd, void *arg, size_t arg_size);
void		cluster_stratege(t_cluster *cluster);

int			data_recv(t_data *data, size_t size);
void		process_send(char cmd, t_data *data, t_cluster *cluster, int sockfd);
#endif
