/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 20:51:47 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 19:07:16 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_precision(t_pr *e, int i)
{
	i++;
	e->fl->ispres = TRUE;
	e->fl->pres = ft_atoi(&e->b[i]);
	while (!ft_isdigit(e->b[i]))
		i++;
	return (i);
}

static int		parse_handler3(t_flag *fl, char c, char cc)
{
	if (c == 'h' && cc == 'h')
		fl->hh = TRUE;
	else if (c == 'h')
		fl->h = TRUE;
	else if (c == ' ')
		fl->space = TRUE;
	else if (c == 'l' && cc == 'l')
		fl->ll = TRUE;
	else if (c == 'l')
		fl->l = TRUE;
	else if (c == 'z')
		fl->z = TRUE;
	else if (c == 'j')
		fl->j = TRUE;
	else if (c == '+')
		fl->plus = TRUE;
	else if (c == '-')
		fl->min = TRUE;
	else if (c == '#')
		fl->hash = TRUE;
	else if (c == '.' && !ft_isdigit(cc))
		fl->ispres = TRUE;
	else
		return (1);
	return (0);
}

static int		parse_handler2(t_pr *e, int i)
{
	if (!e->fl->zero && e->b[i] == '0' && e->pad == 0)
		e->fl->zero = TRUE;
	else if (ft_isdigit(e->b[i]) && e->fl->pres == 0 && e->pad == 0)
		e->pad = ft_atoi(&e->b[i]);
	else
		return (1);
	return (0);
}

int				parse_handler(t_pr *e, t_flag *fl)
{
	int			i;

	i = 0;
	if (e->b[i] == '%')
		i++;
	while (check_conv(e->b[i]))
	{
		if (parse_handler2(e, i) == 0)
			;
		else if (e->b[i] == '\0')
			break ;
		else if (parse_handler3(fl, e->b[i], e->b[i + 1]) == 0)
			;
		else if (e->b[i] == '.' && ft_isdigit(e->b[i + 1]))
			i = get_precision(e, i);
		if (wrong_char(e->b[i]) == 1)
		{
			e->b = &e->b[i];
			get_wrong_conv(e);
			return (1);
		}
		i++;
	}
	e->b = &e->b[i];
	return (0);
}
