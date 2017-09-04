/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:30:59 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:59:09 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			sign_umax(int flag, t_pr *e)
{
	if (flag == 1)
	{
		if (!e->fl->zero || (e->fl->zero && e->fl->min))
		{
			wnl("-", 1, e);
			e->pad--;
		}
	}
}

void				ft_putnbr_umax(uintmax_t nb, char *base, t_pr *e, int flag)
{
	uintmax_t		ret;
	uintmax_t		div;
	int				bsize;
	int				nlen;

	bsize = ft_strlen(base);
	nlen = get_nb_len(nb, bsize, e);
	e->pad = (e->fl->pres > nlen) ? e->pad - e->fl->pres : e->pad - nlen;
	pad_left(nb, e);
	put_precision(0, nlen, e);
	div = 1;
	sign_umax(flag, e);
	while ((nb / div) >= (unsigned long)bsize)
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

int					put_pad_l(long int nb, t_pr *e, int flag, int nlen)
{
	e->pad = (e->fl->pres > nlen) ? e->pad - e->fl->pres : e->pad - nlen;
	pad_left(nb, e);
	put_precision((nb < 0 && nlen < e->fl->pres ? 1 : 0), nlen, e);
	sign_umax(flag, e);
	return (1);
}

void				ft_putnbr_l(long int nb, char *base, t_pr *e, int flag)
{
	long int		ret;
	long int		div;
	unsigned int	bsize;
	int				nlen;
	int				max;

	max = (nb == LONG_MIN) ? 1 : 0;
	if (nb == LONG_MIN)
		nb++;
	nb = nb < 0 ? -nb : nb;
	bsize = ft_strlen(base);
	nlen = get_nb_len(nb, bsize, e);
	div = put_pad_l(nb, e, flag, nlen);
	while ((nb / div) >= bsize)
		div = div * bsize;
	while (div > 0)
	{
		if (nb == 0 && e->fl->ispres)
			break ;
		ret = (nb / div) % bsize;
		if (max == 1 && div < bsize)
			ret++;
		wnil(base[ret], e);
		div = div / bsize;
	}
}
