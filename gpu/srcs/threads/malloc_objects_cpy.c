/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_malloc_cpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:45:45 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/21 11:39:33 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_plane		*copy_plan(t_plane *obj)
{
	t_plane *newl;

	if (obj)
	{
		if (!(newl = (t_plane *)malloc(sizeof(t_plane))))
			ft_putendl_fd("Error : Can't Malloc copy thread plan\n", 1);
		newl->up = obj->up;
		newl->pos = obj->pos;
		newl->color = obj->color;
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
		newl->pos = obj->pos;
		newl->color = obj->color;
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
		news->radius = obj->radius;
		news->pos = obj->pos;
		news->color = obj->color;
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
		news->half_angle = obj->half_angle;
		news->pos = obj->pos;
		news->up = obj->up;
		news->color = obj->color;
		news->next = NULL;
		if (obj->next)
			news->next = copy_cone(obj->next);
		return (news);
	}
	return (NULL);
}

t_cylinder	*copy_cylinder(t_cylinder *obj)
{
	t_cylinder *news;

	if (obj)
	{
		if (!(news = (t_cylinder *)malloc(sizeof(t_cylinder))))
			ft_putendl_fd("error : can't malloc copy thread cy\n", 1);
		news->pos = obj->pos;
		news->up = obj->up;
		news->up_v = obj->up_v;
		news->radius = obj->radius;
		news->color = obj->color;
		news->next = NULL;
		if (news && obj->next)
			news->next = copy_cylinder(obj->next);
		return (news);
	}
	return (NULL);
}
