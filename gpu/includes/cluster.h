/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 16:19:30 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/26 15:13:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_H
# define CLUSTER_H

#include <pthread.h>
#include <rt.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

# define FIND_PORT 60000
# define MAX_CLIENTS 16

# define SEND_CAMERA 0
# define SEND_SPHERES 0
# define SEND_LIGHTS 0
# define SEND_PLANS 0
# define SEND_CONES 0
# define SEND_CYLINDERS 0

typedef struct			s_data
{
	void				*data;
	size_t				used;
	size_t				total;
}						t_data;

typedef struct			s_client
{
	t_offsets			offsets;
	int					fd;
	int					*buffer;
	char				status;
	char				remove;
	int					nbr_clients;
	struct s_client		*next;
}						t_client;

struct					s_offsets;

typedef struct			s_cluster
{
	pthread_t			client_thread;
	t_client			*client_list;
	t_offsets			offsets;
	int					sockfd;
	int					nbr_clients;
	int					th;
	int					y_min;
	int					y_max;
	struct s_world		*world;
}						t_cluster;

/*******************************************************************************
**                     CLIENT_CLUSTERING                                      **
*******************************************************************************/

int						serveur_address_serveur(char *ip, t_world *world);
void					client_loop(int sockfd, t_cluster *cl, t_data *data);
int						client_init(char *host_ip);
void					rt_cluster(t_world *world);
int						data_recv(t_data *data, size_t size);
void					process_send(char cmd, t_data *data, t_cluster *cluster, int sockfd);

/*******************************************************************************
**                     MASTER CLUSTERING                                      **
*******************************************************************************/

int						send_informations_all(t_cluster *cluster,
						char cmd, void *arg, size_t arg_size);
int						send_informations(t_client *clients,
						char cmd, void *arg, size_t arg_size);
int						cluster_stratege(t_cluster *cluster);
int						launch_client(t_cluster *cluster, t_client *client);
void					remove_client_if(t_cluster *cluster, t_client **alst,
						t_client *last, t_client *tmp);
void					free_buffer(t_cluster *cluster);

#endif
