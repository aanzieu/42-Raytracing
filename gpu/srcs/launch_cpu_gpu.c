/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cpu_gpu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/10/02 10:50:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <display.h>
#include <unistd.h>
#include <cluster.h>

static	void	*perform_thread(void *arg)
{
	t_thread_input	*thread;
	int				x;
	int				x_aa;
	int				y;
	int				y_aa;

	thread = (t_thread_input *)arg;
	y = (((thread->th) * ((thread->y_max - thread->y_min) / NB_TH)
		+ thread->y_min)) - 1;
	y_aa = y * thread->aa;
	while (++y < (thread->th + 1) * ((thread->y_max - thread->y_min) / NB_TH) +
																thread->y_min)
	{
		x = -1;
		x_aa = 0;
		while (++x < thread->world->viewplane.x_res)
		{
			thread->world->a_h[(y - thread->y_min) *
			thread->world->viewplane.x_res + x] =
				ray_tracer_cpu(*thread->world, x_aa, y_aa);
			x_aa += thread->world->aa;
		}
		y_aa += thread->world->aa;
	}
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
	}
	i = -1;
	while (++i < NB_TH)
		pthread_join(world->thread[i], NULL);
	return (0);
}

void			launch_cpu(t_world *world)
{
	int i;

	i = -1;
	if (!world->p)
	{
		if (!(world->p = (int *)malloc(512 * sizeof(int))))
			show_error("Error malloc noise\n");
		perlin_noise_setup(world);
	}
	if (world->clientrender == 1)
	{
		ft_printf("Calculating on Cpu\n");
		refresh_viewplane_cluster(world);
		get_viewplane_cluster(world);
		launch_thread(world, world->offsets.y_min / world->render_factor,
				world->offsets.y_max / world->render_factor, world->offsets.aa);
		ft_printf("End of Calculate\n");
		return ;
	}
	refresh_viewplane_cluster(world);
	get_viewplane(world);
	launch_thread(world, 0, world->viewplane.y_res, world->aa);
}

/*
**	On event receive send data to handler
*/

void			launch_gpu(t_world *world)
{
	if (world->clientrender == 1)
	{
		ft_printf("Calculating on Gpu\n");
		refresh_viewplane_cluster(world);
		get_viewplane_cluster(world);
		render_cuda(world->a_h, WIN_WIDTH,
				world->offsets.y_max - world->offsets.y_min, *world, 0);
		ft_printf("End of Calculate\n");
		return ;
	}
	get_viewplane(world);
	render_cuda(world->a_h, world->viewplane.x_res,
		world->viewplane.y_res, *world, 0);
}
