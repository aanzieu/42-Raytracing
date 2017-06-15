/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:04:37 by aanzieu           #+#    #+#             */
/*   Updated: 2017/03/28 08:59:47 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_nbr(int n)
{
	int size;

	size = 0;
	if (n < 0)
		size++;
	while (n / 10 != 0)
	{
		n /= 10;
		size++;
	}
	size++;
	return (size);
}

char			*ft_itoa(int n)
{
	char	*new;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len_nbr(n);
	if (!(new = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		*new = '-';
		n *= -1;
	}
	new[len] = '\0';
	while (n >= 10)
	{
		new[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	new[len - 1] = n + '0';
	return (new);
}
