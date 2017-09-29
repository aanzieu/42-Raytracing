/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cpu_gpu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/09/29 17:19:52 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <display.h>
#include <unistd.h>

void			get_viewplane_cluster(t_world *world)
{
	world->viewplane.x_res = (double)(WIN_WIDTH) / world->render_factor;
	world->viewplane.y_res = (double)
		(world->offsets.y_max - world->offsets.y_min) / world->render_factor;
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

void			refresh_viewplane_cluster(t_world *world)
{
	world->win_width = WIN_WIDTH * world->aa;
	world->win_height = (WIN_HEIGHT) * world->aa;
	world->viewplane.width = (double)((M_PI / 4) / 2);
	world->viewplane.height = ((double)((double)(world->win_height) /
		(double)(WIN_WIDTH)) * world->viewplane.width);
	world->viewplane_aa.width = (double)((M_PI / 4) / 2);
	world->viewplane_aa.height = ((double)((double)(world->win_height) /
		(double)(world->win_width)) * world->viewplane_aa.width);
}
