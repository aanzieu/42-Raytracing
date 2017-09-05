/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 09:11:05 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 09:10:01 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_ray		new_ray(t_3point org, t_vec3d dir)
{
	t_ray	r;

	r.org = org;
	r.dir = dir;
	return (r);
}

t_color		new_color(double r, double g, double b, double light)
{
	t_color	new;

	new.r = r;
	new.g = g;
	new.b = b;
	new.light = light;
	return (new);
}

t_object	*new_object(void)
{
	t_object	*i;

	if (!(i = (t_object *)ft_memalloc(sizeof(t_object))))
		ft_putendl_fd("Error Malloc on Intersection point", 1);
	i->tclose = -1;
	return (i);
}
