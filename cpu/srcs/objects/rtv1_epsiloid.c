/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_epsiloid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:39:45 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 16:56:05 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_elips				*get_epsiloid(t_env *e)
{
	t_elips *boloid;

	(void)e;
	if (!(boloid = (t_elips*)malloc(sizeof(t_elips))))
		ft_putendl_fd("Erroc Malloc on Cone", 1);
	boloid->center = new_3point(4, 0, -1);
	boloid->normal = new_3dvector(0, 1, 0);
	boloid->kdistance = 1;
	boloid->radius = 2;
	boloid->color = new_color(0.4, 0, 0, 1);
	boloid->next = NULL;
	return (boloid);
}

static void			normalize_epsiloid(t_elips *elips, t_3point p,
		t_ray r, t_object *obj)
{
	t_vec3d cmid;
	t_vec3d gr;
	t_vec3d	v;
	t_vec3d	c;

	(void)r;
	c = point_to_vector(elips->center, elips->center);
	v = vector_normalize(elips->normal);
	cmid = vector_sum(c, vector_scalaire(v, elips->kdistance / 2));
	gr = point_vect_sub(p, cmid);
	obj->normal = vector_normalize(vector_sub(gr,
				vector_scalaire(v, (1 - (pow(elips->sol.b, 2)
							/ pow(elips->sol.a, 2)))
					* vector_dotproduct(gr, v))));
}

static	t_object	*pixel_tclose_from_view(t_elips *elips, t_object *obj,
		t_ray ray, double t)
{
	obj->tclose = t;
	normalize_epsiloid(elips, vector_to_point(vector_scalaire(ray.dir, t),
				ray.org), ray, obj);
	obj->point = point_from_ray(ray, obj->tclose);
	obj->specular = get_ref_ray(obj->normal, obj->point);
	obj->color = elips->color;
	return (obj);
}

static double		find_elipsoid_intersection(t_elips *elips, t_ray r)
{
	double	a1;
	double	a2;
	t_vec3d	x;
	t_vec3d	v;

	x = point_to_vector(elips->center, r.org);
	v = vector_normalize(elips->normal);
	a1 = 2 * elips->kdistance * (vector_dotproduct(r.dir, v));
	a2 = pow(elips->radius, 2) +
		(2 * elips->kdistance * (vector_dotproduct(x, v))) - elips->kdistance;
	elips->sol.a = (4 * (pow(elips->radius, 2) *
				(vector_dotproduct(r.dir, r.dir)))) - pow(a1, 2);
	elips->sol.b = 2 * ((4 * (pow(elips->radius, 2)
					* (vector_dotproduct(r.dir, x)))) - (a1 * a2));
	elips->sol.c = (4 * (pow(elips->radius, 2) *
				(vector_dotproduct(x, x)))) - pow(a2, 2);
	return (positive_solution(equation_second_degres(elips->sol)));
}

t_object			*find_elipsoids_intersection(t_ray ray, t_scene *scene)
{
	t_object	*obj;
	t_elips		*elips;
	double		t;

	elips = scene->elips;
	obj = new_object();
	while (elips != NULL)
	{
		t = find_elipsoid_intersection(elips, ray);
		if (t > MIN && (t < obj->tclose || obj->tclose == -1))
			obj = pixel_tclose_from_view(elips, obj, ray, t);
		elips = elips->next;
	}
	return (obj);
}
