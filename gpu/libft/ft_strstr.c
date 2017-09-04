/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 08:14:36 by svilau            #+#    #+#             */
/*   Updated: 2016/03/17 22:44:21 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
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
	while (str[i])
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (j == s - 1)
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}
