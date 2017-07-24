/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/24 15:52:37 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cluster.h>
#include <rt.h>
#include "../../gpu/srcs/cuda/cudaheader/gpu_rt.h"
#include <parse.h>
#include <display.h>
#include <unistd.h>

/*
 ** MISE EN PLACE DE RECEPTION DONNEE CLIENT
*/


void client_loop(int sockfd, t_cluster *cluster, t_data *data)
{
	char	cmd;
	int		ret;
	size_t	data_size;
	size_t	data_used;

	if ((ret = recv(sockfd, &cmd, 1, 0)) != 1)
	{
		return;
	}
	printf("commande recu : %c\n", cmd);
	data_used = 0;
	if ((ret = recv(sockfd, &data_size, 8, 0)) <= 0)
		return ;
	if (data_size)
	{
		data_recv(data, data_size);
		recv(sockfd, data->data, data_size, 0);
		printf("data recu\n");
		data->used = data_size;
	}
//	load_data(cl->world);
//	printf("je sors de data\n");
//	rt(cl->world);
	process_send(cmd, data, cluster, sockfd);
	client_loop(sockfd, cluster, data);
}

int client_init(char *host_ip)
{
	int					sockfd;
	int					ret;
	int					port_offs;
	struct hostent		*host;
	struct sockaddr_in	sin;

	if ((host = gethostbyname(host_ip)) == NULL)
	{
		printf("cant get hostname\n");
		exit(1);
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("cant load socket\n");
		exit(1);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = FIND_PORT;
	sin.sin_addr = *((struct in_addr *)host->h_addr);
	port_offs = 0;
	while (port_offs <= 5 && (ret = connect(sockfd, (struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		close(sockfd);
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			printf("cant load socket\n");
			exit(1);
		}
		sin.sin_port = FIND_PORT + ++port_offs;
	}
	if (ret == -1)
	{
		printf("cant connect\n");
		exit(1);
	}
	// while(1)
	// {
	// 	if (write(sockfd, "Donnez moi des donnees\n", 23) == -1) {
	// 		perror("write");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	printf("je suis connecté\n");
	// }
	// //	
	return (sockfd);
}

int		serveur_address_serveur(char *ip, t_world *world)
{
	int sockfd;
	t_cluster cluster;
	t_data	data;
	
	data.data = NULL;
	data.used = 0;
	data.total = 0;
	sockfd = client_init(ip);

	cluster.world = ft_memalloc(sizeof(t_world));
	ft_bzero(cluster.world, sizeof(t_world));
	cluster.world = world;
	printf("spheres len %d\n", cluster.world->spheres_len);
	client_loop(sockfd, &cluster, &data);
	return(0);
}
