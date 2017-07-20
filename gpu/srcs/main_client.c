/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/20 15:35:03 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cluster.h>
#include <rt.h>
#include "../../gpu/srcs/cuda/cudaheader/gpu_rt.h"
#include <parse.h>
#include <display.h>
#include <unistd.h>

// static	void		*perform_thread(void *arg)
// {
// 	t_thread_input	*thread;
// 	int			x;
// 	int			y;

// 	thread = (t_thread_input *)arg;
// 	y = (thread->th * (thread->world->viewplane.y_res / NB_TH));
// 	while (y < (thread->th + 1) * (thread->world->viewplane.y_res / NB_TH))
// 	{
// 		x = 0;
// 		while (x < thread->world->viewplane.x_res)
// 		{
// 			thread->world->a_h[y * thread->world->viewplane.x_res + x]
// 					= ray_tracer(*thread->world, x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// 	pthread_exit(0);
// }

// int					launch_thread(t_world *world)
// {
// 	t_thread_input		tab[NB_TH];
// 	int				i;
		
// 	i = -1;
// 	while (++i < NB_TH)
// 	{
// 		tab[i].th = i;
// 		tab[i].world = world;
// 		if (pthread_create(&world->thread[i], NULL, &perform_thread, &tab[i]))
// 			ft_putendl_fd("Error : Can't init launch_rtv1\n", 1);
// 	}
// 	i = -1;
// 	while (++i < NB_TH)
// 		pthread_join(world->thread[i], NULL);
// 	return(0);
// }

// void	launch_cpu(t_world *world)
// {
// 	// get_viewplane(world);
// 	launch_thread(world);
// }

/*	On event receive send data to handler*/

// void	launch_gpu(t_world *world)
// {
// 	int			quit;
// 	// SDL_Event	event;
		
// 	quit = 0;
// 	// while (quit == 0)
// 	// {
// 		// SDL_PollEvent(&event);
// 		// quit = event_handler(world, event);
// 		// get_viewplane(world);
// 		render_cuda(world->a_h, world->viewplane.x_res,
// 				world->viewplane.y_res, *world, 0);
// 		// put_pixel_screen(world);
// 		// ft_bzero(world->a_h, world->size_main);
// 		// SDL_UpdateWindowSurface(world->window.id);
// 	// }
// 	render_cuda(world->a_h, world->viewplane.x_res,
// 			world->viewplane.y_res, *world, 1);
// }

/*
**	Initialize SDL and start listening to events
*/
void	client_cluster(t_world *world)
{
	world->size_main = world->viewplane.x_res * world->viewplane.y_res
		* sizeof(int);
	if (!(world->a_h = malloc(world->size_main)))
		exit(0);
	ft_bzero(world->a_h, world->size_main);
	// if (world->mode == 1)
	// {
		get_viewplane(world);


		//
		//		C'EST ICI QUE TU METS DES VALEURS POUR TESTER L'INTERVALE DE L'IMAGE EN CLIENT ON VA DEVOIR LES REMPLACER PAR CE QU'ON RECOIT DU MASTER OU SI TU VEUX TU PEUX BIEN CHANGER ET FAIRE UN QUI RECOIT DES DEMANDES DES PLUSIEURS PC COMME SUR UN SERVEUR.
		//
		launch_thread(world, 0, 80);




	// }
	// else
	// {
		// get_viewplane(world);
		// render_cuda(world->a_h, world->viewplane.x_res,
			// world->viewplane.y_res, *world, 0);
		// render_cuda(world->a_h, world->viewplane.x_res,
			// world->viewplane.y_res, *world, 1);
	// }

	send_buffer(world);
	free(world->a_h);
}
/*
 ** MISE EN PLACE DE RECEPTION DONNEE CLIENT
*/

void client_loop(int sockfd, t_cluster *cl)
{
//	char	cmd;
//	int		ret;
//	size_t	data_size;
//	size_t	data_used;

// recv(sockfd, &cmd, envoye pour modifier les donnees);
//	data_used = 0;
//	if ((ret = recv(sockfd, &data_size, 8, 0)) <= 0)
//		return ;
//	if (data_size)
//	{
//		//ecrire fonction qui permet de savoir la quqntite de donne recu;
//		recv(sockfd, &cl, data_size, 0);

//		data_used = data_size;
//	}
//	load_data(cl->world);
//	rt(cl->world);
//	send(sockfd, color, data_size);
//	client_loop(sockfd, cl);
	(void)sockfd;
	(void)cl;
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
	while(1)
	{
		printf("je suis connecté\n");
	}
	return (sockfd);
}

