/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cpu_gpu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/09/08 18:16:00 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <display.h>
# include <unistd.h>

static	void	*perform_thread(void *arg)
{
	t_thread_input	*thread;
	int				x;
	int				y;

	thread = (t_thread_input *)arg;
	y = ((thread->th) * ((thread->y_max - thread->y_min) / NB_TH) +
															thread->y_min);
	while (y < (thread->th + 1) * ((thread->y_max - thread->y_min) /
													NB_TH) + thread->y_min)
	{
		x = 0;
		while (x < thread->world->viewplane.x_res)
		{
			thread->world->a_h[(y - thread->y_min) *
			thread->world->viewplane.x_res + x] =
				ray_tracer(*thread->world, x, y);
			x++;
		}
		y++;
	}
	pthread_exit(0);
}

int				launch_thread(t_world *world, int y_min, int y_max)
{
	t_thread_input	tab[NB_TH];
	int				i;

	i = -1;
	while (++i < NB_TH)
	{
		tab[i].th = i;
		tab[i].world = world;
		tab[i].y_min = y_min;
		tab[i].y_max = y_max;
		if (pthread_create(&world->thread[i], NULL, &perform_thread, &tab[i]))
			ft_putendl_fd("Error : Can't init launch_rtv1", 1);
		//printf("%d %%\n", (i * 100) / NB_TH);
	}
	//printf("100 %%\n");
	i = -1;
	world->load = 0;
	while (++i < NB_TH) {
		pthread_join(world->thread[i], NULL);
		world->load = (i * 100) / NB_TH;
		//printf("%zu %%\n", world->load);
	}
	world->load = 30;
	return (0);
}

void			launch_cpu(t_world *world)
{
	// int			quit;
	// SDL_Event	event;

	if (world->clientrender == 1)
	{
		get_viewplane(world);
		launch_thread(world, world->offsets.y_min, world->offsets.y_max);
		return ;
	}
	// quit = 0;
	// while (quit == 0)
	// {
		// SDL_PollEvent(&event);
		// quit = event_handler(world, event);
		get_viewplane(world);
		launch_thread(world, 0, WIN_HEIGHT);
		//MERCI STEPHAN JAI GALERE A COMPRENDRE POUQUOI LA CAMERA AVANCEE TOUTE SEULE>>>>>>>>>>> XD
	//	move_forward(world);
	//	move_forward(world);
	//	move_forward(world);
	//	move_forward(world);
		// put_pixel_screen(world);
		// ft_bzero(world->a_h, world->size_main);
		// SDL_UpdateWindowSurface(world->window.id);
	// }
}

/*
**	On event receive send data to handler
*/

void			launch_gpu(t_world *world)
{
	int						quit;
	SDL_Event				event;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (world->clientrender == 1)
	{
		pthread_mutex_lock(&mutex);
		get_viewplane(world);
		render_cuda(world->a_h, WIN_WIDTH,
				world->offsets.y_max - world->offsets.y_min, *world, 0);
		pthread_mutex_unlock(&mutex);
		return ;
	}
	quit = 0;
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		get_viewplane(world);
		render_cuda(world->a_h, world->viewplane.x_res,
				world->viewplane.y_res, *world, 0);
		put_pixel_screen(world);
		ft_bzero(world->a_h, world->size_main);
		SDL_UpdateWindowSurface(world->window.id);
	}
}
