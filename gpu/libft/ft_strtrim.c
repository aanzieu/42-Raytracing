/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:34:14 by svilau            #+#    #+#             */
/*   Updated: 2016/03/21 15:51:11 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

static int	ft_count_end(char *str)
{
	int i;
	int j;
	int t;

	i = 0;
	j = 0;
	if (str == NULL)
		return (0);
	while (str[i++] != '\0')
	{
		t = 1;
		j = i;
		while (str[j] != '\0')
		{
			if (str[j] != ' ' && str[j] != '\n' && str[j] != '\t')
			{
				t = 0;
				break ;
			}
			j++;
		}
		if (t == 1)
			return (i);
	}
	return (i);
}

static int	ft_count(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t') &&
			str[i] != '\0')
		i++;
	while (i < ft_count_end((char *)str))
	{
		count++;
		i++;
	}
	return (count);
}

static int	ft_check_blank(char *str)
{
	int i;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t') &&
			str[i] != '\0')
	{
		if (str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *str)
{
	int		i;
	int		j;
	int		n;
	char	*str_ret;

	i = 0;
	j = 0;
	n = ft_count_end((char *)str);
	if (str == NULL)
		return (NULL);
	if (!(str_ret = (char *)malloc(sizeof(char) * (ft_count((char *)str) + 1))))
		return (NULL);
	if (ft_check_blank((char *)str) == 1)
		return (NULL);
	while ((str[i] == ' ' || str[i] == '\n' || str[i] == '\t') &&
			str[i] != '\0')
		i++;
	while (i < n)
	{
		str_ret[j] = str[i];
		j++;
		i++;
	}
	str_ret[j] = '\0';
	return (str_ret);
}
