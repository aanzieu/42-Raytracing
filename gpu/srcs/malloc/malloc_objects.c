/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:54:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 17:41:18 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	add_sphere_tmp(t_sphere **spheres, double radius, t_vec3d pos)
{
	t_sphere *new_sphere;
	t_sphere *tmp;

	tmp = *spheres;
	new_sphere = malloc(sizeof(t_sphere));
	new_sphere->radius = radius;
	new_sphere->pos = pos;
	new_sphere->next = NULL;

	if (!tmp)
		*spheres = new_sphere;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sphere;
	}
}

t_plane		*new_plan(t_plane *nw)
{
	t_plane	*p;

	if (!(p = (t_plane*)malloc(sizeof(t_plane))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	p->up = nw->up;
	p->pos = nw->pos;
	p->color = nw->color;
	p->next = NULL;
	return (p);
}

t_cone		*new_cone(t_cone *nw)
{
	t_cone	*c;

	if (!(c = (t_cone *)ft_memalloc(sizeof(t_cone))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	c->half_angle = nw->half_angle;
	c->pos = nw->pos;
	c->up = nw->up;
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
	l->pos = nw->pos;
	l->color = nw->color;
	l->next = NULL;
	return (l);
}

t_cylinder	*new_cylinder(t_cylinder *nw)
{
	t_cylinder	*cy;

	if (!(cy = (t_cylinder *)ft_memalloc(sizeof(t_cylinder))))
		ft_putendl_fd("Erroc Malloc on Cylinders", 1);
	cy->pos = nw->pos;
	cy->up = nw->up;
	cy->up_v = nw->up_v;
	cy->radius = nw->radius;
	cy->color = nw->color;
	cy->next = NULL;
	return (cy);
}
