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

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void	init_disk_add(t_disk *d)
{
	d->id = 0;
	d->radius = 0.4;
	d->radius_squared = pow(d->radius, 2);
	d->pos = new_vector(0, 0 , 0);
	d->up = new_vector(0, 0 , 1);
	d->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	d->chess = (t_color){-1, -1, -1};
	d->reflection_coef = 0;
	d->refraction_coef = 0;
	d->transparence_coef = 0;
	d->next = NULL;
}

static unsigned int		count_disks(t_disk *disks)
{
	t_disk			*p;
	unsigned int	size;

	size = 0;
	p = disks;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void					load_disks(t_disk **disks, t_disk *disks_tmp,
															int *disks_len)
{
	unsigned int	i;
	t_disk			*tmp;

	if (*disks != NULL)
	{
		free(*disks);
		*disks = NULL;
		*disks_len = 0;
	}
	i = 0;
	if((*disks_len = count_disks(disks_tmp)) == 0)
		return;
	if(!(*disks = (t_disk*)malloc(sizeof(t_disk) * (*disks_len))))
				show_error("Don't Malloc\n");
	tmp = disks_tmp;
	while (tmp)
	{
		(*disks)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}