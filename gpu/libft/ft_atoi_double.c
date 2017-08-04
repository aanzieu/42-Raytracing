/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 10:11:52 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/02 14:33:19 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atoi_double(char const *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int		neg;

	neg = 1;
	c = (char *)str;
	res = (double)ft_atoi(c);
	if (*c == '-')
		neg = -1;
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	if (ft_strlen(c) > 9)
		c[9] = 0;
	res2 = (double)ft_atoi(c);
	len = ft_strlen(c);
	while (len-- > 0)
		res2 /= 10;
	res2 *= neg;
	return ((res + res2));
}
