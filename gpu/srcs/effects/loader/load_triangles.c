/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_triangles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:55:14 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 16:57:09 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void							init_triangle_add(t_triangle *t)
{
	t->id = 0;
	t->pos = new_vector(0, 1.2, -2);
	t->v1 = new_vector(-0.3, 1.5, -2);
	t->v2 = new_vector(0.3, 1.5, -2);
	t->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	t->chess = (t_color){-1, -1, -1};
	t->reflection_coef = 0;
	t->refraction_coef = 0;
	t->transparence_coef = 0;
	t->perlin.is_set = 0;
	t->perlin.pre_set = 0;
	t->perlin.scale = 0;
	t->perlin.amount = 0;
	t->next = NULL;
}

static unsigned int				count_triangle(t_triangle *triangle)
{
	t_triangle		*t;
	unsigned int	size;

	size = 0;
	t = triangle;
	while (t)
	{
		size++;
		t = t->next;
	}
	return (size);
}

void							load_triangles(t_triangle **triangles,
					t_triangle *triangles_tmp, int *triangles_len)
{
	unsigned int	i;
	t_triangle		*tmp;

	if (*triangles != NULL)
	{
		free(*triangles);
		*triangles = NULL;
		*triangles_len = 0;
	}
	i = 0;
	if ((*triangles_len = count_triangle(triangles_tmp)) == 0)
		return ;
	if (!(*triangles = (t_triangle *)malloc(sizeof(t_triangle) *
					*triangles_len)))
		show_error("Don't Malloc\n");
	tmp = triangles_tmp;
	while (tmp)
	{
		(*triangles)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
