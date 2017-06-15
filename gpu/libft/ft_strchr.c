/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:58:36 by svilau            #+#    #+#             */
/*   Updated: 2016/03/09 14:28:05 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	c_char;

	i = 0;
	c_char = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == c_char)
			return ((char *)str + i);
		i++;
	}
	if (c_char == '\0')
		return ((char *)str + i);
	return (NULL);
}
