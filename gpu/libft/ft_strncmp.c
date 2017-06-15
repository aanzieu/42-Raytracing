/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:38:02 by svilau            #+#    #+#             */
/*   Updated: 2016/03/21 16:27:40 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
		{
			j = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (j);
		}
		i++;
	}
	return (0);
}
