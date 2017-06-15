/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:34:38 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/14 16:22:23 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

int			one_keypressed(t_keypress *keys)
{
	int		i;
	int		*key;

	i = 0;
	key = (int*)keys;
	while ((size_t)key - (size_t)(keys) < sizeof(*keys))
	{
		if (*key)
			return (1);
		key++;
	}
	return (0);
}
