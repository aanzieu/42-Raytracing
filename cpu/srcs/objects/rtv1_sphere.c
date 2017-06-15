/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 08:08:31 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 17:43:25 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static	t_vec3d		normalize_sphere(t_sphere *s, t_3point p)
{
	return (vector_normalize(point_to_vector(s->pos, p)));
}

static	void		pixel_tclose_from_view(t_sphere *s, t_object *obj,
		t_ray ray, double t)
{
	obj->sphere = s;
	obj->tclose = t;
	obj->normal = normalize_sphere(s,
			vector_to_point(vector_scalaire(ray.dir, t), ray.org));
	obj->point = point_from_ray(ray, obj->tclose);
	obj->specular = get_ref_ray(obj->normal, obj->point);
	obj->color = s->color;
	obj->type = SPHERE;
	obj->data = s->data;
}

static double		find_sphere_intersection(t_sphere *s, t_ray r)
{
	double	a;
	double	b;
	double	c;
	t_vec3d x;

	x = point_to_vector(s->pos, r.org);
	a = vector_dotproduct(r.dir, r.dir);
	b = 2 * vector_dotproduct(r.dir, x);
	c = vector_dotproduct(x, x) - pow(s->radius, 2);
	return (positive_solution(second_degres(a, b, c)));
}

t_object			*find_spheres_intersection(t_ray ray, t_scene *scene)
{
	t_object	*obj;
	t_sphere	*s;
	double		t;

	s = scene->s;
	obj = new_object();
	while (s)
	{
		t = find_sphere_intersection(s, ray);
		if (t > MIN && (t < obj->tclose || obj->tclose == -1))
			pixel_tclose_from_view(s, obj, ray, t);
		s = s->next;
	}
	return (obj);
}
