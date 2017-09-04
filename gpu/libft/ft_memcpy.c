/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:20:09 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 08:38:00 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char		*src_char;
	unsigned char	*dest_char;

	dest_char = dest;
	src_char = src;
	while (n > 0)
	{
		*dest_char = *src_char;
		src_char++;
		dest_char++;
		n--;
	}
	return (dest);
}
