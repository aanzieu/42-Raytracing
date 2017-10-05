/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:58:50 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:01:16 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				get_nbconv(const char *format)
{
	int				i;
	int				ret;

	i = -1;
	ret = 0;
	while (format[++i])
		if (format[i] == '%')
			ret++;
	return (ret);
}

void			get_next_conv(t_pr *e)
{
	int				i;

	i = 0;
	e->pad--;
	while (e->b[i] != '\0' && e->b[i] != '%')
	{
		wncl(e->b[i], e);
		i++;
	}
	e->b = &e->b[i];
}

void			get_wrong_conv(t_pr *e)
{
	int				i;

	i = 0;
	e->pad--;
	if (!e->fl->space && e->pad != -1)
		pad_left(1, e);
	while (e->b[i] != '\0' && e->b[i] != '%')
	{
		wncl(e->b[i], e);
		if (i == 0 && e->fl->min)
			pad_right(e);
		i++;
	}
	e->b = &e->b[i];
}

int				check_conv(char c)
{
	if (c != 's' && c != 'S' && c != 'p' && c != 'd'
		&& c != 'D' && c != 'i' && c != 'o' && c != 'O'
		&& c != 'u' && c != 'U' && c != 'x' && c != 'X'
		&& c != 'c' && c != 'C' && c != '%')
		return (1);
	return (0);
}

int				wrong_char(char c)
{
	if (c != 's' && c != 'S' && c != 'p' && c != 'd'
		&& c != 'D' && c != 'i' && c != 'o' && c != 'O'
		&& c != 'u' && c != 'U' && c != 'x' && c != 'X'
		&& c != 'c' && c != 'C' && c != '%' && c != ' '
		&& c != 'l' && c != 'z' && c != 'j' && c != '-'
		&& c != '+' && c != 'h' && c != '0' && c != '#'
		&& c != '.' && !ft_isdigit(c))
		return (1);
	return (0);
}
