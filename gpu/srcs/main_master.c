/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 14:03:16 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/20 15:46:57 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <cluster.h>
#include "../srcs/cuda/cudaheader/gpu_rt.h"
#include <parse.h>
#include <display.h>
#include <unistd.h>
/*
int		launch_cluster_thread(t_world *world)
{	
	t_thread_input		client[2];
	int					i;
	
	i = -1;
	while(++i < 2) //nbr de client a definir avec un ping;
	{
		client[i].th = i;
		client[i].world = world;
		if(pthread_create(&world->thread[i], NULL, &get_data_from_client_thread, &client[i]))
			ft_putendl_fd("Error : Can't init clustering thread\n", 1);
	}
	i = -1;
		while(++i < 2) // nbr de client a definir avec un ping
	{
		pthread_join(world->thread[i], NULL);
	}
	return(0);
}
*/
int		launch_cluster(t_world *world)
{
	char *clients[3] = {"10.11.13.10" , "10.11.13.14", NULL};
	int port[2] = {23456 , 12345};	
	int i;

	i = 0;
	while (clients[i] != NULL)
	{
		get_data_from_client(clients[i], port[i], world);
		i++;
	}
	return (0);
}

void	render_clustering(t_world *world)
{

	int			quit;
	SDL_Event	event;

	quit = 0;
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		//launch_cluster_thread(world);
		launch_cluster(world);
		printf("je sors de get_data_from_client\n");
		put_pixel_screen(world);
		ft_bzero(world->a_h, world->size_main);
		SDL_UpdateWindowSurface(world->window.id);
	}
}

/*
 ** Initialize Cluster to find if some Client is open
*/

void	*init_client(void *arg)
{
	t_cluster	*self;
	int			fd;
	t_client	*new;
	int			nbr_clients;

	self = arg;
	nbr_clients = 0;
	while(nbr_clients < 2)//MAX_CLIENTS)
	{
		fd = accept(self->sockfd, NULL, NULL);
		nbr_clients++;
		new = ft_memalloc(sizeof(*new));
		ft_bzero(new, sizeof(*new));
		new->fd = fd;
		new->next = self->client_list;
		self->client_list = new;
	}
	close(self->sockfd);
	return(NULL);
}

int		cluster_initialize(t_world *world, t_cluster *cluster)
{
	int					ret;
	int					port_offs;
	struct sockaddr_in	sockaddr_in;
	int					enable;

	if((cluster->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("no create socket");
		exit(EXIT_FAILURE);
	}
   if (setsockopt(cluster->sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
   {
		perror("setsockopt(SO_REUSEADDR) failed");
		exit(EXIT_FAILURE);
	}
	ft_bzero(&sockaddr_in, sizeof(sockaddr_in));
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = FIND_PORT;
	sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	port_offs = 0;
	while (port_offs <= 5 && (ret = bind(cluster->sockfd, (void *)&sockaddr_in, sizeof(sockaddr_in))) == -1)
	{
		printf("test + BIND");
		sockaddr_in.sin_port = FIND_PORT + ++port_offs;
	}
	if(ret == -1)
	{
		perror("all ports used");
		return(1);
	}
	if (listen(cluster->sockfd, 16) == -1)
	{
		perror("listen");
		return(1);
	}
	cluster->world = world;
	pthread_create(&cluster->client_thread, NULL, &init_client, cluster);
	sleep(3000);
	return(0);
}

/*
**	Initialize SDL and start listening to events
*/

void	master_cluster(t_world *world)
{
	t_cluster			cluster;
	
	world->size_main = world->viewplane.x_res * world->viewplane.y_res
		* sizeof(int);
	if (!(world->a_h = malloc(world->size_main)))
		exit(0);
	ft_bzero(world->a_h, world->size_main);
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	world->window.id = SDL_CreateWindow("Rtv1 v1.2.0", 100, 100, WIN_WIDTH,
								WIN_HEIGHT, 0);
	world->window.screen = SDL_GetWindowSurface(world->window.id);
	if(cluster_initialize(world, &cluster) == 1)
		printf("error init clustering\n");
//	render_clustering(world);
	free(world->a_h);
	SDL_FreeSurface(world->window.screen);
	SDL_DestroyWindow(world->window.id);
}
