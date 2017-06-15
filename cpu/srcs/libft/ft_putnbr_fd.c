/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:05:23 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/10 21:24:59 by aanzieu          ###   ########.fr       */
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

void			ft_putnbr_fd(int n, int fd)
{
	size_t	len;

	len = ft_len_nbr(n);
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 0)
		ft_putchar_fd(48, fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1;
		}
		while (len != 0)
		{
			ft_putchar_fd('0' + n / len, fd);
			n = n - n / len * len;
			len /= 10;
		}
	}
}
