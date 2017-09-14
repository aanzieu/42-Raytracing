/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cylinders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:07:37 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:11:50 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void	init_cylinder_add(t_cylinder *cy)
{
	cy->id = 0;
	cy->radius = 0.5;
	cy->pos = new_vector(0, -1 , 0);
	cy->up = new_vector(0, 1 , 0);
	cy->up_v = new_vector(0, 4 , 0);
	cy->chess = (t_color){-1, -1, -1};
	cy->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	cy->height = 0;
	cy->reflection_coef = 0;
	cy->refraction_coef = 0;
	cy->transparence_coef = 0;
	cy->next = NULL;
}

static unsigned int		count_cylinders(t_cylinder *cylinders)
{
	t_cylinder		*p;
	unsigned int	size;

	size = 0;
	p = cylinders;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void					load_cylinders(t_cylinder **cylinders,
								t_cylinder *cylinders_tmp, int *cylinders_len)
{
	unsigned int	i;
	t_cylinder		*tmp;

	if (*cylinders != NULL)
	{
		free(*cylinders);
		*cylinders = NULL;
		*cylinders_len = 0;
	}
	i = 0;
	if((*cylinders_len = count_cylinders(cylinders_tmp)) == 0)
		return;
	if(!(*cylinders = (t_cylinder*)malloc(sizeof(t_cylinder) * *cylinders_len)))
			show_error("Don't Malloc\n");
	tmp = cylinders_tmp;
	while (tmp)
	{
		(*cylinders)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
