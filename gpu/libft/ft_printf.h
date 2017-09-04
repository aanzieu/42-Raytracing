/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 21:26:36 by huweber           #+#    #+#             */
/*   Updated: 2017/04/20 19:08:25 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include <locale.h>
# include <limits.h>
# define TRUE 1
# define FALSE 0
# define BSIZE 5000

typedef struct		s_flag
{
	int				zero;
	int				plus;
	int				min;
	int				pres;
	int				ispres;
	int				h;
	int				hh;
	int				l;
	int				ll;
	int				j;
	int				z;
	int				hash;
	int				space;
	int				skip;
	int				si;
}					t_flag;

typedef struct		s_pr
{
	int				nbargs;
	int				currconv;
	char			*b;
	char			*b_disp;
	int				i_disp;
	char			type;
	int				len;
	int				pad;
	struct s_flag	*fl;
}					t_pr;

/*
**	FILE CHECK_CONV.C
*/

int					get_nbconv(const char *format);
void				get_next_conv(t_pr *e);
void				get_wrong_conv(t_pr *e);
int					check_conv(char c);
int					wrong_char(char c);

/*
**	FILE FT_PRINTF.C
*/

int					ft_printf(const char *format, ...);

/*
**	FILE HANDLER_CHAR_STR.C
*/

int					put_simple(const char *s, t_pr *e);
void				pad_str(t_pr *e);
void				handler_char(int c, t_pr *e);
void				handler_string(char *s, t_pr *e);

/*
**	FILE HANDLER_HEXA.C
*/

void				ft_putnbr_hex(uintmax_t nb, char *base, t_pr *e);
void				put_hash(t_pr *e, intmax_t nb);
void				ft_putnbr_p(uintmax_t nb, char *base, t_pr *e);
void				handler_hexa2(unsigned long long nb, t_pr *e);
void				handler_hexa(uintmax_t nb, t_pr *e);

/*
**	FILE HANDLER_INT.C
*/

int					get_nb_len(intmax_t nb, int basesize, t_pr *e);
void				ft_putnbr_base(intmax_t nb, char *base, t_pr *e);
void				handler_int(intmax_t nb, t_pr *e);

/*
**	FILE HANDLER_LONG.C
*/

void				ft_putnbr_umax(uintmax_t nb,
							char *base, t_pr *e, int flag);
int					put_pad_l(long int nb, t_pr *e, int flag, int nlen);
void				ft_putnbr_l(long int nb, char *base, t_pr *e, int flag);

/*
**	FILE HANDLER_OCTAL.C
*/

void				ft_putnbr_oct(uintmax_t nb, char *base, t_pr *e);
void				handler_unsigned(uintmax_t nb, t_pr *e);
void				handler_octal(uintmax_t nb, t_pr *e);

/*
**	FILE HANDLER_W_STR.C
*/

int					ft_wcrlen(wchar_t *s);
int					sub_size(wchar_t c);
int					get_wide_size(wchar_t *s, t_pr *e);
void				handler_wstring(wchar_t *s, t_pr *e);

/*
**	FILE HANDLER_WCHAR.C
*/

int					wchar_to_c2(wchar_t c, t_pr *e);
int					wchar_to_c(wchar_t c, t_pr *e);
void				handler_wchar(wchar_t c, t_pr *e);

/*
**	FILE INIT_ENV.C
*/

void				reset_specs(t_flag *fl);
void				free_pr(va_list va, t_pr *e);
int					init_pr(const char *format, t_pr *e);

/*
**	FILE MISC.C
*/

void				put_sign(char c, t_pr *e);
int					put_sign2(intmax_t nb, t_pr *e, int nlen);
int					put_pad_hex(uintmax_t nb, t_pr *e, uintmax_t nlen);
int					put_pad_int(intmax_t nb, t_pr *e, int nlen);
int					put_pad_p(uintmax_t nb, t_pr *e, int nlen);

/*
**	FILE PARSE_BUFFER.C
*/

void				wnl(char *s, int size, t_pr *e);
void				wnil(int i, t_pr *e);
void				wncl(char c, t_pr *e);

/*
**	FILE PARSE_HANDLER.C
*/

int					parse_handler(t_pr *e, t_flag *fl);

/*
**	FILE PARSE_HANDLER.C
*/

void				pad_left2(intmax_t nb, t_pr *e);
void				pad_left(intmax_t nb, t_pr *e);
void				pad_right(t_pr *e);
void				put_precision(intmax_t nb, int nlen, t_pr *e);

#endif
