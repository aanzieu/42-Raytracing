/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/27 18:12:46 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	show_error(const char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	show_error_2(const char *s1, const char *s2)
{
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(s2, 2);
	exit(EXIT_FAILURE);
}
