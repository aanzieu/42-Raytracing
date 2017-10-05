/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:10:12 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/20 14:51:44 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void				init_light_add(t_light *l)
{
	l->id = 0;
	l->pos = new_vector(0, 0, 0);
	l->color = (t_color)
	{color_to_coef(255), color_to_coef(255), color_to_coef(255)};
	l->intensity_coef = 0.1;
	l->next = NULL;
}

static unsigned int	count_lights(t_light *lights)
{
	t_light			*p;
	unsigned int	size;

	size = 0;
	p = lights;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void				load_lights(t_light **lights, t_light *lights_tmp,
															int *lights_len)
{
	unsigned int	i;
	t_light			*tmp;

	if (*lights != NULL)
	{
		free(*lights);
		*lights = NULL;
		*lights_len = 0;
	}
	i = 0;
	if ((*lights_len = count_lights(lights_tmp)) == 0)
		return ;
	if (!(*lights = (t_light*)malloc(sizeof(t_light) * *lights_len)))
		show_error("Don't Malloc\n");
	tmp = lights_tmp;
	while (tmp)
	{
		(*lights)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
