/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 17:40:43 by PZC               #+#    #+#             */
/*   Updated: 2017/08/24 00:00:33 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char *fill_string(char *str, int nb, int neg)
{
	int point;
	int i;

	i = 26;
	point = 0;
	while (nb)
	{
		str[i--] = (nb % 10) + '0';
		nb /= 10;
		point++;
		while (nb == 0 && point < 6)
		{
			str[i--] = '0';
			point++;
		}
		if (point == 6)
			str[i--] = '.';
		if (point == 6 && nb == 0)
			str[i--] = '0';
	}
	if (neg)
		str[i--] = '-';
	return (&str[++i]);
}

char		*ft_itoa_double(double n)
{
	int		neg;
	int		nb;
	char	*str;

	if (!(str = ft_memalloc(28)))
		return (NULL);
	str[27] = '\0';
	nb = n * 1000000;
	if (nb == 0)
	{
		str[26] = '0';
		return (&str[26]);
	}
	neg = (nb < 0) ? 1 : 0;
	if (neg)
		nb *= -1;
	str = fill_string(str, nb, neg);
	return (str);
}
