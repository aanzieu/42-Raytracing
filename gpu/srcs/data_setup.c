/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/08/15 13:18:18 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			data_setup(t_world *world)
{
	world->mode = 0;
	world->light_type = 1;
	world->viewplane.width = (double)((M_PI / 4) / 2);
	world->viewplane.height = ((double)((double)(WIN_HEIGHT) /
								(double)(WIN_WIDTH)) * world->viewplane.width);
	world->render_factor = 1;
	world->viewplane.dist = 1;
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
	world->animation_forward = 0;
	world->recording = 0;
	world->a_h = NULL;
	world->video_buffer = NULL;
	world->intensity = 2.1;

}
