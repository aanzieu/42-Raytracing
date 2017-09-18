/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_free_thread_next.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:29:22 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:00:35 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/parse.h"

void		thread_free_and_add_plane(t_plane **p,
		t_plane **p_tmp, int *len, int id)
{
	t_plane	*new;

	if (*p != NULL)
	{
		free(*p);
		*len = 0;
		*p = NULL;
	}
	if (!(new = (t_plane*)ft_memalloc(sizeof(t_plane))))
		show_error("Error to Malloc Plane");
	init_plane_add(new);
	*len = 0;
	*p = NULL;
	add_plan(p_tmp, new_plan(new, id));
	free(new);
	load_planes(p, *p_tmp, len);
}

void		thread_free_and_add_sphere(t_sphere **s,
		t_sphere **s_tmp, int *len, int id)
{
	t_sphere	*new;

	if (*s != NULL)
	{
		free(*s);
		*len = 0;
		*s = NULL;
	}
	if (!(new = (t_sphere*)ft_memalloc(sizeof(t_sphere))))
		show_error("error malloc sphere");
	init_sphere_add(new);
	*len = 0;
	*s = NULL;
	add_sphere(s_tmp, new_sphere(new, id));
	free(new);
	load_spheres(s, *s_tmp, len);
}

void		thread_free_and_add_cone(t_cone **c,
		t_cone **c_tmp, int *len, int id)
{
	t_cone	*new;

	if (*c != NULL)
	{
		free(*c);
		*len = 0;
		*c = NULL;
	}
	if (!(new = (t_cone*)ft_memalloc(sizeof(t_cone))))
		show_error("Error Malloc Cone");
	init_cone_add(new);
	*len = 0;
	*c = NULL;
	add_cone(c_tmp, new_cone(new, id));
	free(new);
	load_cones(c, *c_tmp, len);
}

void		thread_free_and_add_cylinder(t_cylinder **cy,
		t_cylinder **cy_tmp, int *len, int id)
{
	t_cylinder	*new;

	if (*cy != NULL)
	{
		free(*cy);
		*len = 0;
		*cy = NULL;
	}
	if (!(new = (t_cylinder*)ft_memalloc(sizeof(t_cylinder))))
		show_error("error malloc cylinder");
	init_cylinder_add(new);
	*len = 0;
	*cy = NULL;
	add_cylinder(cy_tmp, new_cylinder(new, id));
	free(new);
	load_cylinders(cy, *cy_tmp, len);
}
