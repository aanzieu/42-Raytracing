/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_object_thread3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:02:01 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:02:29 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/parse.h"

void		thread_free_and_add_paraboloid(t_paraboloid **p,
		t_paraboloid **p_tmp, int *len, int id)
{
	t_paraboloid	*new;

	if (*p != NULL)
	{
		free(*p);
		*len = 0;
		*p = NULL;
	}
	if (!(new = (t_paraboloid*)ft_memalloc(sizeof(t_paraboloid))))
		show_error("error malloc paraboloid");
	init_paraboloid_add(new);
	*len = 0;
	*p = NULL;
	add_paraboloid(p_tmp, new_paraboloid(new, id));
	free(new);
	load_paraboloids(p, *p_tmp, len);
}

void		thread_free_and_add_triangle(t_triangle **t,
		t_triangle **t_tmp, int *len, int id)
{
	t_triangle	*new;

	if (*t != NULL)
	{
		free(*t);
		*len = 0;
		*t = NULL;
	}
	if (!(new = (t_triangle*)ft_memalloc(sizeof(t_triangle))))
		show_error("error malloc triangle");
	init_triangle_add(new);
	*len = 0;
	*t = NULL;
	add_triangle(t_tmp, new_triangle(new, id));
	free(new);
	load_triangles(t, *t_tmp, len);
}

void		thread_free_and_add_h_cube(t_h_cube **cu, t_h_cube **cu_tmp, int *len, int id)
{
	t_h_cube	*new;

	if(*cu != NULL)
	{
		free(*cu);
		*len = 0;
		*cu = NULL;
	}
	if (!(new = (t_h_cube*)ft_memalloc(sizeof(t_h_cube))))
		show_error("error malloc hollow cube");
	init_h_cube_add(new);
	*len = 0;
	*cu = NULL;
	add_h_cube(cu_tmp, new_h_cube(new, id));
	free(new);
	load_h_cubes(cu, *cu_tmp, len);
}
