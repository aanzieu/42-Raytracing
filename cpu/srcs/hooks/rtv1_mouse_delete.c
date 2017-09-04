/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_mouse_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 08:58:37 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 16:38:53 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void			remove_plan(t_plan **s, t_plan *i)
{
	t_plan	*current;
	t_plan	*last;
	t_plan	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current == i)
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

void			remove_cyl(t_cy **s, t_cy *i)
{
	t_cy	*current;
	t_cy	*last;
	t_cy	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current == i)
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

void			remove_cone(t_cone **s, t_cone *i)
{
	t_cone	*current;
	t_cone	*last;
	t_cone	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current == i)
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

void			remove_sphere(t_sphere **s, t_sphere *i)
{
	t_sphere	*current;
	t_sphere	*last;
	t_sphere	*tmp;

	current = *s;
	tmp = NULL;
	last = NULL;
	while (current)
	{
		if (current == i)
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
