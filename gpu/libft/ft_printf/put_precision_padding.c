/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_precision_padding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 21:29:01 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:04:53 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				pad_left2(intmax_t nb, t_pr *e)
{
	if (nb == 0 && e->fl->ispres && !e->fl->hash)
		e->pad++;
	if ((nb > 0 || (nb == 0 && e->pad > 1))
		&& !e->fl->plus && !e->fl->min && e->fl->space)
	{
		wnl(" ", 1, e);
		e->pad--;
	}
}

void				pad_left(intmax_t nb, t_pr *e)
{
	if (e->fl->min && !e->fl->plus)
		return ;
	pad_left2(nb, e);
	if (nb < 0)
	{
		if (e->fl->zero)
			put_sign('-', e);
		e->pad--;
		e->fl->plus = FALSE;
	}
	if (e->fl->plus && nb >= 0 && e->fl->zero)
	{
		put_sign('+', e);
		e->pad--;
	}
	while (e->pad > 0 && !e->fl->min)
	{
		wnl(e->fl->zero && e->fl->pres < e->pad ? "0" : " ", 1, e);
		e->pad--;
	}
	if (e->fl->plus && !e->fl->zero)
		wnl("+", 1, e);
}

void				pad_right(t_pr *e)
{
	if (e->pad > 0 && e->fl->min)
		while (e->pad > 0)
		{
			wnl(" ", 1, e);
			e->pad--;
		}
}

void				put_precision(intmax_t nb, int nlen, t_pr *e)
{
	if (nb == 1)
		put_sign('-', e);
	if (nb == 3)
		e->fl->pres++;
	if (nlen > e->fl->pres)
		return ;
	while (e->fl->pres > nlen)
	{
		wnl("0", 1, e);
		e->fl->pres--;
	}
}
