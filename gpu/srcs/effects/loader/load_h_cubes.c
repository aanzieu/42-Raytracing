/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_h_cubes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:58:09 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/03 15:11:31 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void						init_h_cube_add(t_h_cube *c)
{
	c->id = 0;
	c->pos = new_vector(0, 0, 0);
	c->color = (t_color)
	{color_to_coef(125), color_to_coef(225), color_to_coef(125)};
	c->chess = (t_color){-1, -1, -1};
	c->reflection_coef = 0;
	c->refraction_coef = 0;
	c->transparence_coef = 0;
	c->perlin.is_set = 0;
	c->perlin.pre_set = 0;
	c->perlin.scale = 0;
	c->perlin.amount = 0;
	c->next = NULL;
}

static unsigned int			count_h_cubes(t_h_cube *h_cubes)
{
	t_h_cube		*s;
	unsigned int	size;

	size = 0;
	s = h_cubes;
	while (s)
	{
		size++;
		s = s->next;
	}
	return (size);
}

void						load_h_cubes(t_h_cube **h_cubes,
									t_h_cube *h_cubes_tmp, int *h_cubes_len)
{
	unsigned int	i;
	t_h_cube		*tmp;

	if (*h_cubes_len != 0)
	{
		free(*h_cubes);
		*h_cubes = NULL;
		*h_cubes_len = 0;
	}
	i = 0;
	if ((*h_cubes_len = count_h_cubes(h_cubes_tmp)) == 0)
		return ;
	if (!(*h_cubes = (t_h_cube*)malloc(sizeof(t_h_cube) * *h_cubes_len)))
		show_error("Don't Malloc\n");
	tmp = h_cubes_tmp;
	while (tmp)
	{
		(*h_cubes)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
