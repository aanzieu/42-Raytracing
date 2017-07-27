/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 14:03:16 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 17:32:48 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cluster.h>
#include <display.h>
#include <unistd.h>

/*
 ** Initialize Cluster to find if some Client is open
*/

static void			*init_client(void *arg)
{
	t_client	*new;
	t_cluster	*self;
	int			fd;
	int			nbr_clients;

	self = arg;
	nbr_clients = 0;
	while (nbr_clients < MAX_CLIENTS)
	{
		fd = accept(self->sockfd, NULL, NULL);
		nbr_clients++;
		new = ft_memalloc(sizeof(*new));
		ft_bzero(new, sizeof(*new));
		new->fd = fd;
		new->status = 'a';
		new->ww = WIN_WIDTH;
		new->next = self->client_list;
		self->client_list = new;
	}
	close(self->sockfd);
	return (NULL);
}

static void			cluster_initialize(t_world *world, t_cluster *cluster)
{
	int					ret;
	int					port_offs;
	struct sockaddr_in	sockaddr_in;
	int					enable;

	cluster->client_list = NULL;
	if ((cluster->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_putendl_fd("Error : no create socket", 1);
	if (setsockopt(cluster->sockfd,
				SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		ft_putendl_fd("Error :setsockopt(SO_REUSEADDR) failed", 1);
	ft_bzero(&sockaddr_in, sizeof(sockaddr_in));
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = FIND_PORT;
	sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	port_offs = 0;
	while (port_offs <= 5 && (ret = bind(cluster->sockfd,
					(void *)&sockaddr_in, sizeof(sockaddr_in))) == -1)
		sockaddr_in.sin_port = FIND_PORT + ++port_offs;
	if (ret == -1)
		ft_putendl_fd("Error : all ports used", 1);
	if (listen(cluster->sockfd, 0) == -1)
		ft_putendl_fd("Error : listen", 1);
	cluster->world = world;
	pthread_create(&cluster->client_thread, NULL, &init_client, cluster);
}

static void			put_buffer_together(t_cluster *cluster, t_client *clients,
		int x, int y)
{
	int	nbr_clients;
	int	y_max;
	int	i;

	nbr_clients = cluster->nbr_clients;
	while (nbr_clients-- && clients != NULL)
	{
		i = 0;
		if (clients->buffer)
		{
			y = nbr_clients * WIN_HEIGHT / cluster->nbr_clients;
			y_max = y + (WIN_HEIGHT / cluster->nbr_clients);
			while (y < y_max)
			{
				x = -1;
				while (++x < WIN_WIDTH)
				{
					cluster->world->a_h[y * WIN_WIDTH + x] = clients->buffer[i];
					i++;
				}
				y++;
			}
		}
		clients = clients->next;
	}
}

/*
**	Render Clustering
*/

static void			render_clustering(t_world *world, t_cluster *cluster)
{
	int			quit;
	SDL_Event	event;
	int			tmp;

	quit = 0;
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		if (cluster_stratege(cluster) == 1)
			launch_client(cluster, cluster->client_list);
		tmp = cluster->nbr_clients;
		remove_client_if(cluster, &cluster->client_list, NULL, NULL);
		if (cluster->nbr_clients == tmp)
			put_buffer_together(cluster, cluster->client_list, 0, 0);
		put_pixel_screen(cluster->world);
		ft_bzero(cluster->world->a_h, cluster->world->size_main);
		free_buffer(cluster);
		SDL_UpdateWindowSurface(cluster->world->window.id);
	}
}

/*
**	Initialize SDL and start listening to events
*/

void				master_cluster(t_world *world)
{
	t_cluster	cluster;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	world->window.id =
		SDL_CreateWindow("RT v3.0.0", 100, 100, WIN_WIDTH, WIN_HEIGHT, 0);
	world->window.screen = SDL_GetWindowSurface(world->window.id);
	cluster_initialize(world, &cluster);
	cluster.world->size_main =
		world->viewplane.x_res * world->viewplane.y_res * sizeof(int);
	if (!(cluster.world->a_h = malloc(cluster.world->size_main)))
		ft_putendl_fd("Error : Can't malloc cluster", 1);
	ft_bzero(cluster.world->a_h, cluster.world->size_main);
	render_clustering(world, &cluster);
	SDL_FreeSurface(world->window.screen);
	SDL_DestroyWindow(world->window.id);
}
