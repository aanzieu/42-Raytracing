/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 20:20:31 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 18:49:28 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			handler_fork(va_list va, t_pr *e)
{
	if (e->type == 'C' || (e->type == 'c' && e->fl->l))
		handler_wchar(va_arg(va, wchar_t), e);
	else if (e->type == 'c')
		handler_char(va_arg(va, int), e);
	else if (e->type == '%')
		handler_char('%', e);
	else if (e->type == 'S' || (e->type == 's' && e->fl->l))
		handler_wstring(va_arg(va, wchar_t *), e);
	else if (e->type == 's')
		handler_string(va_arg(va, char *), e);
	else if (e->type == 'd' || e->type == 'o' || e->type == 'O'
		|| e->type == 'u' || e->type == 'U' || e->type == 'i')
		handler_int(va_arg(va, intmax_t), e);
	else if (e->type == 'D')
		handler_int(va_arg(va, long int), e);
	else if (e->type == 'x' || e->type == 'X' || e->type == 'p')
		handler_hexa(va_arg(va, uintmax_t), e);
}

static void			parse_conv(va_list va, t_pr *e)
{
	e->pad = 0;
	if (e->b[0] == '\0' && e->b[0] != '%')
		return ;
	reset_specs(e->fl);
	if (parse_handler(e, e->fl) == 1)
		return ;
	e->type = e->b[0];
	e->b = &e->b[1];
	handler_fork(va, e);
}

int					ft_printf(const char *format, ...)
{
	va_list			va;
	t_pr			*e;
	int				i;
	int				ret;

	i = -1;
	va_start(va, format);
	e = (t_pr *)malloc(sizeof(t_pr));
	if ((ret = init_pr(format, e)) > 0)
		return (ret);
	if (ret == -2)
		return (0);
	while (++i < e->nbargs)
	{
		if (e->b[0] != '\0' && e->b[0] != '%')
			get_next_conv(e);
		parse_conv(va, e);
	}
	if (e->b)
		get_next_conv(e);
	e->b_disp[e->len] = '\0';
	write(1, e->b_disp, e->len);
	free_pr(va, e);
	return (e->len);
}
