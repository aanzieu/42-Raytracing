/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_object_thread2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:01:33 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:01:47 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/parse.h"

void		thread_free_and_add_torus(t_torus **to,
		t_torus **to_tmp, int *len, int id)
{
	t_torus	*new;

	if (*to != NULL)
	{
		free(*to);
		*len = 0;
		*to = NULL;
	}
	if (!(new = (t_torus*)ft_memalloc(sizeof(t_torus))))
		show_error("error malloc torus");
	init_torus_add(new);
	*len = 0;
	*to = NULL;
	add_torus(to_tmp, new_torus(new, id));
	free(new);
	load_torus(to, *to_tmp, len);
}

void		thread_free_and_add_mobius(t_mobius **mo,
		t_mobius **mo_tmp, int *len, int id)
{
	t_mobius	*new;

	if (*mo != NULL)
	{
		free(*mo);
		*len = 0;
		*mo = NULL;
	}
	if (!(new = (t_mobius*)ft_memalloc(sizeof(t_mobius))))
		show_error("error malloc mobius");
	init_mobius_add(new);
	*len = 0;
	*mo = NULL;
	add_mobius(mo_tmp, new_mobius(new, id));
	free(new);
	load_mobius(mo, *mo_tmp, len);
}

void		thread_free_and_add_disk(t_disk **di,
		t_disk **di_tmp, int *len, int id)
{
	t_disk	*new;

	if (*di != NULL)
	{
		free(*di);
		*len = 0;
		*di = NULL;
	}
	if (!(new = (t_disk*)ft_memalloc(sizeof(t_disk))))
		show_error("error malloc disk");
	init_disk_add(new);
	*len = 0;
	*di = NULL;
	add_disk(di_tmp, new_disk(new, id));
	free(new);
	load_disks(di, *di_tmp, len);
}

void		thread_free_and_add_cube(t_cube **cu,
		t_cube **cu_tmp, int *len, int id)
{
	t_cube	*new;

	if (*cu != NULL)
	{
		free(*cu);
		*len = 0;
		*cu = NULL;
	}
	if (!(new = (t_cube*)ft_memalloc(sizeof(t_cube))))
		show_error("error malloc sphere");
	init_cube_add(new);
	*len = 0;
	*cu = NULL;
	add_cube(cu_tmp, new_cube(new, id));
	free(new);
	load_cubes(cu, *cu_tmp, len);
}

void		thread_free_and_add_hyperboloid(t_hyperboloid **hy,
		t_hyperboloid **hy_tmp, int *len, int id)
{
	t_hyperboloid	*new;

	if (*hy != NULL)
	{
		free(*hy);
		*len = 0;
		*hy = NULL;
	}
	if (!(new = (t_hyperboloid*)ft_memalloc(sizeof(t_hyperboloid))))
		show_error("error malloc sphere");
	init_hyperboloid_add(new);
	*len = 0;
	*hy = NULL;
	add_hyperboloid(hy_tmp, new_hyperboloid(new, id));
	free(new);
	load_hyperboloids(hy, *hy_tmp, len);
}
