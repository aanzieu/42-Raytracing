/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 12:31:07 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/21 13:13:53 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static t_vec3d		normalize_cone(t_cone *co, t_ray r, double t, t_3point p)
{
	double	k;
	double	m;
	t_vec3d v;
	t_vec3d	x;
	t_vec3d n;

	x = point_to_vector(co->center, r.org);
	v = vector_normalize(co->normal);
	
	m = vector_dotproduct(r.dir, vector_scalaire(v, t))
		+ vector_dotproduct(x, v);

	
	
	k = co->angle;
	n = vector_normalize(vector_sub(point_to_vector(co->center, p),
				vector_scalaire(vector_scalaire(v, m), (1 + k * k))));
	return (n);
}

static	void		pixel_tclose_from_view(t_cone *cone, t_object *obj,
		t_ray ray, double t)
{
	obj->cone = cone;
	obj->tclose = t;
	obj->normal = normalize_cone(cone, ray, t,
			vector_to_point(vector_scalaire(ray.dir, t), ray.org));
	obj->point = point_from_ray(ray, obj->tclose);
	obj->specular = get_ref_ray(obj->normal, obj->point);
	obj->color = cone->color;
	obj->type = CONE;
}

static double		find_cone_intersection(t_cone *co, t_ray r)
{
	double	a[3];
	double	k;
	t_vec3d	x;
	t_vec3d	v;

	x = point_to_vector(co->center, r.org);
	v = vector_normalize(co->normal);
	k = co->angle;
	a[0] = vector_dotproduct(r.dir, r.dir) - ((1 + (k * k)) *
			(pow(vector_dotproduct(r.dir, v), 2)));

	a[1] = 2 * ((vector_dotproduct(r.dir, x) - ((1 + (k * k)) *
			vector_dotproduct(r.dir, v) * vector_dotproduct(x, v))));
	
	a[2] = vector_dotproduct(x, x) - ((1 + (k * k)) *
			(pow(vector_dotproduct(x, v), 2)));
	return (positive_solution(second_degres(a[0], a[1], a[2])));
}

t_object			*find_cones_intersection(t_ray ray, t_scene *scene)
{
	t_object	*obj;
	t_cone		*cone;
	double		t;

	cone = scene->co;
	obj = new_object();
	while (cone != NULL)
	{
		t = find_cone_intersection(cone, ray);
		if (t > MIN && (t < obj->tclose || obj->tclose == -1))
			pixel_tclose_from_view(cone, obj, ray, t);
		cone = cone->next;
	}
	return (obj);
}
