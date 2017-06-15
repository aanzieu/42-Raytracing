/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:05:21 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/10 21:20:34 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_nbr(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		i = i * 10;
		n = n / 10;
	}
	return (i);
}

void			ft_putnbr(int n)
{
	size_t	len;

	len = ft_len_nbr(n);
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n == 0)
		ft_putchar(48);
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n *= -1;
		}
		while (len != 0)
		{
			ft_putchar('0' + n / len);
			n = n - n / len * len;
			len /= 10;
		}
	}
}
