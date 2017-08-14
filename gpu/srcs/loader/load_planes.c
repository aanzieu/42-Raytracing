/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:59:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:07:22 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static unsigned int		count_planes(t_plane *planes)
{
	t_plane			*p;
	unsigned int	size;

	size = 0;
	p = planes;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void					load_planes(t_plane **planes, t_plane *planes_tmp,
															int *planes_len)
{
	unsigned int	i;

	i = 0;
	*planes_len = count_planes(planes_tmp);
	*planes = (t_plane*)malloc(sizeof(t_plane) * (*planes_len));
	while (planes_tmp)
	{
		(*planes)[i] = *planes_tmp;
		planes_tmp = planes_tmp->next;
		i++;
	}
}
