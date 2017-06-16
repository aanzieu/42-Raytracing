/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 13:27:40 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include "../libft/libft.h"
#include "./cuda/cudaheader/gpu_rt.h"
#include "../frameworks/SDL2.framework/Headers/SDL.h"

void	add_sphere_tmp(t_sphere **spheres, double radius, t_vec3d pos)
{
	t_sphere *new_sphere;
	t_sphere *tmp;

	tmp = *spheres;
	new_sphere = malloc(sizeof(t_sphere));
	new_sphere->radius = radius;
	new_sphere->pos = pos;
	new_sphere->next = NULL;

	if (!tmp)
		*spheres = new_sphere;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sphere;
	}
}

void	get_viewplane(t_world *world)
{
	world->viewplane.x_res = WIN_WIDTH / world->render_factor;
	world->viewplane.y_res = WIN_HEIGHT / world->render_factor;
	world->viewplane.x_indent = world->viewplane.width /
									(double)world->viewplane.x_res;
	world->viewplane.y_indent = world->viewplane.height /
									(double)world->viewplane.y_res;
}

void	data_setup(t_world *world)
{
	world->viewplane.width = 0.5;
	world->viewplane.height = 0.5;
	world->render_factor = 1;
	world->viewplane.dist = 1;
	world->line = 0;
}

/*
**	Counts spheres from an linked list
*/

unsigned int	count_spheres(t_sphere *spheres)
{
	t_sphere *s;
	unsigned int size;

	size = 0;
	s = spheres;
	while (s)
	{
		size++;
		s = s->next;
	}
	return (size);
}

unsigned int	count_planes(t_plane *planes)
{
	t_plane *p;
	unsigned int size;

	size = 0;
	p = planes;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

unsigned int	count_cones(t_cone *cones)
{
	t_cone *p;
	unsigned int size;

	size = 0;
	p = cones;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

unsigned int	count_cylinders(t_cylinder *cylinders)
{
	t_cylinder *p;
	unsigned int size;

	size = 0;
	p = cylinders;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

unsigned int	count_lights(t_light *lights)
{
	t_light *p;
	unsigned int size;

	size = 0;
	p = lights;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void			load_spheres(t_sphere **spheres, t_sphere *spheres_tmp, int *spheres_len)
{
	unsigned int i;
	t_sphere *tmp;

	i = 0;
	*spheres_len = count_spheres(spheres_tmp);
	*spheres = (t_sphere*)malloc(sizeof(t_sphere) * *spheres_len);
	tmp = spheres_tmp;
	while (tmp)
	{
		(*spheres)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}

void			load_planes(t_plane **planes, t_plane *planes_tmp, int *planes_len)
{
	unsigned int i;

	i = 0;
	*planes_len = count_planes(planes_tmp);
	*planes = (t_plane*)malloc(sizeof(t_plane) * (*planes_len));
	while (planes_tmp)
	{
		(*planes)[i] = *planes_tmp;
		planes_tmp = planes_tmp->next;
		i++;
	}
}

void			load_cones(t_cone **cones, t_cone *cones_tmp, int *cones_len)
{
	unsigned int i;
	t_cone *tmp;

	i = 0;
	*cones_len = count_cones(cones_tmp);
	*cones = (t_cone*)malloc(sizeof(t_cone) * *cones_len);
	tmp = cones_tmp;
	while (tmp)
	{
		(*cones)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}

void			load_cylinders(t_cylinder **cylinders, t_cylinder *cylinders_tmp, int *cylinders_len)
{
	unsigned int i;
	t_cylinder *tmp;

	i = 0;
	*cylinders_len = count_cylinders(cylinders_tmp);
	*cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * *cylinders_len);
	tmp = cylinders_tmp;
	while (tmp)
	{
		(*cylinders)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}

void			load_lights(t_light **lights, t_light *lights_tmp, int *lights_len)
{
	unsigned int i;
	t_light *tmp;

	i = 0;
	*lights_len = count_lights(lights_tmp);
	*lights = (t_light*)malloc(sizeof(t_light) * *lights_len);
	tmp = lights_tmp;
	while (tmp)
	{
		(*lights)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}

void	load_data(t_world *world)
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

void	rtv1(t_world *world)
{
	SDL_Event		event;
	int				quit;
	int		*a_h;
	size_t			size_main;

	quit = 0;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return ;
	world->window.id = SDL_CreateWindow("Rtv1 v0.9.1", 100, 100, WIN_WIDTH,
								WIN_HEIGHT, 0);
	world->window.screen = SDL_GetWindowSurface(world->window.id);
	size_main = world->viewplane.x_res * world->viewplane.y_res * sizeof(int);
	if (!(a_h = malloc(size_main)))
		return ;
	ft_bzero(a_h, size_main);
	while (quit == 0)
	{
		// printf("%d\n", world->render_factor);
		SDL_PollEvent(&event);
		quit = event_handler(world, event);
		get_viewplane(world);		
		// printf("%d : %d : %d\n", world->render_factor, world->viewplane.x_res, world->viewplane.y_res);
		render_cuda(a_h, world->viewplane.x_res, world->viewplane.y_res, *world, 0);
		// ft_bzero(a_h, size_main);
		SDL_UpdateWindowSurface(world->window.id);
	}
	render_cuda(a_h, world->viewplane.x_res, world->viewplane.y_res, *world, 1);
	free(a_h);
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

	if (argc == 2)
	{
		if (!(world = (t_world*)malloc(sizeof(t_world) * 1)))
			memory_allocation_error();
		data_setup(world);
		get_viewplane(world);
		parse_rtv1(world, argv[1]);
		load_data(world);
		rtv1(world);
		free_world(world);
	}
	else
		ft_putstr("Usage: ./rtv1 filename.xml\n");
	SDL_Quit();
	return (0);
}
