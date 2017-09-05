/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 07:49:07 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/21 14:28:09 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

t_object		*closest_object(t_object *i, t_object *i2)
{
	if (i2 == NULL)
		return (i);
	else if (i == NULL)
		return (i2);
	else if ((i2->tclose < i->tclose || i->tclose == -1)
			&& i2->tclose > MIN)
	{
		free(i);
		return (i2);
	}
	free(i2);
	return (i);
}

t_object		*find_intersection(t_ray r, t_scene *e)
{
	t_object	*objet;

	objet = new_object();
	objet = closest_object(objet, find_cylindres_intersection(r, e));
	objet = closest_object(objet, find_paraboloids_intersection(r, e));
	objet = closest_object(objet, find_elipsoids_intersection(r, e));
	objet = closest_object(objet, find_plans_intersection(r, e));
	objet = closest_object(objet, find_spheres_intersection(r, e));
	objet = closest_object(objet, find_cones_intersection(r, e));
	return (objet);
}

t_color			get_color_object(t_ray r, t_scene *s)
{
	t_object	*i;
	t_color		colorfinal;

	colorfinal = new_color(0, 0, 0, 0);
	i = find_intersection(r, s);
	if (i->tclose > MIN)
		colorfinal = color_def(get_light_at(i, s));
	free(i);
	return (colorfinal);
}
