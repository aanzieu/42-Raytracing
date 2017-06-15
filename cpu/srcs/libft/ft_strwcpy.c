/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 12:09:28 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/26 14:56:00 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strwcpy(const char *src, size_t n)
{
	size_t	j;
	size_t	i;
	char	*dst;

	i = 0;
	j = ft_strlen(src);
	if (j < n || j == 0)
		return (NULL);
	if ((dst = (char*)ft_memalloc((j - n + 1))) == NULL)
		return (NULL);
	while (n < j && src[n])
	{
		dst[i] = src[n];
		i++;
		n++;
	}
	while (i < j)
	{
		dst[i] = '\0';
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
