/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/19 09:21:03 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <../srcs/cuda/cudaheader/gpu_rt.h>
#include <parse.h>

static void	get_viewplane(t_world *world)
{
	world->viewplane.x_res = WIN_WIDTH / world->render_factor;
	world->viewplane.y_res = WIN_HEIGHT / world->render_factor;
	world->viewplane.x_indent = world->viewplane.width /
									(double)world->viewplane.x_res;
	world->viewplane.y_indent = world->viewplane.height /
									(double)world->viewplane.y_res;
}

static void	data_setup(t_world *world)
{
	world->viewplane.width = 0.5;
	world->viewplane.height = 0.5;
	world->render_factor = 1;
	world->viewplane.dist = 1;
	world->line = 0;
}

static void	load_data(t_world *world)
{
	load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);
	load_planes(&world->planes, world->planes_tmp, &world->planes_len);
	load_cones(&world->cones, world->cones_tmp, &world->cones_len);
	load_cylinders(&world->cylinders, world->cylinders_tmp, &world->cylinders_len);
	load_lights(&world->lights, world->lights_tmp, &world->lights_len);
}

/*
**	Set the game in fullscreen
**	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
*/

/*
**	Initialize SDL and start listening to events
**	On event receive send data to handler
*/

static	void		*perform_thread(void *arg)
{
	t_thread_input	*thread;
	int			x;
	int			y;

	thread = (t_thread_input *)arg;
	y = (thread->th * (thread->world->viewplane.y_res / NB_TH));
	while (y < (thread->th + 1) * ((thread->world->viewplane.y_res / NB_TH)))
	{
		x = 0;
		while (x < thread->world->viewplane.x_res)
		{
			pixel_to_image(thread->world->window.screen,
			x, y, ray_tracer(*thread->world, x, y));
			x++;
		}
		y++;
	}
	pthread_exit(0);
}

int					launch_thread(t_world *world)
{
	t_thread_input		tab[NB_TH];
	int					i;

	i = -1;
	while (++i < NB_TH)
	{
		tab[i].th = i;
		tab[i].world = world;
		if (pthread_create(&world->thread[i], NULL, &perform_thread, &tab[i]))
			ft_putendl_fd("Error : Can't init launch_rtv1\n", 1);
	}
	i = -1;
	while (++i < NB_TH)
		pthread_join(world->thread[i], NULL);
	return (0);
}

void	rt(t_world *world)
{
	SDL_Event		event;
	int				quit;
//	int		*a_h;
//	size_t			size_main;

	quit = 0;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	world->window.id = SDL_CreateWindow("Rtv1 v0.9.1", 100, 100, WIN_WIDTH,
								WIN_HEIGHT, 0);
	world->window.screen = SDL_GetWindowSurface(world->window.id);
//	size_main = world->viewplane.x_res * world->viewplane.y_res * sizeof(int);
//	if (!(a_h = malloc(size_main)))
//		return ;
//	ft_bzero(a_h, size_main);
	while (quit == 0)
	{
		// printf("%d\n", world->render_factor);
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		get_viewplane(world);
		launch_thread(world);
		// printf("%d : %d : %d\n", world->render_factor, world->viewplane.x_res, world->viewplane.y_res);
//		render_cuda(a_h, world->viewplane.x_res, world->viewplane.y_res, *world, 0);
		// ft_bzero(a_h, size_main);
		SDL_UpdateWindowSurface(world->window.id);
	}
//	render_cuda(a_h, world->viewplane.x_res, world->viewplane.y_res, *world, 1);
//	free(a_h);
	SDL_FreeSurface(world->window.screen);
	SDL_DestroyWindow(world->window.id);
}

/*
** DEBUG TO FILE
**	int fd;
**	FILE *saved = stdout;
**	stdout = fopen("log.txt", "w+");
*/

int		main(int argc, char **argv)
{
	t_world	*world;

	(void)argv;
	if (argc == 2)
	{
		if (!(world = (t_world*)malloc(sizeof(t_world) * 1)))
			memory_allocation_error();
		data_setup(world);
		get_viewplane(world);
		parse_rtv1(world, argv[1]);
		load_data(world);
		rt(world);
		free_world(world);
	}
	else
		ft_putstr("Usage: ./rtv1 filename.xml\n");
	SDL_Quit();
	return (0);
}
