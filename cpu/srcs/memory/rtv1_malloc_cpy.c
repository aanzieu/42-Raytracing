/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_malloc_cpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:45:45 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 17:02:43 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_plan		*copy_plan(t_plan *obj)
{
	t_plan *newl;

	if (obj)
	{
		if (!(newl = (t_plan *)malloc(sizeof(t_plan))))
			ft_putendl_fd("Error : Can't Malloc copy thread plan\n", 1);
		newl->origin = obj->origin;
		newl->color = obj->color;
		newl->normal = obj->normal;
		newl->next = NULL;
		if (newl && obj->next)
			newl->next = copy_plan(obj->next);
		return (newl);
	}
	return (NULL);
}

t_light		*copy_light(t_light *obj)
{
	t_light *newl;

	if (obj)
	{
		if (!(newl = (t_light *)malloc(sizeof(t_light))))
			ft_putendl_fd("error : can't malloc copy thread light\n", 1);
		newl->position = obj->position;
		newl->color = obj->color;
		newl->light_lenght = obj->light_lenght;
		newl->light_distance = obj->light_distance;
		newl->next = NULL;
		if (newl && obj->next)
			newl->next = copy_light(obj->next);
		return (newl);
	}
	return (NULL);
}

t_sphere	*copy_sphere(t_sphere *obj)
{
	t_sphere *news;

	if (obj)
	{
		if (!(news = (t_sphere *)malloc(sizeof(t_sphere))))
			ft_putendl_fd("error : can't malloc copy thread sphere\n", 1);
		news->pos = obj->pos;
		news->color = obj->color;
		news->radius = obj->radius;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_sphere(obj->next);
		return (news);
	}
	return (NULL);
}

t_cone		*copy_cone(t_cone *obj)
{
	t_cone *news;

	if (obj)
	{
		if (!(news = (t_cone *)malloc(sizeof(t_cone))))
			ft_putendl_fd("error : can't malloc copy thread cone\n", 1);
		news->center = obj->center;
		news->normal = obj->normal;
		news->color = obj->color;
		news->angle = obj->angle;
		news->next = NULL;
		if (obj->next)
			news->next = copy_cone(obj->next);
		return (news);
	}
	return (NULL);
}

t_cy		*copy_cy(t_cy *obj)
{
	t_cy *news;

	if (obj)
	{
		if (!(news = (t_cy *)malloc(sizeof(t_cy))))
			ft_putendl_fd("error : can't malloc copy thread cy\n", 1);
		news->center = obj->center;
		news->normal = obj->normal;
		news->color = obj->color;
		news->angle = obj->angle;
		news->limit = obj->limit;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_cy(obj->next);
		return (news);
	}
	return (NULL);
}
