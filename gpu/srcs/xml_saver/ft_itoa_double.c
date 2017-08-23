/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 17:40:43 by PZC               #+#    #+#             */
/*   Updated: 2017/08/23 18:09:36 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_count_int(int nb)
{
	int count;

	count = 0;
	if (nb < 0)
		count++;
	if (nb == 0)
		count = 1;
	while (nb)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

static char *fill_string(char *str, int nb, int count, int zero)
{
	int point;

	point = 0;
	str[count--] = '\0';
	if (nb == 0)
		return (ft_strcpy(str, "0"));
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (zero == 1)
		str[0] = '0';
	else if (zero == 2)
		str[1] = '0';
	while (nb)
	{
		str[count--] = (nb % 10) + '0';
		nb /= 10;
		point++;
		if (point == 6)
			str[count--] = '.';
	}
	return (str);
}

char		*ft_itoa_double(double n)
{
	int		count;
	int		nb;
	int     zero;
	char	*str;

	nb = n * 1000000;
	zero = 0;
	count = ft_count_int(nb);
	if (count == 6)
	{
		zero = 1;
		count++;
	}
	else if (nb < 0 && count == 7)
	{
		zero = 2;
		count++;
	}
	count++;
	if (!(str = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	str = fill_string(str, nb, count, zero);
	return (str);
}
