/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:05:50 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/02 12:36:12 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*temp;

	if ((temp = (char*)malloc((ft_strlen(str) + 1))) == NULL)
		return (NULL);
	ft_strcpy(temp, str);
	return (temp);
}
