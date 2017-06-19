/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_paraboloids.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 11:16:27 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 14:17:49 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static unsigned int	count_paraboloids(t_paraboloid *paraboloids)
{
	t_paraboloid *p;
	unsigned int size;

	size = 0;
	p = paraboloids;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void			load_paraboloids(t_paraboloid **paraboloids, t_paraboloid *paraboloids_tmp, int *paraboloids_len)
{
	unsigned int i;
	t_paraboloid *tmp;

	i = 0;
	*paraboloids_len = count_paraboloids(paraboloids_tmp);
	*paraboloids = (t_paraboloid*)malloc(sizeof(t_paraboloid) * *paraboloids_len);
	tmp = paraboloids_tmp;
	while (tmp)
	{
		(*paraboloids)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}

