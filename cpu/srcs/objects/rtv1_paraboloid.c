/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_paraboloid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 14:01:50 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 18:23:19 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void			normalize_para(t_para *para, t_3point p,
		t_ray r, t_object *obj)
{
	t_vec3d	x;
	t_vec3d	v;
	double	m;

	x = point_to_vector(para->top, r.org);
	v = vector_normalize(para->normal);
	m = vector_dotproduct(r.dir, vector_scalaire(v, obj->tclose))
		+ vector_dotproduct(x, v);
	obj->normal = vector_normalize(vector_sub(point_to_vector(para->top, p),
				vector_scalaire(v, m + para->distance)));
}

static int			normalize_para_withmax(t_para *para, t_3point p,
		t_ray r, t_object *obj)
{
	t_vec3d	x;
	t_vec3d	v;
	double	m;

	x = point_to_vector(para->top, r.org);
	v = vector_normalize(para->normal);
	if ((m = vector_dotproduct(r.dir, vector_scalaire(v, obj->tclose)) +
				vector_dotproduct(x, v)) <= para->maxm)
	{
		obj->normal = vector_normalize(vector_sub(point_to_vector(para->top, p),
					vector_scalaire(v, m + para->distance)));
		return (0);
	}
	return (1);
}

static double		find_paraboloid_intersection(t_para *para, t_ray r)
{
	t_eq	e;
	t_vec3d	x;
	t_vec3d	v;

	x = point_to_vector(para->top, r.org);
	v = vector_normalize(para->normal);
	e.a = vector_dotproduct(r.dir, r.dir)
		- (pow(vector_dotproduct(r.dir, v), 2));
	e.b = 2 * (vector_dotproduct(r.dir, x)
			- (vector_dotproduct(r.dir, v)
				* ((vector_dotproduct(x, v) + 2 * para->distance))));
	e.c = vector_dotproduct(x, x)
		- (vector_dotproduct(x, v)
				* (vector_dotproduct(x, v) + 4 * para->distance));
	return (positive_solution(equation_second_degres(e)));
}

static	t_object	*pixel_tclose_from_view(t_para *para,
		t_object *obj, t_ray ray, double t)
{
	obj->tclose = t;
	if (para->maxm > 0)
	{
		if ((normalize_para_withmax(para,
						vector_to_point(vector_scalaire(ray.dir, t), ray.org),
						ray, obj) == 0))
		{
			obj->point = point_from_ray(ray, obj->tclose);
			obj->specular = get_ref_ray(obj->normal, obj->point);
			obj->color = para->color;
		}
		else
			obj->tclose = -1;
	}
	else
	{
		normalize_para(para, vector_to_point(vector_scalaire(ray.dir, t),
					ray.org), ray, obj);
		obj->point = point_from_ray(ray, obj->tclose);
		obj->specular = get_ref_ray(obj->normal, obj->point);
		obj->color = para->color;
	}
	return (obj);
}

t_object			*find_paraboloids_intersection(t_ray ray, t_scene *scene)
{
	t_object	*obj;
	t_para		*para;
	double		t;

	para = scene->para;
	obj = new_object();
	while (para != NULL)
	{
		t = find_paraboloid_intersection(para, ray);
		if (t > MIN && (t < obj->tclose || obj->tclose == -1))
			obj = pixel_tclose_from_view(para, obj, ray, t);
		para = para->next;
	}
	return (obj);
}
