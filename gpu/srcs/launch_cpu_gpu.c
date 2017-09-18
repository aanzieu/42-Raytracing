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
	int				x, x_aa;
	int				y, y_aa;

	thread = (t_thread_input *)arg;
	y = (thread->th) * ((thread->y_max - thread->y_min) / NB_TH) + thread->y_min;

	y_aa = y * thread->aa;
	printf(" thread No %d | valeur de y_aa avant %d\n", thread->th, y_aa);
	while (y < (thread->th + 1) * ((thread->y_max - thread->y_min) / NB_TH) + thread->y_min)
	{
		x = 0;
		x_aa = 0;
		while (x < thread->world->viewplane.x_res)
		{
			thread->world->a_h[(y - thread->y_min) *
			thread->world->viewplane.x_res + x] =
				ray_tracer(*thread->world, x_aa, y_aa);
			x_aa += thread->world->aa;
			x++;
		}
		y_aa += thread->world->aa;
		y++;
	}
	printf(" thread No %d | valeur de y_aa apres %d\n", thread->th, y_aa);
	pthread_exit(0);
}

int				launch_thread(t_world *world, int y_min, int y_max, int aa)
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
		tab[i].aa = aa;
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

void			get_viewplane_cluster(t_world *world)
{
	world->viewplane.x_res = (double)(WIN_WIDTH) / world->render_factor;
	world->viewplane.y_res = (double)(world->offsets.y_max - world->offsets.y_min) / world->render_factor;
	world->viewplane_aa.x_res = world->win_width / world->render_factor;
	world->viewplane_aa.y_res = world->win_height / world->render_factor;
	world->viewplane.x_indent = world->viewplane.width /
									(double)world->viewplane.x_res;
	world->viewplane.y_indent = world->viewplane.height /
									(double)world->viewplane.y_res;
	world->viewplane_aa.x_indent = world->viewplane_aa.width /
									(double)world->viewplane_aa.x_res;
	world->viewplane_aa.y_indent = world->viewplane_aa.height /	(double)world->viewplane_aa.y_res;
}


void 	refresh_viewplane_cluster(t_world *world)
{
	world->win_width = WIN_WIDTH * world->aa;
	//world->offsets.y_max - world->offsets.y_min
	world->win_height = (WIN_HEIGHT) * world->aa;
	world->viewplane.width = (double)((M_PI / 4) / 2);
	world->viewplane.height = ((double)((double)(world->win_height) /
								(double)(WIN_WIDTH)) * world->viewplane.width);
	world->viewplane_aa.width = (double)((M_PI / 4) / 2);
	world->viewplane_aa.height = ((double)((double)(world->win_height) /
								(double)(world->win_width)) * world->viewplane_aa.width);

}

void			launch_cpu(t_world *world)
{
	// int			quit;
	// SDL_Event	event;

	if (world->clientrender == 1)
	{
		refresh_viewplane_cluster(world);
		get_viewplane_cluster(world);
		// printf("print offset y_min %d\n", world->offsets.y_min);
		// printf("print offset y_max %d\n", world->offsets.y_max);		
		// printf("print offset aa %d\n", world->aa);
		// printf("print ambiant %f\n", world->ambient.intensity);
		// printf("print sphere.pos.x %f\n", world->spheres[1].pos.x);
		launch_thread(world, world->offsets.y_min, world->offsets.y_max, world->offsets.aa);
		printf("y_min_ = %d | y_max_ = %d | width = %d | heigth = %d\n", world->offsets.y_min, world->offsets.y_max, world->win_width, world->win_height);
		printf("width-AA = %f | heigth-AA = %fm\n", world->viewplane_aa.width, world->viewplane_aa.height);
		printf("aa-y_indent = %f | aa-x_indent = %f | aa-x_res = %d | aa-y_res = %d\n", world->viewplane_aa.y_indent, world->viewplane_aa.x_indent, world->viewplane_aa.x_res, world->viewplane_aa.y_res);
		return ;
	}
	// quit = 0;
	// while (quit == 0)
	// {
		// SDL_PollEvent(&event);
		// quit = event_handler(world, event);
		get_viewplane(world);
		launch_thread(world, 0, WIN_HEIGHT, world->aa);
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
	// int						quit;
	// SDL_Event				event;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if (world->clientrender == 1)
	{
		pthread_mutex_lock(&mutex);
		printf("je suis dans gpu cluster\n");
		get_viewplane(world);
		render_cuda(world->a_h, WIN_WIDTH,
				world->offsets.y_max - world->offsets.y_min, world, 0);
		pthread_mutex_unlock(&mutex);
		return ;
	}
	// quit = 0;
	// while (quit == 0)
	// {
	// 	SDL_PollEvent(&event);
	// 	quit = event_handler(world, event);
		get_viewplane(world);
		render_cuda(world->a_h, world->viewplane.x_res,
				world->viewplane.y_res, world, 0);

		// render_cuda(world->a_h, WIN_WIDTH, WIN_HEIGHT, *world, 0);
		// put_pixel_screen(world);
		// ft_bzero(world->a_h, world->size_main);
		// SDL_UpdateWindowSurface(world->window.id);
	// }
}
