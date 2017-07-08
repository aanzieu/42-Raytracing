/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/07 14:45:12 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <parse.h>
#include <display.h>

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
	world->mode = 1;
	world->light_type = 0;
	world->viewplane.width = 0.5;
	world->viewplane.height = 0.5;
	world->render_factor = 1;
	world->viewplane.dist = 1;
	world->line = 0;
	world->ambient.coef = 0.2;
}

static void	load_data(t_world *world)
{
	load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);
	load_planes(&world->planes, world->planes_tmp, &world->planes_len);
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
	y = (thread->th * (thread->world->viewplane.y_res / NB_TH));
	while (y < (thread->th + 1) * (thread->world->viewplane.y_res / NB_TH))
	{
		x = 0;
//		i = 0;
		while (x < thread->world->viewplane.x_res)
		{
			thread->world->a_h[y * thread->world->viewplane.x_res + x]
					= ray_tracer(*thread->world, x, y);
			x++;
		}
		y++;
	}
	pthread_exit(0);
}

int					launch_thread(t_world *world)
{
	t_thread_input		tab[NB_TH];
	int				i;

	i = -1;
	while (++i < NB_TH)
	{
		tab[i].th = i;
		tab[i].world = world;
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

	quit = 0;
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		get_viewplane(world);
		launch_thread(world);
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
	render_cuda(world->a_h, world->viewplane.x_res,
			world->viewplane.y_res, *world, 1);
}

/*
**	Initialize SDL and start listening to events
*/

void	rt(t_world *world)
{
	world->size_main = world->viewplane.x_res * world->viewplane.y_res
		* sizeof(int);
	if (!(world->a_h = malloc(world->size_main)))
		exit(0);
	ft_bzero(world->a_h, world->size_main);
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	world->window.id = SDL_CreateWindow(world->title, 100, 100, WIN_WIDTH,
								WIN_HEIGHT, 0);
	world->window.screen = SDL_GetWindowSurface(world->window.id);
	if (world->mode == 1)
		launch_cpu(world);
	else
		launch_gpu(world);
	free(world->a_h);
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

//	(void)argv;
	if (argc == 2)
	{
		if (!(world = (t_world*)malloc(sizeof(t_world) * 1)))
			memory_allocation_error();
		data_setup(world);
		get_viewplane(world);
		parse_rtv1(world, argv[1]);
		load_data(world);
		rt(world);
		// printf("%f\n", world->disks->color.r);
		// printf("%f\n", world->disks->color.g);
		// printf("%f\n\n", world->disks->color.b);
		// printf("%f\n", world->disks->radius);
		// printf("%f\n", world->disks->radius_squared);
		// printf("%f\n", world->camera.look_at.x);
		// printf("%f\n", world->camera.look_at.y);
		// printf("%f\n", world->camera.look_at.z);
		free_world(world);
	}
	else
		ft_putstr("Usage: ./bin/RT filename.xml\n");
	SDL_Quit();
	return (0);
}
