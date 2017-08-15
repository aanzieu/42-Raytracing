	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/27 18:08:49 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <../../gpu/srcs/cuda/cudaheader/gpu_rt.h>
#include <parse.h>
#include <display.h>
#include <unistd.h>
#include <cluster.h>

void		get_viewplane(t_world *world)
{
	world->viewplane.x_res = (WIN_WIDTH) / world->render_factor;
	world->viewplane.y_res = (WIN_HEIGHT) / world->render_factor;
	world->viewplane.x_indent = world->viewplane.width /
									(double)world->viewplane.x_res;
	world->viewplane.y_indent = world->viewplane.height /
									(double)world->viewplane.y_res;
}

void	data_setup(t_world *world)
{
	world->mode = 0;
	world->light_type = 1;
	world->viewplane.width = (double)((M_PI / 4) / 2);
	world->viewplane.height = ((double)((double)(WIN_HEIGHT) / (double)(WIN_WIDTH))
	 														* world->viewplane.width);
	world->render_factor = 1;
	world->viewplane.dist = 1;
	world->k = 0;
	world->line = 0;
	world->ambient.coef = 0.2;
	world->offsets.y_min = 0;
	world->offsets.y_max = 0;
	world->spheres = NULL;
	world->spheres_len = 0;
	world->planes = NULL;
	world->planes_len = 0;
	world->cones = NULL;
	world->cones_len = 0;
	world->cylinders = NULL;
	world->cylinders_len = 0;
	world->torus = NULL;
	world->torus_len = 0;
	world->lights = NULL;
	world->lights_len = 0;
	world->id = 0;
}

static void	load_data(t_world *world)
{
	load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);
	load_planes(&world->planes, world->planes_tmp, &world->planes_len);
	load_torus(&world->torus, world->torus_tmp, &world->torus_len);
	load_disks(&world->disks, world->disks_tmp, &world->disks_len);
	load_cones(&world->cones, world->cones_tmp, &world->cones_len);
	load_cylinders(&world->cylinders,
			world->cylinders_tmp, &world->cylinders_len);
	load_lights(&world->lights, world->lights_tmp, &world->lights_len);
	load_paraboloids(&world->paraboloids,
			world->paraboloids_tmp, &world->paraboloids_len);
	load_hyperboloids(&world->hyperboloids,
			world->hyperboloids_tmp, &world->hyperboloids_len);
}

static	void		*perform_thread(void *arg)
{
	t_thread_input	*thread;
	int			x;
	int			y;

	thread = (t_thread_input *)arg;
	y = ((thread->th) * ((thread->y_max - thread->y_min) / NB_TH) + thread->y_min);
	while (y < (thread->th + 1) * ((thread->y_max - thread->y_min) / NB_TH) + thread->y_min)
	{
		x = 0;
		while (x < thread->world->viewplane.x_res)
		{
			thread->world->a_h[(y - thread->y_min) * thread->world->viewplane.x_res + x]
					= ray_tracer(*thread->world, x, y);
			x++;
		}
		y++;
	}
	pthread_exit(0);
}

int					launch_thread(t_world *world, int y_min, int y_max)
{
	t_thread_input		tab[NB_TH];
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
	}
	i = -1;
	while (++i < NB_TH)
		pthread_join(world->thread[i], NULL);
	return(0);
}

void	launch_cpu(t_world *world)
{
	int			quit;
	SDL_Event	event;
	if(world->clientrender == 1)
	{
		get_viewplane(world);
		launch_thread(world, world->offsets.y_min, world->offsets.y_max);
		return;
	}
	quit = 0;
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		get_viewplane(world);
		launch_thread(world, 0, WIN_HEIGHT);
		put_pixel_screen(world);
		ft_bzero(world->a_h, world->size_main);
		SDL_UpdateWindowSurface(world->window.id);
	}
}

/*	On event receive send data to handler*/

void	launch_gpu(t_world *world)
{
	int			quit;
	SDL_Event	event;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	if(world->clientrender == 1)
	{
		pthread_mutex_lock(&mutex);
		get_viewplane(world);
		render_cuda(world->a_h, WIN_WIDTH, world->offsets.y_max - world->offsets.y_min, *world, 0);
		pthread_mutex_unlock(&mutex);
		return;
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

/*
**	Initialize SDL and start listening to events
*/

void    rt_cluster(t_world *world)
{
	world->clientrender = 1;
	world->render_factor = world->offsets.render_factor;
	if(world->a_h != NULL)
		free(world->a_h);
	world->size_main = WIN_WIDTH * (world->offsets.y_max - world->offsets.y_min)
        * sizeof(int);
    if (!(world->a_h = ft_memalloc(world->size_main)))
		ft_putendl_fd("Error : Can't malloc client a_h", 1);
    ft_bzero(world->a_h, world->size_main);
    if (world->mode == 1)
        launch_cpu(world);
    else
        launch_gpu(world);
}

void    rt(t_world *world)
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
    if (world->mode == 0)
        launch_cpu(world);
    else
        launch_gpu(world);
    free(world->a_h);
    SDL_FreeSurface(world->window.screen);
    SDL_DestroyWindow(world->window.id);
}

void		choose_main_launcher(char **argv, int flags)
{
	t_world		*world;

	if (!(world = (t_world*)ft_memalloc(sizeof(t_world))))
		memory_allocation_error();
	data_setup(world);
	get_viewplane(world);
	if (flags == 0 && argv[1])
	{
		parse_rtv1(world, argv[1]);
		load_data(world);
		rt(world);
		free_world(world);
	}
	else if(flags == 1 && argv[1])
	{
		parse_rtv1(world, argv[1]);
		load_data(world);
		ft_putstr("Wait Connection\n");
		master_cluster(world);
		ft_putstr("End of connexion, get start again\n");
	}
	else if(flags == 2)
	{
		if(argv[1] == NULL)
			ft_putstr_fd("usage : client IP\n", 1);
		serveur_address_serveur(argv[1], world);
		ft_putstr("Thank you for your patience\n");
	}
}

int		main(int argc, char **argv)
{
	int			flags;

	flags = 0;
	if (argc == 2)
		choose_main_launcher(argv, 0);
	else if (argc > 2)
	{
		if((ft_strcmp("master", argv[2]) == 0))
			flags = 1;
		else if((ft_strcmp("client", argv[2]) == 0))
			flags = 2;
		choose_main_launcher(argv, flags);
	}
	else
		ft_putstr("Usage: ./bin/RT filename.xml\n");
	SDL_Quit();
	return (0);
}
