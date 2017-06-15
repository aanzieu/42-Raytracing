/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_translation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 13:19:20 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/26 16:58:10 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

void		point_vector_scal(t_3point *p, t_vec3d *v, double coef)
{
	p->x += v->x * coef;
	p->y += v->y * coef;
	p->z += v->z * coef;
}

void		ft_rot_y(t_vec3d *z, double angle)
{
	t_2point	a;

	a.x = z->x;
	a.y = z->z;
	z->x = a.y * sin(angle) + a.x * cos(angle);
	z->z = a.y * cos(angle) - a.x * sin(angle);
}

void		ft_rot_x(t_vec3d *y, double angle)
{
	t_2point	a;

	a.x = y->y;
	a.y = y->z;
	y->y = a.x * cos(angle) - a.y * sin(angle);
	y->z = a.x * sin(angle) + a.y * cos(angle);
}

void		ft_rot_z(t_vec3d *x, double angle)
{
	t_2point	a;

	a.x = x->x;
	a.y = x->y;
	x->x = a.y * sin(angle) + a.x * cos(angle);
	x->y = a.y * cos(angle) - a.x * sin(angle);
}
