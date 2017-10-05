/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 11:05:44 by svilau            #+#    #+#             */
/*   Updated: 2017/10/03 12:28:27 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		memory_allocation_error(void)
{
	ft_putendl("Not enough memory, quiting...");
	exit(0);
}

void		free_world(t_world *world)
{
	free(world);
}
