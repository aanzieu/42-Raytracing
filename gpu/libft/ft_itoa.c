/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 18:53:31 by svilau            #+#    #+#             */
/*   Updated: 2016/03/18 12:31:46 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int		ft_count_int(int nb)
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

char			*ft_itoa(int n)
{
	int		count;
	int		nb;
	char	*str;

	nb = n;
	count = ft_count_int(nb);
	if (!(str = (char *)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	str[count--] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		return (ft_strcpy(str, "0"));
	if (nb == -2147483648)
		return (ft_strcpy(str, "-2147483648"));
	while (nb)
	{
		str[count--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}
