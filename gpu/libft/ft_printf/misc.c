/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 21:13:09 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:04:32 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		put_sign(char c, t_pr *e)
{
	if (!e->fl->si)
	{
		wncl(c, e);
		e->fl->si = TRUE;
	}
}

int			put_sign2(intmax_t nb, t_pr *e, int nlen)
{
	if ((!e->fl->zero || (e->fl->zero && e->fl->min)) && nlen > e->fl->pres)
	{
		put_sign('-', e);
		e->pad--;
	}
	return (nb);
}

int			put_pad_hex(uintmax_t nb, t_pr *e, uintmax_t nlen)
{
	put_precision(e->type == 'p' && nb == 0
			&& e->fl->ispres ? 3 : 0, nlen, e);
	if ((!e->fl->zero && !e->fl->ispres) || (e->type == 'p' && nb != 0))
		put_hash(e, nb);
	return (1);
}

int			put_pad_int(intmax_t nb, t_pr *e, int nlen)
{
	e->pad = (e->fl->pres > nlen) ? e->pad - e->fl->pres : e->pad - nlen;
	e->pad -= nb == 0 && e->fl->ispres && e->fl->zero ? 1 : 0;
	pad_left(nb, e);
	put_precision((nb < 0 && nlen < e->fl->pres ? 1 : 0), nlen, e);
	return (1);
}

int			put_pad_p(uintmax_t nb, t_pr *e, int nlen)
{
	pad_left(nb, e);
	put_precision(0, nlen, e);
	if (nb != '0')
		put_hash(e, nb);
	return (1);
}
