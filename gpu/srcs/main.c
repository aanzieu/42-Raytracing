/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/09/29 17:20:04 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <parse.h>
#include <display.h>
#include <unistd.h>
#include <cluster.h>

void			get_viewplane(t_world *world)
{
	world->viewplane.x_res = (WIN_WIDTH) / world->render_factor;
	world->viewplane.y_res = (WIN_HEIGHT) / world->render_factor;
	world->viewplane_aa.x_res = world->win_width / world->render_factor;
	world->viewplane_aa.y_res = world->win_height / world->render_factor;
	world->viewplane.x_indent = world->viewplane.width /
									(double)world->viewplane.x_res;
	world->viewplane.y_indent = world->viewplane.height /
									(double)world->viewplane.y_res;
	world->viewplane_aa.x_indent = world->viewplane_aa.width /
									(double)world->viewplane_aa.x_res;
	world->viewplane_aa.y_indent = world->viewplane_aa.height /
									(double)world->viewplane_aa.y_res;
}

void			load_data(t_world *world)
{
	load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);
	load_planes(&world->planes, world->planes_tmp, &world->planes_len);
	load_disks(&world->disks, world->disks_tmp, &world->disks_len);
	load_cones(&world->cones, world->cones_tmp, &world->cones_len);
	load_triangles(&world->triangles, world->triangles_tmp,
			&world->triangles_len);
	load_cubes(&world->cubes, world->cubes_tmp,
			&world->cubes_len);
	load_h_cubes(&world->h_cubes, world->h_cubes_tmp,
			&world->h_cubes_len);
	load_torus(&world->torus, world->torus_tmp,
			&world->torus_len);
	load_cylinders(&world->cylinders,
			world->cylinders_tmp, &world->cylinders_len);
	load_lights(&world->lights, world->lights_tmp, &world->lights_len);
	load_paraboloids(&world->paraboloids,
			world->paraboloids_tmp, &world->paraboloids_len);
	load_hyperboloids(&world->hyperboloids,
			world->hyperboloids_tmp, &world->hyperboloids_len);
	load_mobius(&world->mobius,
			world->mobius_tmp, &world->mobius_len);
}

void			rt_cluster(t_world *world)
{
	world->clientrender = 1;
	world->render_factor = world->offsets.render_factor;
	world->aa = world->offsets.aa;
	world->id_save = world->offsets.id_save;
	world->ob_save = world->offsets.ob_save;
	world->mode = world->offsets.mode;
	world->size_main = (WIN_WIDTH / world->render_factor) *
		((world->offsets.y_max - world->offsets.y_min) / world->render_factor) *
		sizeof(int);
	if (world->a_h == NULL)
	{
		if (!(world->a_h = ft_memalloc(world->size_main)))
			ft_putendl_fd("Error : Can't malloc client a_h", 1);
	}
	ft_bzero(world->a_h, world->size_main);
	if (world->mode == 0)
		launch_cpu(world);
	else
		launch_gpu(world);
}

void			rt(t_world *world)
{
	world->size_main = world->viewplane.x_res * world->viewplane.y_res *
			sizeof(int);
	if (world->a_h == NULL)
		if (!(world->a_h = malloc(world->size_main)))
			exit(0);
	if (world->video_buffer == NULL)
	{
		if (!(world->video_buffer = malloc(WIN_WIDTH * WIN_HEIGHT * 4 *
												sizeof(unsigned char))))
			exit(0);
	}
	ft_bzero(world->video_buffer, WIN_WIDTH * WIN_HEIGHT * 4 *
												sizeof(unsigned char));
	ft_bzero(world->a_h, world->size_main);
	if (world->mode_cluster == 1)
		return ;
	if (world->mode == 0)
	{
		printf("laucnh CPU\n");
		launch_cpu(world);
	}
	else
		launch_gpu(world);
}

int				main(int argc, char **argv)
{
	if (argc == 1)
		choose_main_launcher(argv, 0);
	else if (argc == 3)
	{
		if ((ft_strcmp("client", argv[1]) == 0))
			choose_main_launcher(argv, 2);
		else
			ft_putstr("Usage: ./bin/RT client [IP]");
	}
	else
		ft_putstr("Usage: launch only with ./bin/RT");
	SDL_Quit();
	return (0);
}
