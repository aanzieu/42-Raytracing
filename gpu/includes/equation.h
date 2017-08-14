/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:45:23 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/21 16:55:28 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

# include <math.h>

# define ZERO_DP					(1e-4)
# define NOT_A_SOLUTION			0xFFFFFFFFFFFFFFFF

/*
** Structure for Equation N degrees
*/

typedef struct		s_solve
{
	double			tmp[4];
	double			det;
	double			res;
}					t_solve;

typedef struct		s_dichotomie
{
	double			l;
	double			r;
	double			mid;
	int				sl;
	int				sr;
	int				smid;
}					t_dichotomie;

typedef struct		s_eq
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			res;
}					t_eq;

#endif
