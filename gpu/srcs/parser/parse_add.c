/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:52:43 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/06 16:12:19 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>
#include <light.h>

void	add_cylinder(t_cylinder **alst, t_cylinder *nw)
{
	t_cylinder *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = nw;
	}
}


void	add_disk(t_disk **alst, t_disk *nw)
{
	t_disk *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = nw;
	}
}

void	add_cone(t_cone **alst, t_cone *nw)
{
	t_cone *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = nw;
	}
}
