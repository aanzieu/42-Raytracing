/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 12:26:39 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 12:32:10 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	temp_char[n + 1];
	unsigned char	*dest_char;
	int				j;
	int				i;

	i = 0;
	j = n;
	dest_char = dest;
	ft_memcpy(temp_char, (unsigned char *)src, n);
	while (j > 0)
	{
		*dest_char = temp_char[i];
		dest_char++;
		j--;
		i++;
	}
	return (dest);
}
