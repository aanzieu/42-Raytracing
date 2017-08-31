/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 21:29:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

void			remove_sphere(t_sphere **s, t_intersection *i)
{
	t_sphere	*current;
	t_sphere	*last;
	t_sphere	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current->id == i->id)
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

void			remove_cone(t_cone **s, t_intersection *i)
{
	t_cone	*current;
	t_cone	*last;
	t_cone	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current->id == i->id)
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

void			remove_cylinder(t_cylinder **s, t_intersection *i)
{
	t_cylinder	*current;
	t_cylinder	*last;
	t_cylinder	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current->id == i->id)
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

void			remove_plane(t_plane **s, t_intersection *i)
{
	t_plane	*current;
	t_plane	*last;
	t_plane	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current->id == i->id)
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