/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:13:52 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 10:43:54 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(char *str, char *to_find, size_t len)
{
	int i;
	int j;
	int s;

	i = 0;
	s = 0;
	if (*to_find == '\0')
		return (str);
	while (to_find[s] != '\0')
		s++;
	if (to_find == '\0')
		return (str);
	while (str[i])
	{
		j = 0;
		while (to_find[j] == str[i + j] && (i + j) < (int)len)
		{
			if (j == s - 1)
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}
