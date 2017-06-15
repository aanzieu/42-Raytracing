/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_malloc_cpy_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:56:27 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 18:19:29 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_para		*copy_para(t_para *obj)
{
	t_para *newl;

	if (obj)
	{
		if (!(newl = (t_para *)malloc(sizeof(t_para))))
			ft_putendl_fd("Error : Can't Malloc copy thread plan\n", 1);
		newl->top = obj->top;
		newl->color = obj->color;
		newl->normal = obj->normal;
		newl->distance = obj->distance;
		newl->maxm = obj->maxm;
		newl->next = NULL;
		if (newl && obj->next)
			newl->next = copy_para(obj->next);
		return (newl);
	}
	return (NULL);
}

t_elips		*copy_elips(t_elips *obj)
{
	t_elips *newl;

	if (obj)
	{
		if (!(newl = (t_elips *)malloc(sizeof(t_elips))))
			ft_putendl_fd("error : can't malloc copy thread light\n", 1);
		newl->center = obj->center;
		newl->color = obj->color;
		newl->normal = obj->normal;
		newl->radius = obj->radius;
		newl->kdistance = obj->kdistance;
		newl->sol = obj->sol;
		newl->next = NULL;
		if (newl && obj->next)
			newl->next = copy_elips(obj->next);
		return (newl);
	}
	return (NULL);
}
