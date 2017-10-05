/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:34:35 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/12 14:39:24 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/rt.h"

void	free_disk(t_disk **d_tmp, t_disk **d, int *len)
{
	t_disk	*next;

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

void	free_para(t_paraboloid **p_tmp, t_paraboloid **p, int *len)
{
	t_paraboloid	*next;

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

void	free_hyper(t_hyperboloid **c_tmp, t_hyperboloid **c, int *len)
{
	t_hyperboloid	*next;

	while (*c_tmp)
	{
		next = (*c_tmp)->next;
		free(*c_tmp);
		(*c_tmp) = next;
	}
	if (*c != NULL)
	{
		free(*c);
		*len = 0;
		*c = NULL;
	}
	*c = 0;
	*c = NULL;
}

void	free_torus(t_torus **c_tmp, t_torus **c, int *len)
{
	t_torus	*next;

	while (*c_tmp)
	{
		next = (*c_tmp)->next;
		free(*c_tmp);
		(*c_tmp) = next;
	}
	if (*c != NULL)
	{
		free(*c);
		*len = 0;
		*c = NULL;
	}
	*c = 0;
	*c = NULL;
}

void	free_mobius(t_mobius **l_tmp, t_mobius **l, int *len)
{
	t_mobius	*next;

	while (*l_tmp)
	{
		next = (*l_tmp)->next;
		free(*l_tmp);
		(*l_tmp) = next;
	}
	if (*l != NULL)
	{
		free(*l);
		*len = 0;
		*l = NULL;
	}
	*len = 0;
	*l = NULL;
}
