/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:04:44 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/14 22:28:31 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	temp;

	i = 0;
	while (i < n)
	{
		temp = ((char*)src)[i];
		((char*)dest)[i] = temp;
		i++;
		if (temp == c)
			return ((char*)dest + i);
	}
	return (NULL);
}
