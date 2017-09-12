/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 13:20:56 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/12 13:35:25 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rt.h"

static void		clear_world2(t_world *world)
{
	if (world->cubes_tmp != NULL)
		free_cube(&world->cubes_tmp, &world->cubes, &world->cubes_len);
	if (world->triangles_tmp != NULL)
		free_triangle(&world->triangles_tmp, &world->triangles,\
					&world->triangles_len);
	if (world->title != NULL)
	{
		free(world->title);
		world->title = NULL;
	}
	if (world->video_buffer != NULL)
	{
		free(world->video_buffer);
		world->video_buffer = NULL;
	}
	if (world->a_h != NULL)
	{
		free(world->a_h);
		world->a_h = NULL;
	}
}

void			clear_world(t_world *world)
{
	if (world->lights_tmp != NULL)
		free_light(&world->lights_tmp, &world->lights, &world->lights_len);
	if (world->spheres_tmp != NULL)
		free_sphere(&world->spheres_tmp, &world->spheres, &world->spheres_len);
	if (world->planes_tmp != NULL)
		free_plan(&world->planes_tmp, &world->planes, &world->planes_len);
	if (world->cylinders_tmp != NULL)
		free_cy(&world->cylinders_tmp, &world->cylinders,\
				&world->cylinders_len);
	if (world->cones_tmp != NULL)
		free_cone(&world->cones_tmp, &world->cones, &world->cones_len);
	if (world->mobius_tmp != NULL)
		free_mobius(&world->mobius_tmp, &world->mobius, &world->mobius_len);
	if (world->torus_tmp != NULL)
		free_torus(&world->torus_tmp, &world->torus, &world->torus_len);
	if (world->hyperboloids_tmp != NULL)
		free_hyper(&world->hyperboloids_tmp, &world->hyperboloids,\
				&world->hyperboloids_len);
	if (world->paraboloids_tmp != NULL)
		free_para(&world->paraboloids_tmp, &world->paraboloids,\
				&world->paraboloids_len);
	clear_world2(world);
}
