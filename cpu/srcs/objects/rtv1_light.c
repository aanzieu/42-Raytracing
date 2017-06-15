/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 13:00:21 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/13 08:53:31 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static int			distance_from_light_shadow(t_object *i,
		t_object *intersection, t_light *l)
{
	double		distance_from_object;
	double		distance_from_light;

	if (intersection->tclose != -1)
	{
		distance_from_object =
			distance_btw_3points(i->point.org, intersection->point.org);
		distance_from_light =
			distance_btw_3points(i->point.org, l->position);
		if (distance_from_object <= distance_from_light)
			return (0);
	}
	return (1);
}

static t_color		light_specular(t_object *i, t_light *l, t_color lambert)
{
	double specular;

	specular = vector_dotproduct(vector_normalize(i->specular),
			vector_normalize(l->light_lenght));
	lambert = color_add(lambert, color_scalar(pow(fmax(0, specular), PRECISION)
				* i->color.light, l->color));
	return (lambert);
}

static t_color		positive_angle(t_object *i, t_scene *s,
		t_color lambert, t_light *l)
{
	l->angle = vector_dotproduct(vector_normalize(i->normal),
			vector_normalize(l->light_lenght));
	if (l->angle > 0.0)
	{
		if (s->light == 1)
			lambert = color_add(lambert,
				color_scalar(l->angle, color_multiply(i->color, l->color)));
		else
			lambert = color_scalar(AMBIENT, i->color);
		if (i->color.light > 0 && i->color.light <= 1.0 && s->brillance == 1)
			lambert = light_specular(i, l, lambert);
	}
	return (lambert);
}

static t_color		spot_light(t_object *i, t_scene *s)
{
	t_ray		shadow;
	t_light		*l;
	t_object	*intersection;
	t_color		lambert;

	l = s->l;
	lambert = color_scalar(AMBIENT, i->color);
	while (l != NULL)
	{
		l->light_lenght = point_to_vector(i->point.org, l->position);
		shadow = new_ray(i->point.org, l->light_lenght);
		intersection = find_intersection(shadow, s);
		if (!(distance_from_light_shadow(i, intersection, l)) && s->shadow == 1)
		{
			lambert = color_scalar(AMBIENT, i->color);
			free(intersection);
			return (lambert);
		}
		else
			lambert = positive_angle(i, s, lambert, l);
		l = l->next;
		free(intersection);
	}
	return (lambert);
}

t_color				get_light_at(t_object *i, t_scene *s)
{
	t_color		c;

	c = new_color(0, 0, 0, 0);
	if (i->tclose > MIN && i->tclose < MAX)
		c = spot_light(i, s);
	return (c);
}
