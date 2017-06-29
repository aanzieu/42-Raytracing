/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/23 17:18:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <parse.h>
#include <display.h>

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
		launch_thread(world);
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
