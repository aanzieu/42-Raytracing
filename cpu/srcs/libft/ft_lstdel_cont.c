/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:18:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/04/27 08:22:29 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelcont(t_list **alst, void *cont)
{
	t_list	*prev;
	t_list	*current;

	if (!alst || !*alst)
		return ;
	prev = *alst;
	if (prev->content == cont)
	{
		*alst = prev->next;
		return ;
	}
	current = prev->next;
	while (current)
	{
		if (current->content == cont)
		{
			prev->next = current->next;
			free(current);
			free(cont);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
