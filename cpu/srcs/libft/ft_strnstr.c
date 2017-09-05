/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:06:31 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/13 16:59:05 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	int		count;
	int		start;
	int		end;

	if (needle[0] == '\0')
		return ((char*)haystack);
	count = 0;
	while (haystack[count] && n > 0)
	{
		if (n < ft_strlen(needle))
			return (NULL);
		start = 0;
		end = count;
		while (haystack[end] == needle[start] && haystack[end] && needle[start])
		{
			start++;
			end++;
		}
		if (needle[start] == '\0')
			return ((char*)haystack + count);
		n--;
		count++;
	}
	return (NULL);
}
