/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/07/24 18:01:44 by aanzieu          ###   ########.fr       */
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
	world->viewplane.x_res = WIN_WIDTH / world->render_factor;
	world->viewplane.y_res = WIN_HEIGHT / world->render_factor;
	world->viewplane.x_indent = world->viewplane.width /
									(double)world->viewplane.x_res;
	world->viewplane.y_indent = world->viewplane.height /
									(double)world->viewplane.y_res;
}

static void	data_setup(t_world *world)
{
	world->mode = 0;
	world->light_type = 1;
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

// thread = 0;
// y_min = 32;
// y_max = 320;
// 
// y = 0 * (320 / 8) + 32    =   32;
// while y < 1 * (320 / 8)   =   40;

// thread = 1;
// y_min = 32;
// y_max = 320;
// 
// y = 1 * (320 / 8) + 32    =   72;
// while y < 2 * (320 / 8)   =   80;

// thread = 2;
// y_min = 32;
// y_max = 320;
// 
// y = 2 * (320 / 8) + 32    =   112;
// while y < 3 * (320 / 8)   =   120;

// 320 / 8 = 40


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
			thread->world->a_h[y * thread->world->viewplane.x_res + x]
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
			ft_putendl_fd("Error : Can't init launch_rtv1\n", 1);
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
		printf("test\n");
		launch_thread(world, world->offsets.y_min, world->offsets.y_max);
		return;
	}
	quit = 0;
	while (quit == 0)
	{
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		get_viewplane(world);
		//		C'EST ICI QUE TU METS DES VALEURS POUR TESTER L'INTERVALE DE L'IMAGE , TU DOIS EXECUTER EN LOCAL
		launch_thread(world, 0, 640);
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

void    rt_cluster(t_world *world)
{
    if(world->a_h != NULL)
		free(world->a_h);
	world->clientrender = 1;
	world->size_main = world->viewplane.x_res * world->viewplane.y_res
        * sizeof(int);
    if (!(world->a_h = malloc(world->size_main)))
        exit(0);
	printf("JE RENTRE DANS RT\n");
    ft_bzero(world->a_h, world->size_main);
 //   if (world->mode == 0)
        launch_cpu(world);
//    else
  //      launch_gpu(world);
	printf("JE SORS DE RT\n");
}

void    rt(t_world *world)
{
	world->size_main = world->viewplane.x_res * world->viewplane.y_res
        * sizeof(int);
    if (!(world->a_h = malloc(world->size_main)))
        exit(0);
	printf("JE RENTRE DANS RT\n");
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
	printf("JE SORS DE RT\n");
	// printf("couleurs %d :\n", world->a_h[620]);
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
	int		flags = 0;

	if (!(world = (t_world*)malloc(sizeof(t_world) * 1)))
		memory_allocation_error();
	data_setup(world);
	get_viewplane(world);
	if (argc > 2)
	{
		if((ft_strcmp("local", argv[2]) == 0))
			flags = 0;
		else if((ft_strcmp("master", argv[2]) == 0))
			flags = 1;
		else if((ft_strcmp("client", argv[1]) == 0))
			flags = 2;
	}
	if (flags == 0 && argv[1])
	{
		parse_rtv1(world, argv[1]);
		load_data(world);
		printf("post process world spheres radius %lf\n", world->spheres[1].radius);
		rt(world);
		free_world(world);
	}
	else if(flags == 1 && argv[1])
	{
		parse_rtv1(world, argv[1]);
		load_data(world);
		printf("post process world spheres radius %lf\n", world->spheres[1].radius);
		master_cluster(world);// == -1;
		printf("je sors de master_cluster\n");
	}
	else if(flags == 2)
	{
		if(argv[2] == NULL)
		{
			printf("usage : client IP");
			exit(1);
		}
		serveur_address_serveur(argv[2], world);
	//	parse_rtv1(world, argv[1]);	// A retirer pour utiliser les donees recues de master
	//	load_data(world); // A retirer pour utiliser les donees recues de master
	//	client_cluster(world);// == -1;
		printf("je sors de client\n");
	}
	else
		ft_putstr("Usage: ./rtv1 filename.xml\n");
	SDL_Quit();
	return (0);
}
