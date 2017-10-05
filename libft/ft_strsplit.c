/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:03:09 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 13:43:10 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

static int		ft_word_count(char *str, char c)
{
	int word;
	int i;

	word = 0;
	i = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		while (str[i] != c && str[i] != '\0')
		{
			i++;
		}
		word++;
		while (str[i] == c)
			i++;
	}
	return (word);
}

static char		**ft_dest_assign(char **dest, char *str, char c)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		y = 0;
		while (str[i] != c && str[i] != '\0')
		{
			dest[x][y] = str[i];
			y++;
			i++;
		}
		dest[x][y] = '\0';
		x++;
		while (str[i] == c)
			i++;
	}
	dest[x] = NULL;
	return (dest);
}

char			**ft_strsplit(char const *str, char c)
{
	int		i;
	int		x;
	int		letter;
	char	**dest;

	x = 0;
	i = 0;
	if (!(dest = (char**)malloc(sizeof(*dest) * (ft_word_count((char *)str, c)
						+ 1))))
		return (NULL);
	while (str[i])
	{
		letter = 0;
		while (str[i] != c && str[i] != '\0')
		{
			letter++;
			i++;
		}
		if (!(dest[x++] = (char *)malloc(sizeof(*dest[x]) * (letter + 1))))
			return (NULL);
		while (str[i] == c)
			i++;
	}
	ft_dest_assign(dest, (char *)str, c);
	return (dest);
}
