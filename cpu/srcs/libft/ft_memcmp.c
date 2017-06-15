/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:04:52 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/13 13:40:46 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	j;

	j = 0;
	while (j < n)
	{
		if (*((char*)str1 + j) != *((char*)str2 + j))
			return (*((unsigned char*)str1 + j) - *((unsigned char*)str2 + j));
		j++;
	}
	return (0);
}
