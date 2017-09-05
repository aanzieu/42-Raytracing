/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 17:56:20 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/13 17:20:06 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_ray		point_from_ray(t_ray r, double inter)
{
	t_vec3d		v;
	t_3point	p;

	v = vector_scalaire(r.dir, inter);
	p = vector_to_point(v, r.org);
	return (new_ray(cpy_3point(p), cpy_3dvect(r.dir)));
}

t_vec3d		get_ref_ray(t_vec3d n, t_ray r)
{
	t_vec3d	a;
	t_vec3d	b;
	t_vec3d	c;
	t_vec3d	d;

	a = vector_neg(r.dir);
	a = vector_scalaire(n, vector_dotproduct(a, n));
	c = vector_sum(a, r.dir);
	b = vector_scalaire(c, 2);
	a = vector_neg(r.dir);
	d = vector_sum(a, b);
	a = (d);
	return (cpy_3dvect(a));
}

t_ray		get_raytracing(t_cam *c)
{
	t_vec3d	v1;

	v1 = (vector_sum(c->axe_z,
				vector_sum(vector_scalaire(c->axe_x, c->x - 0.5),
					vector_scalaire(c->axe_y, c->y - 0.5))));
	return (new_ray(c->pos, v1));
}
