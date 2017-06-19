/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_free_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:27:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 09:21:23 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"
/*
void		thread_free_para(t_para *p)
{
	t_para	*fst;
	t_para	*tmp;

	fst = p;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	p = NULL;
}

void		thread_free_elips(t_elips *s)
{
	t_elips	*fst;
	t_elips	*tmp;

	fst = s;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	s = NULL;
}

void		thread_free_lists(t_thread_cpy *cpy)
{
	thread_free_para(cpy->scene->para);
	thread_free_elips(cpy->scene->elips);
	thread_free_sphere(cpy->scene->s);
	thread_free_cy(cpy->scene->cy);
	thread_free_plan(cpy->scene->p);
	thread_free_cone(cpy->scene->co);
	thread_free_light(cpy->scene->l);
	free(cpy->scene);
	cpy->s_l = 0;
	cpy->bpp = 0;
	cpy->endian = 0;
}
*/
