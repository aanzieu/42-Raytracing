/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_objects_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 10:37:11 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:13:33 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_paraboloid				*new_paraboloid(t_paraboloid *nw, int id)
{
	t_paraboloid	*para;

	if (!(para = (t_paraboloid *)ft_memalloc(sizeof(t_paraboloid))))
		ft_putendl_fd("Erroc Malloc on paraboloid", 1);
	para->id = id;
	para->top = nw->top;
	para->normal = nw->normal;
	para->distance = nw->distance;
	para->maxm = nw->maxm;
	para->color = nw->color;
	para->chess = nw->chess;
	para->reflection_coef = nw->reflection_coef;
	para->refraction_coef = nw->refraction_coef;
	para->transparence_coef = nw->transparence_coef;
	para->perlin = nw->perlin;
	para->next = NULL;
	return (para);
}

t_hyperboloid				*new_hyperboloid(t_hyperboloid *nw, int id)
{
	t_hyperboloid *hyper;

	if (!(hyper = (t_hyperboloid *)ft_memalloc(sizeof(t_hyperboloid))))
		ft_putendl_fd("Erroc Malloc on hyperboloid", 1);
	hyper->id = id;
	hyper->top = nw->top;
	hyper->normal = nw->normal;
	hyper->radius = nw->radius;
	hyper->reflection_coef = nw->reflection_coef;
	hyper->refraction_coef = nw->refraction_coef;
	hyper->transparence_coef = nw->transparence_coef;
	hyper->maxm = nw->maxm;
	hyper->color = nw->color;
	hyper->chess = nw->chess;
	hyper->perlin = nw->perlin;
	hyper->next = NULL;
	return (hyper);
}

t_torus						*new_torus(t_torus *nw, int id)
{
	t_torus	*t;

	if (!(t = (t_torus *)ft_memalloc(sizeof(t_torus))))
		ft_putendl_fd("Erroc Malloc on Torus", 1);
	t->id = id;
	t->radius_small = nw->radius_small;
	t->radius_big = nw->radius_big;
	t->pos = nw->pos;
	t->color = nw->color;
	t->chess = nw->chess;
	t->reflection_coef = nw->reflection_coef;
	t->refraction_coef = nw->refraction_coef;
	t->transparence_coef = nw->transparence_coef;
	t->perlin = nw->perlin;
	t->next = NULL;
	return (t);
}

t_mobius					*new_mobius(t_mobius *nw, int id)
{
	t_mobius	*s;

	if (!(s = (t_mobius *)ft_memalloc(sizeof(t_mobius))))
		ft_putendl_fd("Erroc Malloc on Sphere", 1);
	s->id = id;
	s->radius = nw->radius;
	s->pos = nw->pos;
	s->color = nw->color;
	s->reflection_coef = nw->reflection_coef;
	s->refraction_coef = nw->refraction_coef;
	s->transparence_coef = nw->transparence_coef;
	s->perlin = nw->perlin;
	s->next = NULL;
	return (s);
}
