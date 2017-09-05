/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:06:11 by aanzieu           #+#    #+#             */
/*   Updated: 2016/03/13 16:17:46 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	size_t	i;

	if (!s || !f || !(new = ft_strdup(s)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = f(new[i]);
		i++;
	}
	return (new);
}
