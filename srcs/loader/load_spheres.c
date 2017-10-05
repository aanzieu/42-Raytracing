/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:06:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/04 15:01:12 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void						init_sphere_add(t_sphere *s)
{
	s->id = 0;
	s->radius = 0.2;
	s->pos = new_vector(0, 0, -0.5);
	s->color = (t_color)
	{color_to_coef(36), color_to_coef(205), color_to_coef(62)};
	s->chess = (t_color){-1, -1, -1};
	s->reflection_coef = 0;
	s->refraction_coef = 0;
	s->transparence_coef = 0;
	s->perlin.is_set = 0;
	s->perlin.pre_set = 0;
	s->perlin.scale = 0;
	s->perlin.amount = 0;
	s->next = NULL;
}

static unsigned int			count_spheres(t_sphere *spheres)
{
	t_sphere		*s;
	unsigned int	size;

	size = 0;
	s = spheres;
	while (s)
	{
		size++;
		s = s->next;
	}
	return (size);
}

void						load_spheres(t_sphere **spheres,
							t_sphere *spheres_tmp, int *spheres_len)
{
	unsigned int	i;
	t_sphere		*tmp;

	if (*spheres_len != 0)
	{
		free(*spheres);
		*spheres = NULL;
		*spheres_len = 0;
	}
	i = 0;
	if ((*spheres_len = count_spheres(spheres_tmp)) == 0)
		return ;
	if (!(*spheres = (t_sphere*)malloc(sizeof(t_sphere) * *spheres_len)))
		show_error("Don't Malloc\n");
	tmp = spheres_tmp;
	while (tmp)
	{
		(*spheres)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
