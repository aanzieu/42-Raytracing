/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_refresh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:52:59 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/26 16:31:00 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

void	refresh_sphere(t_world *world, int i)
{
	t_sphere	*tmp;

	tmp = world->spheres_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->spheres[i].pos;
			tmp->radius = world->spheres[i].radius;
			tmp->color = world->spheres[i].color;
			tmp->chess = world->spheres[i].chess;
			tmp->rgba = world->spheres[i].rgba;
			tmp->reflection_coef = world->spheres[i].reflection_coef;
			tmp->refraction_coef = world->spheres[i].refraction_coef;
			tmp->transparence_coef = world->spheres[i].transparence_coef;
			tmp->texture = world->spheres[i].texture;
			tmp->perlin = world->spheres[i].perlin;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_cone(t_world *world, int i)
{
	t_cone	*tmp;

	tmp = world->cones_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->cones[i].pos;
			tmp->up = world->cones[i].up;
			tmp->half_angle = world->cones[i].half_angle;
			tmp->height = world->cones[i].height;
			tmp->color = world->cones[i].color;
			tmp->chess = world->cones[i].chess;
			tmp->reflection_coef = world->cones[i].reflection_coef;
			tmp->refraction_coef = world->cones[i].refraction_coef;
			tmp->transparence_coef = world->cones[i].transparence_coef;
			tmp->perlin = world->cones[i].perlin;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_cylinder(t_world *world, int i)
{
	t_cylinder	*tmp;

	tmp = world->cylinders_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->cylinders[i].pos;
			tmp->up = world->cylinders[i].up;
			tmp->radius = world->cylinders[i].radius;
			tmp->height = world->cylinders[i].height;
			tmp->color = world->cylinders[i].color;
			tmp->chess = world->cylinders[i].chess;
			tmp->reflection_coef = world->cylinders[i].reflection_coef;
			tmp->refraction_coef = world->cylinders[i].refraction_coef;
			tmp->transparence_coef = world->cylinders[i].transparence_coef;
			tmp->perlin = world->cylinders[i].perlin;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_plane(t_world *world, int i)
{
	t_plane	*tmp;

	tmp = world->planes_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->planes[i].pos;
			tmp->up = world->planes[i].up;
			tmp->color = world->planes[i].color;
			tmp->chess = world->planes[i].chess;
			tmp->reflection_coef = world->planes[i].reflection_coef;
			tmp->refraction_coef = world->planes[i].refraction_coef;
			tmp->transparence_coef = world->planes[i].transparence_coef;
			tmp->perlin = world->planes[i].perlin;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_torus(t_world *world, int i)
{
	t_torus	*tmp;

	tmp = world->torus_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->torus[i].pos;
			tmp->normal = world->torus[i].normal;
			tmp->radius_small = world->torus[i].radius_small;
			tmp->radius_big = world->torus[i].radius_big;
			tmp->color = world->torus[i].color;
			tmp->chess = world->torus[i].chess;
			tmp->reflection_coef = world->torus[i].reflection_coef;
			tmp->refraction_coef = world->torus[i].refraction_coef;
			tmp->transparence_coef = world->torus[i].transparence_coef;
			tmp->perlin = world->torus[i].perlin;
			break ;
		}
		tmp = tmp->next;
	}
}
