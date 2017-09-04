/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_point_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:59:21 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/26 16:49:09 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

inline t_3point		new_3point(double x, double y, double z)
{
	t_3point new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

inline t_3point		cpy_3point(t_3point p)
{
	return (new_3point(p.x, p.y, p.z));
}
