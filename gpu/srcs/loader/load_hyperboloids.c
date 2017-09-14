/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_hyperboloids.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:59:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:07:22 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void	init_hyperboloid_add(t_hyperboloid *h)
{
	h->id = 0;
	h->radius = 0.05;
	h->maxm = 0.05;
	h->top = new_vector(0, 0 , 1);
	h->normal = new_vector(0, 1 , 1);
	h->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	h->chess = (t_color){-1, -1, -1};
	h->reflection_coef = 0;
	h->refraction_coef = 0;
	h->transparence_coef = 0;
	h->next = NULL;
}

static unsigned int	count_hyperboloids(t_hyperboloid *hyperboloids)
{
	t_hyperboloid	*h;
	unsigned int	size;

	size = 0;
	h = hyperboloids;
	while (h)
	{
		size++;
		h = h->next;
	}
	return (size);
}

void				load_hyperboloids(t_hyperboloid **hyperboloids,
						t_hyperboloid *hyperboloids_tmp, int *hyperboloids_len)
{
	unsigned int	i;
	t_hyperboloid	*tmp;

	if (*hyperboloids!= NULL)
	{
		free(*hyperboloids);
		*hyperboloids = NULL;
		*hyperboloids_len = 0;
	}

	i = 0;
	if((*hyperboloids_len = count_hyperboloids(hyperboloids_tmp)) == 0)
		return;
	if(!(*hyperboloids = (t_hyperboloid*)malloc(sizeof(t_hyperboloid) *	*hyperboloids_len)))
				show_error("Don't Malloc\n");
	tmp = hyperboloids_tmp;
	while (tmp)
	{
		(*hyperboloids)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
