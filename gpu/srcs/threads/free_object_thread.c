/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_free_thread_next.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:29:22 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 08:02:29 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../../includes/rt.h>

void		thread_free_plan(t_plane *p)
{
	t_plane	*fst;
	t_plane	*tmp;

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

void		thread_free_cylinder(t_cylinder *cy)
{
	t_cylinder	*fst;
	t_cylinder	*tmp;

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
