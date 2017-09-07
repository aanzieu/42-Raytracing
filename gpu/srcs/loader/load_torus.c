/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_torus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:06:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/26 17:50:35 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void	init_torus_add(t_torus *t)
{
	t->id = 0;
	t->radius_small = 0.5;
	t->radius_big = 1;
	t->pos = new_vector(0, 0 , 1);
	t->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	t->chess = (t_color){-1, -1, -1};
	t->reflection_coef = 0;
	t->refraction_coef = 0;
	t->transparence_coef = 0;
	t->next = NULL;
}

static unsigned int			count_torus(t_torus *torus)
{
	t_torus			*t;
	unsigned int	size;

	size = 0;
	t = torus;
	while (t)
	{
		size++;
		t = t->next;
	}
	return (size);
}

void						load_torus(t_torus **torus,
										t_torus *torus_tmp, int *torus_len)
{
	unsigned int	i;
	t_torus			*tmp;

	i = 0;
	*torus_len = count_torus(torus_tmp);
	*torus = (t_torus*)malloc(sizeof(t_torus) * *torus_len);
	tmp = torus_tmp;
	while (tmp)
	{
		(*torus)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
