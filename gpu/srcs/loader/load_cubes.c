/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cubes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 16:03:48 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 16:04:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void						init_cube_add(t_cube *c)
{
	c->id = 0;
	c->min = new_vector(0, 0, 0);
	c->max = new_vector(1, 1, 1);
	c->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	c->chess = (t_color){-1, -1, -1};
	c->reflection_coef = 0;
	c->refraction_coef = 0;
	c->transparence_coef = 0;
	c->next = NULL;
}

static unsigned int			count_cube(t_cube *cube)
{
	t_cube			*t;
	unsigned int	size;

	size = 0;
	t = cube;
	while (t)
	{
		size++;
		t = t->next;
	}
	return (size);
}

void						load_cubes(t_cube **cubes,
							t_cube *cubes_tmp, int *cubes_len)
{
	unsigned int	i;
	t_cube			*tmp;

	if (*cubes != NULL)
	{
		free(*cubes);
		*cubes = NULL;
		*cubes_len = 0;
	}
	i = 0;
	if ((*cubes_len = count_cube(cubes_tmp)) == 0)
		return ;
	if (!(*cubes = (t_cube *)malloc(sizeof(t_cube) * *cubes_len)))
		show_error("Don't Malloc\n");
	tmp = cubes_tmp;
	while (tmp)
	{
		(*cubes)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
