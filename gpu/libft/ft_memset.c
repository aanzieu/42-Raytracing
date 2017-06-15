/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:24:01 by svilau            #+#    #+#             */
/*   Updated: 2016/03/07 18:36:14 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*str_char;
	unsigned char	c_char;

	c_char = (unsigned char)c;
	str_char = str;
	while (n > 0)
	{
		*str_char = c_char;
		str_char++;
		n--;
	}
	return (str);
}
