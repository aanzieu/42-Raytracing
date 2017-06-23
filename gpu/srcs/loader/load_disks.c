/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_disks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:59:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:07:22 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static unsigned int		count_disks(t_disk *disks)
{
	t_disk *p;
	unsigned int size;

	size = 0;
	p = disks;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void			load_disks(t_disk **disks, t_disk *disks_tmp, int *disks_len)
{
	unsigned int i;

	i = 0;
	*disks_len = count_disks(disks_tmp);
	*disks = (t_disk*)malloc(sizeof(t_disk) * (*disks_len));
	while (disks_tmp)
	{
		(*disks)[i] = *disks_tmp;
		disks_tmp = disks_tmp->next;
		i++;
	}
}
