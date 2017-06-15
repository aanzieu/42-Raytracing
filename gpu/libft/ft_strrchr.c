/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 13:25:53 by svilau            #+#    #+#             */
/*   Updated: 2016/03/17 22:34:25 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int				i;
	int				found;
	unsigned char	c_char;

	i = 0;
	found = -1;
	c_char = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == c_char)
			found = i;
		i++;
	}
	if (c_char == '\0')
		found = i;
	if (found == -1)
		return (NULL);
	return ((char *)str + found);
}
