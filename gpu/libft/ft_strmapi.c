/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 15:53:56 by svilau            #+#    #+#             */
/*   Updated: 2016/03/15 22:14:07 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	int		i;
	char	*str_ret;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (!(str_ret = (char *)malloc(sizeof(char) * (ft_strlen((char *)str)
						+ 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		str_ret[i] = f(i, str[i]);
		i++;
	}
	str_ret[i] = '\0';
	return (str_ret);
}
