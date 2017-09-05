/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:58:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 19:00:25 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static t_vec3d	normalize_cy(t_cy *cy, t_3point p, t_ray r, double t)
{
	t_vec3d	n;
	t_vec3d	x;
	t_vec3d	v;
	double	m;

	x = point_to_vector(cy->center, r.org);
	v = vector_normalize(cy->normal);
	m = vector_dotproduct(r.dir, vector_scalaire(v, t))
		+ vector_dotproduct(x, v);
	n = vector_normalize(vector_sub(point_to_vector(cy->center, p),
				vector_scalaire(v, m)));
	return (n);
}

static double	find_cylindre_intersection(t_cy *cy, t_ray r)
{
	t_eq	e;
	t_vec3d	x;
	t_vec3d	v;

	x = point_to_vector(cy->center, r.org);
	v = vector_normalize(cy->normal);
	e.a = vector_dotproduct(r.dir, r.dir)
		- (pow(vector_dotproduct(r.dir, v), 2));
	e.b = 2 * (vector_dotproduct(r.dir, x)
			- (vector_dotproduct(r.dir, v) * vector_dotproduct(x, v)));
	e.c = vector_dotproduct(x, x) - (pow(vector_dotproduct(x, v), 2))
		- (cy->angle * cy->angle);
	return (positive_solution(equation_second_degres(e)));
}

static	void	pixel_tclose_from_view(t_cy *cy, t_object *obj,
		t_ray ray, double t)
{
	obj->cy = cy;
	obj->tclose = t;
	obj->normal = normalize_cy(cy, vector_to_point(vector_scalaire(ray.dir, t),
				ray.org), ray, t);
	obj->point = point_from_ray(ray, obj->tclose);
	obj->specular = get_ref_ray(obj->normal, obj->point);
	obj->color = cy->color;
	obj->type = CYLINDRE;
}

t_object		*find_cylindres_intersection(t_ray ray, t_scene *scene)
{
	t_object	*obj;
	t_cy		*cy;
	double		t;

	cy = scene->cy;
	obj = new_object();
	while (cy != NULL)
	{
		t = find_cylindre_intersection(cy, ray);
		if (t > MIN && (t < obj->tclose || obj->tclose == -1))
			pixel_tclose_from_view(cy, obj, ray, t);
		cy = cy->next;
	}
	return (obj);
}
