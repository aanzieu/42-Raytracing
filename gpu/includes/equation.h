/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:45:23 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 13:34:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_H
# define EQUATION_H

#include <math.h>
#include <float.h>

#define EPSILON				(1e-9)
#define IS_ZERO(X)			(fabs(X) < ZERO_DP ? 1 : 0)
#define ZERO_DP			(1e-4)
#define NOT_A_SOLUTION		0xFFFFFFFFFFFFFFFF
#define MAX_ROOT			(1e10)
#define SIGNOF(A)			(((A) < -ZERO_DP) ? -1 : !(IS_ZERO(A)))
#define POSITIVE(A)		(((A) > 0.0) ? (A) : 0.0)
#define MIN(A, B)			SMALLER(A, B)
#define MAX(A, B)			(((A) > (B)) ? (A) : (B))
#define CUBIC_ROOT(A)		(pow(A, 1.0 / 3.0))
#define CHECK_COEF(A)		((A < -ZERO_DP) ? (-1) : (A > ZERO_DP))
#define POW(A)				((A) * (A))

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
	double			dr;
	double			mid;
	double			q;
	double			r;
	double			bq;
	double			br;
	double			bq3;
	double			br2;
	double			cr2;
	double			cq3;
	double			sqrtbq;
	double			sgnbr;
	double			ratio;
	double			theta;
	double			norm;
	double			r0;
	double			r1;
	double			r2;
	double			ba;
	double			bb;
	int				i;
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
	double			f;
	double			g;
	double			res;
}					t_eq;

#endif
