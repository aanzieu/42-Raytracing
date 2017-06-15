/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_free_thread_next.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:29:22 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 17:02:37 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void		thread_free_plan(t_plan *p)
{
	t_plan	*fst;
	t_plan	*tmp;

	fst = p;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	p = NULL;
}

void		thread_free_sphere(t_sphere *s)
{
	t_sphere	*fst;
	t_sphere	*tmp;

	fst = s;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	s = NULL;
}

void		thread_free_cone(t_cone *c)
{
	t_cone	*fst;
	t_cone	*tmp;

	fst = c;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	c = NULL;
}

void		thread_free_cy(t_cy *cy)
{
	t_cy	*fst;
	t_cy	*tmp;

	fst = cy;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	cy = NULL;
}

void		thread_free_light(t_light *l)
{
	t_light	*fst;
	t_light	*tmp;

	fst = l;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	l = NULL;
}
