/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/27 17:24:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cluster.h>
#include <unistd.h>
#include <rt.h>

/*
 ** MISE EN PLACE DE RECEPTION DONNEE CLIENT_CLUSTERING EN BOUCLE
*/

void				client_loop(int sockfd, t_cluster *cluster, t_data *data)
{
	char	cmd;
	int		ret;
	size_t	data_size;
	size_t	data_used;

	if ((ret = recv(sockfd, &cmd, 1, 0)) != 1)
		return ;
	data_used = 0;
	if ((ret = recv(sockfd, &data_size, 8, 0)) <= 0)
		return ;
	if (data_size || data_size == 0)
	{
		if (data_recv(data, data_size) == 0)
			printf("zero data receved from %c\n", cmd);
		recv(sockfd, data->data, data_size, 0);
		data->used = data_size;
	}
	process_send(cmd, data, cluster, sockfd);
	client_loop(sockfd, cluster, data);
}

static int			client_init(char *host_ip)
{
	int					sockfd;
	int					ret;
	int					port_offs;
	struct hostent		*host;
	struct sockaddr_in	sin;

	if ((host = gethostbyname(host_ip)) == NULL)
		ft_putendl_fd("cant gethostbyname", 1);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_putendl_fd("cant load socket", 1);
	sin.sin_family = AF_INET;
	sin.sin_port = FIND_PORT;
	sin.sin_addr = *((struct in_addr *)host->h_addr);
	port_offs = 0;
	while (port_offs <= 5 && (ret = connect(sockfd,
					(struct sockaddr *)&sin, sizeof(sin))) == -1)
	{
		close(sockfd);
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
			ft_putendl_fd("cant load socket", 1);
		sin.sin_port = FIND_PORT + ++port_offs;
	}
	if (ret == -1)
		ft_putendl_fd("cant connect", 1);
	return (sockfd);
}

int					serveur_address_serveur(char *ip, t_world *world)
{
	int			sockfd;
	t_cluster	cluster;
	t_data		data;

	data.data = NULL;
	data.used = 0;
	data.total = 0;
	sockfd = client_init(ip);
	cluster.world = world;
	data_setup(cluster.world);
	client_loop(sockfd, &cluster, &data);
	return (0);
}
