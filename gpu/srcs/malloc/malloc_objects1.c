/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_objects1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:54:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/20 12:08:17 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

t_light		*new_light(t_light *nw, int id)
{
	t_light	*l;

	if (!(l = (t_light *)ft_memalloc(sizeof(t_light))))
		ft_putendl_fd("Erroc Malloc on Light", 1);
	l->id = id;
	l->pos = nw->pos;
	l->dir = nw->dir;
	l->dir_v = vector_normalize(vector_calculate(nw->dir, nw->pos));
	l->color = nw->color;
	l->type = nw->type;
	l->intensity_coef = nw->intensity_coef;
	l->next = NULL;
	return (l);
}
