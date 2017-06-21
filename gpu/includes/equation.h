/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:45:23 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/20 14:05:00 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

# include <math.h>

# define IS_ZERO(X)		(fabs(X) < ZERO_DP ? 1 : 0)
# define ZERO_DP					(1e-6)
# define NOT_A_SOLUTION			0xFFFFFFFFFFFFFFFF

//# define SMALLER(A, B)		(((A) < (B) ? A : B))

/*
** Structure for Equation N degrees
*/

typedef struct		s_solve
{
	double			tmp[4];
	double			det;
	double			res;
}					t_solve;

typedef struct s_dichotomie
{
	double		l;
	double		r;
	double		mid;
	int			sl;
	int			sr;
	int			smid;
}				t_dichotomie;

typedef struct		s_eq
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
//	double			det;
	double			b0;
	double			b1;
	double			b2;
}					t_eq;
/*
# define POSITIVE(A)		(((A) > 0.0) ? (A) : 0.0)
# define MIN(A, B)		SMALLER(A, B)
# define MAX(A, B)		(((A) > (B)) ? (A) : (B))
# define CUBIC_ROOT(A)		(pow(A, 1.0 / 3.0))
# define CHECK_COEF(A)		((A < -ZERO_DP) ? (-1) : (A > ZERO_DP))
# define SIGNOF(A)		(((A) < -ZERO_DP) ? -1 : !(IS_ZERO(A)))
# define POW(A)			((A) * (A))
*/
#endif
