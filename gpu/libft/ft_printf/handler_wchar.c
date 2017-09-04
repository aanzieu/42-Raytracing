/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_wchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:08:40 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 19:03:54 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					wchar_to_c2(wchar_t c, t_pr *e)
{
	wncl((c >> 18) + 0xF0, e);
	wncl(((c >> 12) & 0x3F) + 0x80, e);
	wncl(((c >> 6) & 0x3F) + 0x80, e);
	wncl((c & 0x3F) + 0x80, e);
	return (4);
}

int					wchar_to_c(wchar_t c, t_pr *e)
{
	int				ret;

	ret = 0;
	if (c <= 0x7F)
	{
		wncl(c, e);
		ret++;
	}
	else if (c <= 0x7FF)
	{
		wncl((c >> 6) + 0xC0, e);
		wncl((c & 0x3F) + 0x80, e);
		ret += 2;
	}
	else if (c <= 0xFFFF)
	{
		wncl((c >> 12) + 0xE0, e);
		wncl(((c >> 6) & 0x3F) + 0x80, e);
		wncl((c & 0x3F) + 0x80, e);
		ret += 3;
	}
	else if (c <= 0x10FFFF)
		ret += wchar_to_c2(c, e);
	return (ret);
}

void				handler_wchar(wchar_t c, t_pr *e)
{
	e->pad--;
	e->fl->plus = FALSE;
	pad_left(0, e);
	wchar_to_c(c, e);
	if (e->fl->min)
		pad_right(e);
}
