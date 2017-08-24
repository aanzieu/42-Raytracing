/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_objects_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 10:37:11 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 13:39:17 by aanzieu          ###   ########.fr       */
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
	hyper->maxm = nw->maxm;
	hyper->color = nw->color;
	hyper->chess = nw->chess;
	hyper->next = NULL;
	return (hyper);
}

t_torus						*new_torus(t_torus *nw, int id)
{
	t_torus	*t;

	if (!(t = (t_torus *)ft_memalloc(sizeof(t_torus))))
		ft_putendl_fd("Erroc Malloc on Torus", 1);
	t->id = id;
	t->radius = nw->radius;
	t->radius2 = nw->radius2;
	t->pos = nw->pos;
	t->color = nw->color;
	t->chess = nw->chess;
	t->reflection_coef = nw->reflection_coef;
	t->refraction_coef = nw->refraction_coef;
	t->next = NULL;
	return (t);
}

t_mobius					*new_mobius(t_mobius *nw)
{
	t_mobius	*s;

	if (!(s = (t_mobius *)ft_memalloc(sizeof(t_mobius))))
		ft_putendl_fd("Erroc Malloc on Sphere", 1);
	s->radius = nw->radius;
	s->pos = nw->pos;
	s->color = nw->color;
	s->reflection_coef = nw->reflection_coef;
	s->refraction_coef = nw->refraction_coef;
	s->next = NULL;
	return (s);
}
