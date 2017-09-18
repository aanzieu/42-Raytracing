/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_paraboloids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 11:16:27 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 16:50:36 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void							init_paraboloid_add(t_paraboloid *p)
{
	p->id = 0;
	p->top = new_vector(0, 0, 0);
	p->normal = new_vector(0, -1, 0);
	p->distance = 0.05;
	p->maxm = 0.05;
	p->color = (t_color)
	{color_to_coef(6), color_to_coef(205), color_to_coef(62)};
	p->chess = (t_color){-1, -1, -1};
	p->reflection_coef = 0;
	p->refraction_coef = 0;
	p->transparence_coef = 0;
	p->next = NULL;
}

static unsigned int				count_paraboloids(t_paraboloid *paraboloids)
{
	t_paraboloid	*p;
	unsigned int	size;

	size = 0;
	p = paraboloids;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void							load_paraboloids(t_paraboloid **paraboloids,
						t_paraboloid *paraboloids_tmp, int *paraboloids_len)
{
	unsigned int	i;
	t_paraboloid	*tmp;

	if (*paraboloids != NULL)
	{
		free(*paraboloids);
		*paraboloids = NULL;
		*paraboloids_len = 0;
	}
	i = 0;
	if ((*paraboloids_len = count_paraboloids(paraboloids_tmp)) == 0)
		return ;
	if (!(*paraboloids = (t_paraboloid*)malloc(sizeof(t_paraboloid) *
					*paraboloids_len)))
		show_error("Don't Malloc\n");
	tmp = paraboloids_tmp;
	while (tmp)
	{
		(*paraboloids)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
