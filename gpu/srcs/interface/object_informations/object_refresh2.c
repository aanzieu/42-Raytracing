/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_refresh2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:52:59 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/13 18:07:14 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	refresh_mobius(t_world *world, int i)
{
	t_mobius	*tmp;

	tmp = world->mobius_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->mobius[i].pos;
			tmp->radius = world->mobius[i].radius;
			tmp->color = world->mobius[i].color;
			tmp->chess = world->mobius[i].chess;
			tmp->reflection_coef = world->mobius[i].reflection_coef;
			tmp->refraction_coef = world->mobius[i].refraction_coef;
			tmp->transparence_coef = world->mobius[i].transparence_coef;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_disk(t_world *world, int i)
{
	t_disk	*tmp;

	tmp = world->disks_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->disks[i].pos;
			tmp->up = world->disks[i].up;
			tmp->radius = world->disks[i].radius;
			tmp->radius_squared = world->disks[i].radius_squared;
			tmp->color = world->disks[i].color;
			tmp->chess = world->disks[i].chess;
			tmp->reflection_coef = world->disks[i].reflection_coef;
			tmp->refraction_coef = world->disks[i].refraction_coef;
			tmp->transparence_coef = world->disks[i].transparence_coef;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_cube(t_world *world, int i)
{
	t_cube	*tmp;

	tmp = world->cubes_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->min = world->cubes[i].min;
			tmp->max = world->cubes[i].max;
			tmp->up = world->cubes[i].up;
			tmp->color = world->cubes[i].color;
			tmp->chess = world->cubes[i].chess;
			tmp->reflection_coef = world->cubes[i].reflection_coef;
			tmp->refraction_coef = world->cubes[i].refraction_coef;
			tmp->transparence_coef = world->cubes[i].transparence_coef;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_paraboloid(t_world *world, int i)
{
	t_paraboloid	*tmp;

	tmp = world->paraboloids_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->top = world->paraboloids[i].top;
			tmp->normal = world->paraboloids[i].normal;
			tmp->distance = world->paraboloids[i].distance;
			tmp->maxm = world->paraboloids[i].maxm;
			tmp->color = world->paraboloids[i].color;
			tmp->chess = world->paraboloids[i].chess;
			tmp->reflection_coef = world->paraboloids[i].reflection_coef;
			tmp->refraction_coef = world->paraboloids[i].refraction_coef;
			tmp->transparence_coef = world->paraboloids[i].transparence_coef;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_hyperboloid(t_world *world, int i)
{
	t_hyperboloid	*tmp;

	tmp = world->hyperboloids_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->top = world->hyperboloids[i].top;
			tmp->normal = world->hyperboloids[i].normal;
			tmp->maxm = world->hyperboloids[i].maxm;
			tmp->radius = world->hyperboloids[i].radius;
			tmp->color = world->hyperboloids[i].color;
			tmp->chess = world->hyperboloids[i].chess;
			tmp->reflection_coef = world->hyperboloids[i].reflection_coef;
			tmp->refraction_coef = world->hyperboloids[i].refraction_coef;
			tmp->transparence_coef = world->hyperboloids[i].transparence_coef;
			break ;
		}
		tmp = tmp->next;
	}
}
