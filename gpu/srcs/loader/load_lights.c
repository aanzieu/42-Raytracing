/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:10:12 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 16:46:14 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

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
