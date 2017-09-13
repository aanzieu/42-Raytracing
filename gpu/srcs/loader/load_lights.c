/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_lights.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:10:12 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:11:48 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
	printf("LIght len SIZE = %d\n", size);
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
	if((*lights_len = count_lights(lights_tmp)) == 0)
	{
		printf("PAS DE LIGHTS\n");
		return;
	}
	*lights = (t_light*)malloc(sizeof(t_light) * *lights_len);
	tmp = lights_tmp;
	while (tmp)
	{
		(*lights)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
