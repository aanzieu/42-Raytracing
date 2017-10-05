/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:10:03 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/03 17:41:25 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void			refresh_viewplane(t_world *world)
{
	world->win_width = WIN_WIDTH * world->aa;
	world->win_height = WIN_HEIGHT * world->aa;
	world->viewplane.width = (double)((M_PI / 4) / 2);
	world->viewplane.height = ((double)((double)(WIN_HEIGHT) /
								(double)(WIN_WIDTH)) * world->viewplane.width);
	world->viewplane_aa.width = (double)((M_PI / 4) / 2);
	world->viewplane_aa.height = ((double)((double)(world->win_height) /
					(double)(world->win_width)) * world->viewplane_aa.width);
}

void			data_setup_2(t_world *world)
{
	world->triangles = NULL;
	world->triangles_len = 0;
	world->cubes = NULL;
	world->cubes_len = 0;
	world->h_cubes = NULL;
	world->h_cubes_len = 0;
	world->keys.light_none = 0;
	world->reload_buffer = 1;
	world->redraw = 2;
	world->id = 0;
	world->animation_forward = 0;
	world->recording = 0;
	world->a_h = NULL;
	world->video_buffer = NULL;
	world->intensity = 2.1;
	world->img_scene = 0;
	world->hover_menu = 0;
	world->hover_ui = 0;
	world->clientrender = 0;
	world->on = 0;
	world->camera.up_v = (t_vec3d){0, 1, 0};
}

void			data_setup(t_world *world)
{
	world->aa = 1;
	refresh_viewplane(world);
	world->mode = 0;
	world->anaglyph_depth = 30;
	world->light_type = 1;
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
	data_setup_2(world);
}
