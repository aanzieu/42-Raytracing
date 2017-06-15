/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 10:55:39 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/14 11:51:16 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_ray		cpy_ray(t_ray r)
{
	return (new_ray(r.org, r.dir));
}

t_color		cpy_color(t_color c)
{
	return (new_color(c.r, c.g, c.b, c.light));
}

void		thread_copy(t_env *e, t_thread_cpy *cpy)
{
	cpy->img_s = e->image->img_s;
	cpy->s_l = e->image->s_l;
	cpy->bpp = e->image->bpp;
	cpy->endian = e->image->endian;
	cpy->scene = ft_copy_scene(e);
//	ft_bzero(&cpy->c, sizeof(int));
}
