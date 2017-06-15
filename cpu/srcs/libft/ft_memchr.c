/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:04:48 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/14 22:28:43 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t	j;

	j = 0;
	while (j < n)
	{
		if ((unsigned char)c == ((unsigned char*)src)[j])
			return ((unsigned char*)src + j);
		j++;
	}
	return (NULL);
}
