/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects_next2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:29:43 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/12 14:32:56 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rt.h"

void	free_cube(t_cube **d_tmp, t_cube **d, int *len)
{
	t_cube	*next;

	while (*d_tmp)
	{
		next = (*d_tmp)->next;
		free(*d_tmp);
		(*d_tmp) = next;
	}
	if (*d != NULL)
	{
		free(*d);
		*len = 0;
		*d = NULL;
	}
	*d = 0;
	*d = NULL;
}

void	free_triangle(t_triangle **p_tmp, t_triangle **p, int *len)
{
	t_triangle	*next;

	while (*p_tmp)
	{
		next = (*p_tmp)->next;
		free(*p_tmp);
		(*p_tmp) = next;
	}
	if (*p != NULL)
	{
		free(*p);
		*len = 0;
		*p = NULL;
	}
	*p = 0;
	*p = NULL;
}
