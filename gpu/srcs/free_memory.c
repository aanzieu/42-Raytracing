/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 11:05:44 by svilau            #+#    #+#             */
/*   Updated: 2017/06/16 17:42:30 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		memory_allocation_error(void)
{
	ft_putstr("Not enough memory, quiting...\n");
	exit(0);
}

void		free_world(t_world *world)
{
	free(world);
}
