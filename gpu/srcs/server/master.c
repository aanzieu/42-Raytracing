/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:32:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/24 14:32:48 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/cluster.h"
#include <arpa/inet.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../includes/rt.h"
#include "../includes/display.h"

void remove_clients(t_cluster *cl, t_client **cli, t_client **tmp)
{
	free((*cli)->buffer);
	if (*tmp == NULL)
	{
		cl->client_list = (*cli)->next;
		close((*cli)->fd);
		free(*cli);
		*cli = cl->client_list;
	}
	else
	{
		(*tmp)->next = (*cli)->next;
		free(*cli);
		*cli = (*tmp)->next;
	}
}

int		send_informations(t_client *clients, char cmd, void *arg, size_t arg_size)
{
	char	ok;
	size_t	main_size;

	main_size = 4 * (WIN_WIDTH * (WIN_HEIGHT - clients->offsets.y_min));// * sizeof(int);
//	main_size = 4 * WIN_WIDTH * WIN_HEIGHT;// * sizeof(int);
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
	{
		printf("offsets save y_min :%d | y_max :%d\n", clients->offsets.y_min, clients->offsets.y_max);
		printf("Structure recu cote master\n");
		return(0);
	}
	if (recv(clients->fd, &ok, 1, 0) == 0)
	{
		printf("pas de message recu cote master\n");
		return(0);
	}
	if (ok == 'c')
	{
		printf("Camera OK\n");
		clients->status |= SEND_CAMERA;
	}
	if (ok == 's')
	{
		printf("Spheres OK\n");
		clients->status |= SEND_SPHERES;
	}
	if (ok == 'l')
	{
		printf("Lights OK\n");
		clients->status |= SEND_LIGHTS;
	}
	printf("fin de send information\n");
	return(1);
}

void	*dup_data(t_cluster *cluster, char cmd)
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
	//	printf("client spheres radius %lf\n", cluster->world->spheres[0].radius);
		size = sizeof(t_sphere) * cluster->world->spheres_len;
		ret = ft_memalloc(size);
		if(ret != NULL)
			ret = ft_memcpy(ret, cluster->world->spheres, size);
	}
	if(cmd == 'l')
	{
//		printf("client lights %lf\n", cluster->world->spheres[0].radius);
		size = sizeof(t_light) * cluster->world->lights_len;
		ret = ft_memalloc(size);
		if(ret != NULL)
			ret = ft_memcpy(ret, cluster->world->lights, size);
	}
	return(ret);
}

int send_buffer_clients(t_cluster *cluster, t_client *clients)
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
		printf("nb de spheres %d\n", cluster->world->spheres_len);
		send_informations(clients, 's', buffer, cluster->world->spheres_len * sizeof(t_sphere));
	}
	if ((clients->status & SEND_LIGHTS) == 0)
	{
		if (!(buffer = dup_data(cluster, 'l')))
			return (0);
		printf("nb de light %d\n", cluster->world->lights_len);
		send_informations(clients, 'l', buffer, cluster->world->lights_len * sizeof(t_light));
	}
	free(buffer);
	return (1);
}

void		send_informations_all(t_cluster *cluster, char cmd, void *arg, size_t arg_size)
{
	t_client	*clients;
	t_client	*clients_tmp;
	int			nbr_clients;
	int			clients_alive;

	clients_tmp = NULL;
	nbr_clients = 0;
	clients = cluster->client_list;
	while(clients != NULL)
	{
		if (cmd == 'r')
			clients_alive = send_buffer_clients(cluster, clients);
		if(clients_alive)
		{
			printf("je rentre information valeur de client%d\n", clients_alive);
			clients_alive = send_informations(clients, cmd, arg, arg_size);
			printf("je sors d'information valeur de client%d\n", clients_alive);
		}
//		if (clients->buffer)
//		{
//			ft_memcpy(cluster->world->a_h, clients->buffer, 4 * WIN_HEIGHT * WIN_WIDTH);
//			put_pixel_screen(cluster->world);
//			SDL_UpdateWindowSurface(cluster->world->window.id);
//			printf("Color : %d\n", cluster->world->a_h[620]);
//			sleep(5);
//		}
		if (!clients_alive)
			remove_clients(cluster, &clients, &clients_tmp);
		else
		{
			clients_tmp = clients;
			clients = clients->next;
			nbr_clients++;
		}
		printf("je change de clients\n");
	}
//	return(n1);
}

