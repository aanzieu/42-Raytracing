/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_objects_bonus2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:13:05 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:13:24 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_triangle					*new_triangle(t_triangle *nw, int id)
{
	t_triangle	*t;

	if (!(t = (t_triangle *)ft_memalloc(sizeof(t_triangle))))
		ft_putendl_fd("Erroc Malloc on triangle", 1);
	t->pos = nw->pos;
	t->v1 = nw->v1;
	t->v2 = nw->v2;
	t->up = nw->up;
	t->color = nw->color;
	t->chess = nw->chess;
	t->id = id;
	t->reflection_coef = nw->reflection_coef;
	t->refraction_coef = nw->refraction_coef;
	t->transparence_coef = nw->transparence_coef;
	t->next = NULL;
	return (t);
}

t_cube						*new_cube(t_cube *nw, int id)
{
	t_cube	*t;

	if (!(t = (t_cube *)ft_memalloc(sizeof(t_cube))))
		ft_putendl_fd("Erroc Malloc on cube", 1);
	t->min = nw->min;
	t->max = nw->max;
	t->color = nw->color;
	t->chess = nw->chess;
	t->id = id;
	t->reflection_coef = nw->reflection_coef;
	t->refraction_coef = nw->refraction_coef;
	t->transparence_coef = nw->transparence_coef;
	t->next = NULL;
	return (t);
}

t_h_cube					*new_h_cube(t_h_cube *nw, int id)
{
	t_h_cube	*t;

	if (!(t = (t_h_cube *)ft_memalloc(sizeof(t_h_cube))))
		ft_putendl_fd("Erroc Malloc on h_cube", 1);
	t->pos = nw->pos;
	t->color = nw->color;
	t->chess = nw->chess;
	t->id = id;
	t->reflection_coef = nw->reflection_coef;
	t->refraction_coef = nw->refraction_coef;
	t->transparence_coef = nw->transparence_coef;
	t->next = NULL;
	return (t);
}
