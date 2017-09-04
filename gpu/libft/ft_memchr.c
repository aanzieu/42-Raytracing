/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 15:19:28 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 11:18:30 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	c_char;
	unsigned char	*str_char;

	str_char = (unsigned char *)str;
	c_char = (unsigned char)c;
	while (n > 0)
	{
		if (*str_char == c_char)
			return ((void *)str_char);
		str_char++;
		n--;
	}
	return (NULL);
}
