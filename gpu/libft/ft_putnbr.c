/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <svilau@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/19 10:53:15 by svilau            #+#    #+#             */
/*   Updated: 2016/03/15 22:03:51 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static int	pos_nb(int nb)
{
	if (nb < 0)
	{
		ft_putchar('-');
		if (nb == -2147483648)
		{
			nb *= -1;
			nb -= 1;
		}
		else
			nb *= -1;
	}
	return (nb);
}

static int	max_pow10(int nb)
{
	int pow;

	pow = 1;
	while (nb > 9)
	{
		pow *= 10;
		nb /= 10;
	}
	return (pow);
}

void		ft_putnbr(int nb)
{
	int	pow10;
	int digit;
	int x;

	x = nb;
	if (nb == 0)
	{
		ft_putchar('0');
	}
	else
	{
		nb = pos_nb(nb);
		pow10 = max_pow10(nb);
		while (pow10)
		{
			digit = nb / pow10;
			if (pow10 == 1 && x == -2147483648)
				ft_putchar('8');
			else
				ft_putchar(digit + '0');
			nb -= digit * pow10;
			pow10 /= 10;
		}
	}
}
