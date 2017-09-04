/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 10:20:44 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/26 10:47:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

inline t_vec3d		new_3dvector(double x, double y, double z)
{
	t_vec3d	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

inline t_vec2d		new_2dvector(double x, double y)
{
	t_vec2d	new;

	new.x = x;
	new.y = y;
	return (new);
}

inline t_vec3d		cpy_3dvect(t_vec3d v)
{
	return (new_3dvector(v.x, v.y, v.z));
}

inline t_vec2d		cpy_2dvect(t_vec2d v)
{
	return (new_2dvector(v.x, v.y));
}
