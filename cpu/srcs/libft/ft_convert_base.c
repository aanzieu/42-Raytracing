/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 07:53:13 by aanzieu           #+#    #+#             */
/*   Updated: 2017/03/06 08:49:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_val(char *nbr, char *base_from)
{
	int	num;
	int	i;
	int	j;

	num = 0;
	i = 0;
	while (nbr[i])
	{
		j = 0;
		while (base_from[j])
		{
			if (nbr[i] == base_from[j])
				num = (num * ft_strlen(base_from)) + j;
			j++;
		}
		i++;
	}
	return (num);
}

int		ft_val_j(int val, int len)
{
	int j;

	j = 0;
	while (val > 0)
	{
		val = val / len;
		j++;
	}
	return (j);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*res;
	int		val;
	int		len;
	int		i;
	int		j;

	val = ft_val(nbr, base_from);
	len = ft_strlen(base_to);
	j = ft_val_j(val, len);
	res = (char*)malloc(sizeof(char) * (j + 1));
	i = 0;
	if (val)
		while (val > 0)
		{
			res[--j] = base_to[val % len];
			val = val / len;
			i++;
		}
	else
	{
		res[i] = base_to[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
