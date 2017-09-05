/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_malloc_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 09:48:31 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 16:25:09 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_plan		*new_plan(t_plan *nw)
{
	t_plan	*p;

	if (!(p = (t_plan*)malloc(sizeof(t_plan))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	p->normal = nw->normal;
	p->origin = nw->origin;
	p->color = nw->color;
	p->next = NULL;
	return (p);
}

t_cone		*new_cone(t_cone *nw)
{
	t_cone	*c;

	if (!(c = (t_cone *)ft_memalloc(sizeof(t_cone))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	c->angle = nw->angle;
	c->center = nw->center;
	c->normal = nw->normal;
	c->color = nw->color;
	c->next = NULL;
	return (c);
}

t_sphere	*new_sphere(t_sphere *nw)
{
	t_sphere	*s;

	if (!(s = (t_sphere *)ft_memalloc(sizeof(t_sphere))))
		ft_putendl_fd("Erroc Malloc on Sphere", 1);
	s->radius = nw->radius;
	s->pos = nw->pos;
	s->color = nw->color;
	s->next = NULL;
	return (s);
}

t_light		*new_light(t_light *nw)
{
	t_light	*l;

	if (!(l = (t_light *)ft_memalloc(sizeof(t_light))))
		ft_putendl_fd("Erroc Malloc on Light", 1);
	l->position = nw->position;
	l->color = nw->color;
	l->next = NULL;
	return (l);
}

t_cy		*new_cy(t_cy *nw)
{
	t_cy	*cy;

	if (!(cy = (t_cy *)ft_memalloc(sizeof(t_cy))))
		ft_putendl_fd("Erroc Malloc on Cylinders", 1);
	cy->center = nw->center;
	cy->normal = nw->normal;
	cy->angle = nw->angle;
	cy->color = nw->color;
	cy->limit = nw->limit;
	cy->next = NULL;
	return (cy);
}
