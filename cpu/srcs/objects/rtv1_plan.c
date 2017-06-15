/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_plan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 12:55:20 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 17:43:23 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static	double		find_plan_intersection(t_plan *p, t_ray ray)
{
	double		n;
	double		d;
	double		rslt;
	t_vec3d		x;

	x = point_to_vector(p->origin, ray.org);
	n = vector_dotproduct(x, p->normal);
	d = vector_dotproduct(ray.dir, p->normal);
	if ((rslt = -n / d) > 0)
		return (rslt);
	return (-1);
}

static	t_vec3d		normalize_plan(t_plan *p, double v)
{
	t_vec3d n;

	v = v > 0 ? v : -v;
	n = vector_normalize(vector_scalaire(p->normal, v));
	return (n);
}

static	void		pixel_tclose_from_view(t_plan *p, t_object *obj,
		t_ray ray, double t)
{
	obj->plan = p;
	obj->tclose = t;
	obj->normal = normalize_plan(p, vector_dotproduct(ray.dir, p->normal));
	obj->color = p->color;
	obj->point = point_from_ray(ray, obj->tclose);
	obj->specular = get_ref_ray(obj->normal, obj->point);
	obj->type = PLAN;
}

t_object			*find_plans_intersection(t_ray ray, t_scene *scene)
{
	t_object	*obj;
	t_plan		*p;
	double		t;

	obj = new_object();
	p = scene->p;
	while (p != NULL)
	{
		t = find_plan_intersection(p, ray);
		if (t > MIN && (t < obj->tclose || obj->tclose == -1))
			pixel_tclose_from_view(p, obj, ray, t);
		p = p->next;
	}
	return (obj);
}
