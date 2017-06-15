/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:17:53 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/15 09:05:25 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void	ft_mlx_del(t_env *e)
{
	if (e->win != NULL)
		mlx_destroy_window(e->mlx, e->win);
	if (e->image != NULL)
		del_image(e, e->image);
}

void	mlx_del(t_env *e)
{
	ft_bzero(e->image->img_s, WH * WW * e->image->bpp);
	expose_hook(e);
}
