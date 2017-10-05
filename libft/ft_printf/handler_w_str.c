/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_w_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 19:01:27 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 19:02:02 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					ft_wcrlen(wchar_t *s)
{
	int				len;
	int				i;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] <= 0x7F)
			len++;
		else if (s[i] <= 0x7FF)
			len += 2;
		else if (s[i] <= 0xFFFF)
			len += 3;
		else if (s[i] <= 0x10FFFF)
			len += 4;
	}
	return (len);
}

int					sub_size(wchar_t c)
{
	if (c <= 0x7F)
		return (-1);
	else if (c <= 0x7FF)
		return (-2);
	else if (c <= 0xFFFF)
		return (-3);
	else if (c <= 0x10FFFF)
		return (-4);
	return (0);
}

int					get_wide_size(wchar_t *s, t_pr *e)
{
	int				i;
	int				len;

	i = 0;
	len = 0;
	if (e->fl->ispres)
		while (s[++i] && len < e->fl->pres)
		{
			if (s[i] <= 0x7F)
				len++;
			else if (s[i] <= 0x7FF)
				len += 2;
			else if (s[i] <= 0xFFFF)
				len += 3;
			else if (s[i] <= 0x10FFFF)
				len += 4;
		}
	if (len > e->fl->pres)
		len += sub_size(s[i]);
	return (len);
}

static void			set_flags(t_pr *e)
{
	e->fl->space = FALSE;
	e->fl->plus = FALSE;
}

void				handler_wstring(wchar_t *s, t_pr *e)
{
	int				len;
	int				ret;
	int				to_print;
	int				i;

	i = -1;
	ret = 0;
	set_flags(e);
	if (!s && !e->fl->ispres)
	{
		wnl("(null)", 6, e);
		return ;
	}
	to_print = e->fl->ispres ? get_wide_size(s, e) : ft_wcrlen(s);
	len = ft_wcrlen(s);
	e->pad -= to_print;
	pad_str(e);
	if (!e->fl->ispres)
		while (s[++i])
			wchar_to_c(s[i], e);
	else
		while (++i < to_print && ret < to_print)
			ret += wchar_to_c(s[i], e);
	if (e->fl->min)
		pad_right(e);
}
