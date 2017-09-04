/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_char_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:08:20 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:51:58 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					put_simple(const char *s, t_pr *e)
{
	int				x;

	free(e->b_disp);
	free(e->fl);
	free(e);
	if (s)
	{
		x = ft_strlen((char *)s);
		write(1, s, x);
		return (x);
	}
	return (0);
}

void				handler_char(int c, t_pr *e)
{
	e->pad--;
	e->fl->plus = FALSE;
	pad_left(e->fl->zero ? 1 : 0, e);
	wncl(c, e);
	if (e->fl->min)
		pad_right(e);
}

void				pad_str(t_pr *e)
{
	if (e->fl->min)
		return ;
	while (e->pad > 0)
	{
		wnl(e->fl->zero ? "0" : " ", 1, e);
		e->pad--;
	}
}

void				handler_string(char *s, t_pr *e)
{
	int				len;
	int				preslen;
	int				i;

	i = -1;
	e->fl->space = FALSE;
	e->fl->plus = FALSE;
	if (!s && !e->fl->ispres)
	{
		wnl("(null)", 6, e);
		return ;
	}
	len = s ? ft_strlen(s) : 0;
	preslen = (e->fl->pres < len && e->fl->ispres) ? e->fl->pres : len;
	e->pad -= preslen;
	pad_str(e);
	if (!s)
		return ;
	if (!e->fl->ispres)
		while (s[++i])
			wncl(s[i], e);
	else
		wnl(s, preslen, e);
	if (e->fl->min)
		pad_right(e);
}
