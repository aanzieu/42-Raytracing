/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:54:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 13:22:02 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>

t_plane		*new_plan(t_plane *nw, int id)
{
	t_plane	*p;

	if (!(p = (t_plane*)malloc(sizeof(t_plane))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	p->id = id;
	p->up = nw->up;
	p->pos = nw->pos;
	p->color = nw->color;
	p->chess = nw->chess;
	p->reflection_coef = nw->reflection_coef;
	p->refraction_coef = nw->refraction_coef;
	p->transparence_coef = nw->transparence_coef;
	p->perlin = nw->perlin;
	p->next = NULL;
	return (p);
}

t_disk		*new_disk(t_disk *nw, int id)
{
	t_disk	*d;

	if (!(d = (t_disk*)malloc(sizeof(t_disk))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	d->id = id;
	d->up = nw->up;
	d->pos = nw->pos;
	d->color = nw->color;
	d->radius = nw->radius;
	d->radius_squared = nw->radius_squared;
	d->reflection_coef = nw->reflection_coef;
	d->refraction_coef = nw->refraction_coef;
	d->transparence_coef = nw->transparence_coef;
	d->chess = nw->chess;
	d->perlin = nw->perlin;
	d->next = NULL;
	return (d);
}

t_cone		*new_cone(t_cone *nw, int id)
{
	t_cone	*c;

	if (!(c = (t_cone *)ft_memalloc(sizeof(t_cone))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	c->id = id;
	c->half_angle = nw->half_angle;
	c->height = nw->height;
	c->pos = nw->pos;
	c->up = nw->up;
	c->color = nw->color;
	c->chess = nw->chess;
	c->reflection_coef = nw->reflection_coef;
	c->refraction_coef = nw->refraction_coef;
	c->transparence_coef = nw->transparence_coef;
	c->min = nw->min;
	c->max = nw->max;
	c->perlin = nw->perlin;
	c->next = NULL;
	return (c);
}

t_sphere	*new_sphere(t_sphere *nw, int id)
{
	t_sphere	*s;

	if (!(s = (t_sphere *)ft_memalloc(sizeof(t_sphere))))
		ft_putendl_fd("Erroc Malloc on Sphere", 1);
	s->id = id;
	s->radius = nw->radius;
	s->pos = nw->pos;
	s->color = nw->color;
	s->chess = nw->chess;
	s->reflection_coef = nw->reflection_coef;
	s->refraction_coef = nw->refraction_coef;
	s->transparence_coef = nw->transparence_coef;
	s->perlin = nw->perlin;
	s->perlin.is_set = nw->perlin.is_set;
	s->perlin.pre_set = nw->perlin.pre_set;
	s->perlin.scale = nw->perlin.scale;
	s->perlin.amount = nw->perlin.amount;
	s->next = NULL;
	return (s);
}

t_cylinder	*new_cylinder(t_cylinder *nw, int id)
{
	t_cylinder	*cy;

	if (!(cy = (t_cylinder *)ft_memalloc(sizeof(t_cylinder))))
		ft_putendl_fd("Erroc Malloc on Cylinders", 1);
	cy->id = id;
	cy->pos = nw->pos;
	cy->up = nw->up;
	cy->up_v = nw->up_v;
	cy->radius = nw->radius;
	cy->height = nw->height;
	cy->color = nw->color;
	cy->chess = nw->chess;
	cy->reflection_coef = nw->reflection_coef;
	cy->refraction_coef = nw->refraction_coef;
	cy->transparence_coef = nw->transparence_coef;
	cy->perlin = nw->perlin;
	cy->next = NULL;
	return (cy);
}
