/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:16:35 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 09:45:35 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

static char		*ft_concatenate(char *dest, char *src)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(src)
						+ 1))))
		return (NULL);
	while (dest[i] != '\0')
	{
		str[i] = dest[i];
		i++;
	}
	while (src[j] != '\0')
	{
		str[i] = src[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_ret;

	str_ret = ft_concatenate((char *)s1, (char *)s2);
	return (str_ret);
}
