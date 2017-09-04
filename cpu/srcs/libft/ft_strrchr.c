/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:06:34 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/13 13:50:04 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*temp;

	temp = ft_strchr(str, '\0');
	while (temp >= str)
	{
		if (*temp == (unsigned char)c)
			return ((char*)temp);
		temp--;
	}
	return (NULL);
}
