/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:43:58 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:03:05 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			put_hash(t_pr *e, intmax_t nb)
{
	if ((e->fl->hash == TRUE && nb != 0) || e->type == 'p')
	{
		if (e->type == 'x' || (e->type == 'p' && !e->fl->skip))
			wnl("0x", 2, e);
		else if (!e->fl->skip)
			wnl("0X", 2, e);
		e->fl->skip = TRUE;
	}
}

void			ft_putnbr_hex(uintmax_t nb, char *base, t_pr *e)
{
	uintmax_t	ret;
	uintmax_t	div;
	uintmax_t	bsize;
	uintmax_t	nlen;

	if (e->fl->hash || e->type == 'p')
		e->pad -= 2;
	if (e->fl->zero || (e->type == 'p' &&
						(e->fl->zero || nb == 0 || e->fl->pres > e->pad)))
		put_hash(e, nb);
	bsize = ft_strlen(base);
	nlen = get_nb_len(nb, bsize, e);
	e->pad = (e->fl->pres > (int)nlen) ? e->pad - e->fl->pres : e->pad - nlen;
	pad_left(nb, e);
	div = put_pad_hex(nb, e, nlen);
	while ((nb / div) >= bsize)
		div = div * bsize;
	while (div > 0)
	{
		if (nb == 0 && e->fl->ispres)
			break ;
		ret = (nb / div) % bsize;
		wnil(base[ret], e);
		div = div / bsize;
	}
}

void			ft_putnbr_p(uintmax_t nb, char *base, t_pr *e)
{
	uintmax_t	ret;
	uintmax_t	div;
	uintmax_t	bsize;
	uintmax_t	nlen;

	e->pad -= 2;
	if (e->fl->zero || (nb == 0 && e->fl->ispres)
		|| (e->fl->ispres && e->fl->pres > e->pad))
		put_hash(e, nb);
	bsize = ft_strlen(base);
	nlen = get_nb_len(nb, bsize, e);
	e->pad = (e->fl->pres > (int)nlen) ? e->pad - e->fl->pres : e->pad - nlen;
	if (nb == 0 && e->fl->ispres)
		e->fl->pres++;
	div = put_pad_p(nb, e, nlen);
	while ((nb / div) >= bsize)
		div = div * bsize;
	while (div > 0)
	{
		if (nb == 0 && e->fl->ispres)
			break ;
		ret = (nb / div) % bsize;
		wnil(base[ret], e);
		div = div / bsize;
	}
}

void			handler_hexa2(unsigned long long nb, t_pr *e)
{
	if (e->type == 'x' && e->fl->hash && e->fl->ispres)
		put_hash(e, nb);
	if (e->fl->j)
	{
		if (e->type == 'x')
			ft_putnbr_umax(nb, "0123456789abcdef", e, 0);
		else if (e->type == 'X')
			ft_putnbr_umax(nb, "0123456789ABCDEF", e, 0);
	}
	else if (e->type == 'x')
		ft_putnbr_hex(nb, "0123456789abcdef", e);
	else if (e->type == 'p')
		ft_putnbr_p(nb, "0123456789abcdef", e);
	else if (e->type == 'X')
		ft_putnbr_hex(nb, "0123456789ABCDEF", e);
}

void			handler_hexa(uintmax_t nb, t_pr *e)
{
	e->fl->plus = FALSE;
	e->fl->space = FALSE;
	if (e->fl->hh)
		handler_hexa2((unsigned char)nb, e);
	else if (e->fl->l && e->type != 'p')
		handler_hexa2((unsigned long)nb, e);
	else if (e->fl->ll || e->fl->z)
		handler_hexa2((unsigned long long)nb, e);
	else if (e->fl->j)
		handler_hexa2((uintmax_t)nb, e);
	else if (e->type == 'p')
		handler_hexa2((intmax_t)nb, e);
	else
		handler_hexa2((unsigned int)nb, e);
	if (e->fl->min)
		pad_right(e);
}
