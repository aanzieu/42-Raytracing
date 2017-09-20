/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_objects3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:52:59 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/12 15:25:47 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

void			remove_triangle(t_triangle **s, t_intersection *i)
{
	t_triangle	*current;
	t_triangle	*last;
	t_triangle	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current->id == i->id_save)
		{
			if (current == *s)
				*s = current->next;
			else
				last->next = current->next;
			tmp = current;
			current = current->next;
			free(tmp);
		}
		else
		{
			last = current;
			current = current->next;
		}
	}
}

void			remove_h_cube(t_h_cube **s, t_intersection *i)
{
	t_h_cube	*current;
	t_h_cube	*last;
	t_h_cube	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current->id == i->id_save)
		{
			if (current == *s)
				*s = current->next;
			else
				last->next = current->next;
			tmp = current;
			current = current->next;
			free(tmp);
		}
		else
		{
			last = current;
			current = current->next;
		}
	}
}
