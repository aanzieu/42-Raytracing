/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_framebuffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:54:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 13:22:02 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void    realloc_framebuffer(t_world *world)
{
    if (world->size_main != 0)
	    free(world->a_h);
    world->size_main = world->viewplane.x_res * world->viewplane.y_res
        * sizeof(int);
    if (!(world->a_h = malloc(world->size_main)))
        exit(0);
    ft_bzero(world->a_h, world->size_main);
}