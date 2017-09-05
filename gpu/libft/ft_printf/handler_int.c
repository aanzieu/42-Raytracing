/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 18:58:24 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:03:15 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					get_nb_len(intmax_t nb, int basesize, t_pr *e)
{
	int				len;

	(void)e;
	len = nb == 0 ? 1 : 0;
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		len++;
		nb /= basesize;
	}
	return (len);
}

void				ft_putnbr_base(intmax_t nb, char *base, t_pr *e)
{
	intmax_t		ret;
	intmax_t		div;
	int				bsize;
	int				nlen;

	e->pad -= e->fl->plus && !e->fl->zero ? 1 : 0;
	bsize = ft_strlen(base);
	nlen = get_nb_len(nb, bsize, e);
	div = put_pad_int(nb, e, nlen);
	if (nb < 0)
	{
		put_sign2(nb, e, nlen);
		nb = -nb;
	}
	while ((nb / div) >= bsize)
		div = div * bsize;
	while (div > 0)
	{
		if (nb == 0 && e->fl->ispres && !e->fl->zero)
			break ;
		ret = (nb / div) % bsize;
		wnil(base[ret], e);
		div = div / bsize;
	}
}

void				handler_int(intmax_t nb, t_pr *e)
{
	if (e->fl->ll)
		e->fl->l = FALSE;
	if (e->type == 'd' || e->type == 'i' || e->type == 'D')
	{
		if (e->fl->h && !e->fl->hh)
			ft_putnbr_base(e->type == 'D' ? (unsigned short int)nb :
				(short int)nb, "0123456789", e);
		else if (e->fl->hh && e->type != 'D')
			ft_putnbr_base((signed char)nb, "0123456789", e);
		else if (e->fl->z)
			ft_putnbr_umax((long long int)nb, "0123456789", e, nb < 0 ? 1 : 0);
		else if ((e->fl->l && !e->fl->ll) || e->type == 'D')
			ft_putnbr_l((long int)nb, "0123456789", e, nb < 0 ? 1 : 0);
		else if (e->fl->ll || e->fl->j)
			ft_putnbr_umax((size_t)nb, "0123456789", e, nb < 0 ? 1 : 0);
		else
			ft_putnbr_base((int)nb, "0123456789", e);
	}
	else if (e->type == 'o' || e->type == 'O')
		handler_octal(nb, e);
	else if (e->type == 'u' || e->type == 'U')
		handler_unsigned((uintmax_t)nb, e);
	if (e->fl->min)
		pad_right(e);
}
