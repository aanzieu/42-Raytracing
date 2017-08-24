/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:06:07 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/24 18:07:12 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_count_double(double n)
{
	int count;
	int nb;

	count = 7;
	nb = n;
	if (n < 0)
		count++;
	if (nb == 0)
		count++;
	while (nb)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

static char	*fill_string(char *str, int nb, int neg, int size)
{
	int point;

	point = 0;
	size--;
	while (nb)
	{
		str[size--] = (nb % 10) + '0';
		nb /= 10;
		point++;
		while (nb == 0 && point < 6)
		{
			str[size--] = '0';
			point++;
		}
		if (point == 6)
			str[size--] = '.';
		if (point == 6 && nb == 0)
			str[size--] = '0';
	}
	if (neg)
		str[size] = '-';
	return (str);
}

char		*ft_itoa_double(double n)
{
	int		neg;
	int		nb;
	int		size;
	char	*str;

	if (n == 0)
	{
		if (!(str = ft_strnew(1)))
			return (NULL);
		str[0] = '0';
		return (str);
	}
	size = ft_count_double(n);
	if (!(str = ft_strnew(size)))
		return (NULL);
	nb = n * 1000000;
	neg = (nb < 0) ? 1 : 0;
	if (neg)
		nb *= -1;
	return (fill_string(str, nb, neg, size));
}
