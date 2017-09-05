/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 19:57:34 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:04:21 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		reset_specs(t_flag *fl)
{
	fl->hash = FALSE;
	fl->zero = FALSE;
	fl->plus = FALSE;
	fl->space = FALSE;
	fl->min = FALSE;
	fl->pres = 0;
	fl->ispres = FALSE;
	fl->h = FALSE;
	fl->hh = FALSE;
	fl->l = FALSE;
	fl->ll = FALSE;
	fl->j = FALSE;
	fl->z = FALSE;
	fl->skip = FALSE;
	fl->si = FALSE;
}

void		free_pr(va_list va, t_pr *e)
{
	free(e->b_disp);
	free(e->fl);
	free(e);
	va_end(va);
}

int			init_pr(const char *format, t_pr *e)
{
	char	*swap;
	int		ret;

	e->fl = (t_flag *)malloc(sizeof(t_flag));
	e->i_disp = 0;
	if (!e || !e->fl || !(e->b_disp = (char *)malloc(BSIZE * sizeof(char))))
		return (-1);
	e->len = 0;
	if ((e->nbargs = get_nbconv(format)) == 0)
		return ((ret = put_simple(format, e)) == 0 ? -2 : ret);
	e->b = ft_strdup((char *)format);
	swap = e->b;
	free(swap);
	return (0);
}
