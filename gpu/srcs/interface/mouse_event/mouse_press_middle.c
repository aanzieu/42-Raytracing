/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_middle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:56:05 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 12:40:23 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"
#include "float.h"

static int		remove_object_4(t_world *world, t_intersection *i)
{
	if (i->type == 'b')
	{
		remove_paraboloid(&world->paraboloids_tmp, i);
		load_paraboloids(&world->paraboloids, world->paraboloids_tmp,
						&world->paraboloids_len);
		return (1);
	}
	if (i->type == 't')
	{
		remove_triangle(&world->triangles_tmp, i);
		load_triangles(&world->triangles, world->triangles_tmp,
						&world->triangles_len);
		return (1);
	}
	if (i->type == 'u')
	{
		remove_h_cube(&world->h_cubes_tmp, i);
		load_h_cubes(&world->h_cubes, world->h_cubes_tmp, &world->h_cubes_len);
		return (1);
	}
	return (0);
}

static int		remove_object_3(t_world *world, t_intersection *i)
{
	if (i->type == 'd')
	{
		remove_disk(&world->disks_tmp, i);
		load_disks(&world->disks, world->disks_tmp, &world->disks_len);
		return (1);
	}
	if (i->type == 'c')
	{
		remove_cube(&world->cubes_tmp, i);
		load_cubes(&world->cubes, world->cubes_tmp, &world->cubes_len);
		return (1);
	}
	if (i->type == 'h')
	{
		remove_hyperboloid(&world->hyperboloids_tmp, i);
		load_hyperboloids(&world->hyperboloids, world->hyperboloids_tmp,\
						&world->hyperboloids_len);
		return (1);
	}
	return (remove_object_4(world, i));
}

static int		remove_object_2(t_world *world, t_intersection *i)
{
	if (i->type == 'p')
	{
		remove_plane(&world->planes_tmp, i);
		load_planes(&world->planes, world->planes_tmp, &world->planes_len);
		return (1);
	}
	if (i->type == 'o')
	{
		remove_torus(&world->torus_tmp, i);
		load_torus(&world->torus, world->torus_tmp, &world->torus_len);
		return (1);
	}
	if (i->type == 'm')
	{
		remove_mobius(&world->mobius_tmp, i);
		load_mobius(&world->mobius, world->mobius_tmp, &world->mobius_len);
		return (1);
	}
	return (remove_object_3(world, i));
}

static int		remove_object(t_world *world, t_intersection *i)
{
	if (i->type == 's')
	{
		remove_sphere(&world->spheres_tmp, i);
		load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);
		return (1);
	}
	if (i->type == 'x')
	{
		remove_cone(&world->cones_tmp, i);
		load_cones(&world->cones, world->cones_tmp, &world->cones_len);
		return (1);
	}
	if (i->type == 'y')
	{
		remove_cylinder(&world->cylinders_tmp, i);
		load_cylinders(&world->cylinders, world->cylinders_tmp,\
						&world->cylinders_len);
		return (1);
	}
	return (remove_object_2(world, i));
}

int				mousepress_middle(struct nk_context *ctx, t_world *world,\
						struct nk_vec2 pos)
{
	t_ray			ray;
	t_intersection	intersection;
	t_vec2d			pad;

	intersection.t = DBL_MAX;
	intersection.type = '0';
	intersection.id = -1;
	if (ctx->input.mouse.buttons[NK_BUTTON_MIDDLE].down)
	{
		pad.x = ctx->input.mouse.pos.x - pos.x;
		pad.y = ctx->input.mouse.pos.y - pos.y - 40;
		if (pad.x < 0 || pad.y < 0 || pad.x > WIN_WIDTH || pad.y > WIN_HEIGHT)
			return (0);
		get_up_left(world);
		get_ray_direction(*(world), &ray, pad.x / world->render_factor,\
						pad.y / world->render_factor);
		get_closest_intersection(*(world), ray, &intersection);
		if (intersection.t != INFINITY)
			if (remove_object(world, &intersection) == 1)
				return (1);
	}
	return (0);
}
