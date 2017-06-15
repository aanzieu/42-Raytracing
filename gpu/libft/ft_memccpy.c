/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:55:18 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 10:49:01 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*src_char;
	unsigned char	*dest_char;
	unsigned char	c_char;

	dest_char = dest;
	src_char = (unsigned char *)src;
	c_char = (unsigned char)c;
	while (n > 0)
	{
		*dest_char = *src_char;
		if (*src_char == c_char)
			return (dest_char + 1);
		src_char++;
		dest_char++;
		n--;
	}
	return (NULL);
}
