/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_refresh3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:52:59 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/20 14:29:05 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void	refresh_triangle(t_world *world, int i)
{
	t_triangle	*tmp;

	tmp = world->triangles_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->triangles[i].pos;
			tmp->up = world->triangles[i].up;
			tmp->v1 = world->triangles[i].v1;
			tmp->v2 = world->triangles[i].v2;
			tmp->color = world->triangles[i].color;
			tmp->chess = world->triangles[i].chess;
			tmp->reflection_coef = world->triangles[i].reflection_coef;
			tmp->refraction_coef = world->triangles[i].refraction_coef;
			tmp->transparence_coef = world->triangles[i].transparence_coef;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_h_cube(t_world *world, int i)
{
	t_h_cube	*tmp;

	tmp = world->h_cubes_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->h_cubes[i].pos;
			tmp->color = world->h_cubes[i].color;
			tmp->chess = world->h_cubes[i].chess;
			tmp->reflection_coef = world->h_cubes[i].reflection_coef;
			tmp->refraction_coef = world->h_cubes[i].refraction_coef;
			tmp->transparence_coef = world->h_cubes[i].transparence_coef;
			break ;
		}
		tmp = tmp->next;
	}
}

void	refresh_light(t_world *world, int i)
{
	t_light	*tmp;

	tmp = world->lights_tmp;
	while (tmp)
	{
		if (tmp->id == world->id_save)
		{
			tmp->pos = world->lights[i].pos;
			tmp->color = world->lights[i].color;
			tmp->intensity_coef = world->lights[i].intensity_coef;
			break ;
		}
		tmp = tmp->next;
	}
}
