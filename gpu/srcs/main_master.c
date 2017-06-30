/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 14:03:16 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/29 18:04:49 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <parse.h>
#include <display.h>
#include <unistd.h>

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

void	render_clustering(t_world *world)
{

	int			quit;
	SDL_Event	event;

	quit = 0;
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		launch_cluster_thread(world);
		printf("je sors de get_data_from_client\n");
		put_pixel_screen(world);
		ft_bzero(world->a_h, world->size_main);
		SDL_UpdateWindowSurface(world->window.id);
	}
}

/*
**	Initialize SDL and start listening to events
*/

void	master_cluster(t_world *world)
{
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
	render_clustering(world);
	free(world->a_h);
	SDL_FreeSurface(world->window.screen);
	SDL_DestroyWindow(world->window.id);
}
