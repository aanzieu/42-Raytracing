/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:06:06 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/10 20:06:06 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	top;
	size_t	j;

	top = ft_strlen(dest);
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (top > size - 1)
		return (size + ft_strlen(src));
	while ((top + j < size - 1) && src[j])
	{
		dest[j + top] = src[j];
		j++;
	}
	dest[j + top] = '\0';
	return (top + ft_strlen(src));
}