void	cluster_stratege(t_cluster *cluster)
{
	int			nbr;
	t_offsets	offsets;
	t_client	*clients;
	float		theta;

	cluster->nbr_clients = 0;
	clients = cluster->client_list;
	while(clients && (cluster->nbr_clients++ | MAX_CLIENTS))
		clients = clients->next;
	theta = 2* M_PI / cluster->nbr_clients;
	clients = cluster->client_list;

	nbr = cluster->nbr_clients;
	offsets.y_min = 0;
//	sleep(5);
	while(nbr--)
	{
		printf("nbr_clients :%d\n", cluster->nbr_clients);
		offsets.y_min = nbr * WIN_HEIGHT / cluster->nbr_clients;//cos(theta * cluster->nbr_clients);
		offsets.y_max = offsets.y_min + WIN_HEIGHT / cluster->nbr_clients;//sin(theta * cluster->nbr_clients);		
		printf("offsets.y_min :%d | offsets.y_max :%d\n", offsets.y_min, offsets.y_max);
		if(clients)
		{	
		//	printf("offsets.x %lf | offsets.y %lf\n", offsets.x, offsets.y);
		//	printf("camera position.z : %lf\n", cluster->world->camera.pos.z);
			clients->offsets.y_min = offsets.y_min;
			clients->offsets.y_max = offsets.y_max;
			printf("offsets save y_min :%d | y_max :%d\n", clients->offsets.y_min, clients->offsets.y_max);
			send_informations(clients, 'w', &offsets, sizeof(offsets));
			clients = clients->next;
		}
		else
			ft_memcpy(&offsets, &offsets, sizeof(offsets));
	}
}




















