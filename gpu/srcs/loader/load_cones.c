/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:08:45 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 10:49:40 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static unsigned int	count_cones(t_cone *cones)
{
	t_cone *p;
	unsigned int size;

	size = 0;
	p = cones;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void			load_cones(t_cone **cones, t_cone *cones_tmp, int *cones_len)
{
	unsigned int i;
	t_cone *tmp;

	i = 0;
	*cones_len = count_cones(cones_tmp);
	*cones = (t_cone*)malloc(sizeof(t_cone) * *cones_len);
	tmp = cones_tmp;
	while (tmp)
	{
		(*cones)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
