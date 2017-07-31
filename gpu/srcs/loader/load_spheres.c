/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_spheres.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:06:29 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:08:23 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static unsigned int			count_spheres(t_sphere *spheres)
{
	t_sphere *s;
	unsigned int size;

	size = 0;
	s = spheres;
	while (s)
	{
		size++;
		s = s->next;
	}
	return (size);
}

void			load_spheres(t_sphere **spheres, t_sphere *spheres_tmp, int *spheres_len)
{
	unsigned int i;
	t_sphere *tmp;

	i = 0;
	*spheres_len = count_spheres(spheres_tmp);
	*spheres = (t_sphere*)malloc(sizeof(t_sphere) * *spheres_len);
	tmp = spheres_tmp;
	while (tmp)
	{
		(*spheres)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}
