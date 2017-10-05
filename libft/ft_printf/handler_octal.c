/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_octal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:29:04 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:59:40 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			put_pad_octal(uintmax_t nb, t_pr *e, int nlen)
{
	e->pad = (e->fl->pres > nlen) ? e->pad - e->fl->pres : e->pad - nlen;
	pad_left(nb, e);
	put_precision(0, nlen, e);
	return (1);
}

void				ft_putnbr_oct(uintmax_t nb, char *base, t_pr *e)
{
	int				ret;
	uintmax_t		div;
	int				bsize;
	int				nlen;

	if (e->fl->hash)
		e->pad--;
	if (e->fl->hash && e->fl->ispres && e->pad == -1)
		e->fl->pres--;
	bsize = ft_strlen(base);
	nlen = get_nb_len(nb, bsize, e);
	div = put_pad_octal(nb, e, nlen);
	if (e->fl->hash)
		wncl('0', e);
	while ((nb / div) >= (unsigned long long)bsize)
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

void				handler_unsigned(uintmax_t nb, t_pr *e)
{
	e->fl->plus = FALSE;
	e->fl->space = FALSE;
	if (e->fl->hh && e->type != 'U')
		ft_putnbr_base((unsigned char)nb, "0123456789", e);
	else if (e->fl->l)
		ft_putnbr_umax((unsigned long)nb, "0123456789", e, 0);
	else if (e->fl->ll || e->type == 'U' || e->fl->j || e->fl->z)
		ft_putnbr_umax((unsigned long long)nb, "0123456789", e, 0);
	else if (e->fl->j)
		ft_putnbr_base((intmax_t)nb, "0123456789", e);
	else
		ft_putnbr_base((unsigned int)nb, "0123456789", e);
}

void				handler_octal(uintmax_t nb, t_pr *e)
{
	e->fl->plus = FALSE;
	e->fl->space = FALSE;
	if (nb == 0 && !e->fl->ispres)
		e->fl->hash = FALSE;
	if (e->fl->hh && e->type != 'O')
		ft_putnbr_base((unsigned char)nb, "01234567", e);
	else if (e->fl->h)
		ft_putnbr_base((unsigned short)nb, "01234567", e);
	else if (e->fl->l)
		ft_putnbr_umax((unsigned long)nb, "01234567", e, 0);
	else if (e->fl->ll || e->type == 'O' || e->fl->z || e->fl->j)
		ft_putnbr_oct(nb, "01234567", e);
	else if (e->fl->j)
		ft_putnbr_oct((uintmax_t)nb, "01234567", e);
	else
		ft_putnbr_oct((unsigned int)nb, "01234567", e);
}