/*
void *get_data_from_client_thread(void *arg)
{
	t_thread_input		*thread;
	thread = (t_thread_input*)arg;

	char buffer[BUFSIZ];
	char protoname[] = "tcp";
	struct protoent *protoent;
	in_addr_t in_addr;
	int sockfd;
	ssize_t nbytes_read;// user_input_len;
	struct hostent *hostent;
	struct sockaddr_in sockaddr_in;
	unsigned short server_port = thread->port[thread->th];//12345;
	char *server_hostname = thread->str[thread->th];
	
	
	int size;
	size = thread->th * (WIN_HEIGHT * WIN_WIDTH) / 2;
	
	if(thread->th == 1)
	{
		server_port = 23456;
		server_hostname = "10.11.13.10";
	}
	if(thread->th == 0)
	{
		server_port = 12345;
		server_hostname = "10.11.13.14";
	}
//	while(*server_hostname) {
//	if (argc > 1) {
//		server_hostname = serveurid;
//		if (argc > 2) {
//			server_port = strtol(argv[2], NULL, 10);
//		}
//	}

	protoent = getprotobyname(protoname);
	if (protoent == NULL) {
		perror("getprotobyname");
		exit(EXIT_FAILURE);
	}
	thread->fd[thread->th] = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
	sockfd = thread->fd[thread->th];
	if (sockfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	hostent = gethostbyname(server_hostname);//serverid]);
	if (hostent == NULL) {
		fprintf(stderr, "error: gethostbyname(\"%s\")\n", server_hostname);
		exit(EXIT_FAILURE);
	}
	in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
	if (in_addr == (in_addr_t)-1) {
		fprintf(stderr, "error: inet_addr(\"%s\")\n", *(hostent->h_addr_list));
		exit(EXIT_FAILURE);
	}
	sockaddr_in.sin_addr.s_addr = in_addr;
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(server_port);
	static double i = 0.000;
	
//	int test = 0;
	while (connect(sockfd, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
		printf("Reconnecting...\n");
		// perror("connect");
		// exit(EXIT_FAILURE);
	}
	while (1) {

		if (dprintf(sockfd, "%lf : Envoie demande connection\n", i) == -1) {
			perror("write");
			exit(EXIT_FAILURE);
		}
		i += 0.001;
//		(void)world;
		if ((nbytes_read = read(sockfd, buffer, BUFSIZ)) > 0)
		{
			while(size < (thread->th + 1) * (WIN_HEIGHT * WIN_WIDTH) / 2)//orld->size_main)
			{
				recv(sockfd, &thread->world->a_h[size], sizeof(thread->world->a_h), 0);
				size++;
//				recv(sockfd, world->a_h, sizeof(world->a_h) * 65536, 0);
	//			recv(sockfd, tab, sizeof(int), 0);
	//			write(STDOUT_FILENO, buffer, nbytes_read);
	//			printf("%d\n", world->a_h[0]);
//				printf("%d\n", tab[0]);
//				if (size == 0)
//					break;
		//		world->a_h[0] = RED;
//				return;
			}
		//	test_pixel_put(world->a_h);
		//	close(sockfd);
			//free(user_input);
		//	fflush(stdout);
		//	break;
		}
		fflush(stdout);		
		break;
	//		if (buffer[nbytes_read - 1] == '\n') {
	//			break;
	//	}
	//	}
	}
//	serverid++;
//	}
	close(thread->fd[thread->th]);
	pthread_exit(0);//
//	exit(EXIT_SUCCESS);
}

void get_data_from_client(char *hostname, unsigned short port, t_world *world)
{
	char buffer[BUFSIZ];
	char protoname[] = "tcp";
	struct protoent *protoent;
	in_addr_t in_addr;
	int sockfd;
	ssize_t nbytes_read;// user_input_len;
	struct hostent *hostent;
	struct sockaddr_in sockaddr_in;
	unsigned short server_port = port;
	char *server_hostname = hostname;
	int ret;
	int size;

	protoent = getprotobyname(protoname);
	if (protoent == NULL) {
		perror("getprotobyname");
		exit(EXIT_FAILURE);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, protoent->p_proto);
	if (sockfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	hostent = gethostbyname(server_hostname);//serverid]);
	if (hostent == NULL) {
		fprintf(stderr, "error: gethostbyname(\"%s\")\n", server_hostname);
		exit(EXIT_FAILURE);
	}
	in_addr = inet_addr(inet_ntoa(*(struct in_addr*)*(hostent->h_addr_list)));
	if (in_addr == (in_addr_t)-1) {
		fprintf(stderr, "error: inet_addr(\"%s\")\n", *(hostent->h_addr_list));
		exit(EXIT_FAILURE);
	}
	sockaddr_in.sin_addr.s_addr = in_addr;
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(server_port);
	
	if (connect(sockfd, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) == -1) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	(void)world;
	while (1) {
		if (write(sockfd, "Donnez moi des donnees\n", 23) == -1) {
			perror("write");
			exit(EXIT_FAILURE);
		}
		printf("Sent demand\n");
		if ((nbytes_read = read(sockfd, buffer, BUFSIZ)) > 0)
		{
			printf("Received response\n");
			size = 0;
			ret = 0;
			while(size < (WIN_HEIGHT * WIN_WIDTH))
			{
				ret = recv(sockfd, &world->a_h[size], sizeof(int), 0);
				if (ret < 0){
					perror("receive");
					exit(EXIT_FAILURE);
				}
				size++;			
			}
			printf("Exited while\n");
			printf("----------------\n");			
			break;
		}
	}
	close(sockfd);
}*/
