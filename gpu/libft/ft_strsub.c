/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:05:08 by svilau            #+#    #+#             */
/*   Updated: 2016/03/15 22:09:57 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	int		i;
	char	*str_ret;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (!(str_ret = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len)
	{
		str_ret[i] = str[start];
		i++;
		str++;
		len--;
	}
	str_ret[i] = '\0';
	return (str_ret);
}
