/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 10:54:43 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/13 16:51:42 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

# include <math.h>
/*
# define ZERO_DP					(1e-6)
# define ZERO(X)					(fabs(X) < ZERO_DP ? 1 : 0)
# define POSITIVE_VALUE(X)		(((X) > 0.0) ? X : 0.0)
# define CHECK_SOLUTION(X)		((((X) > 0.0) ? X : -1.0)
# define SMALLER_THAN(A, B)		(((A) < (B) ? A : B))
# define MIN(A, B)				SMALLER_THAN(A, B)
# define MAX(A, B)				(((A) > (B) ? A : B))
# define TIERS 0.333333333333
*/
/*
** Structure for Equation N degrees
*/

typedef struct		s_solve
{
	double			s1;
	double			s2;
	double			s3;
	double			s4;
	int				none;
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
	double			delta;
	double			b0;
	double			b1;
	double			b2;
}					t_eq;

/*
** Equation Resolve 2nd, 3th, 4th degrees
*/

t_solve				equation_second_degres(t_eq e);
t_solve				second_degres(double a, double b, double c);
double				positive_solution(t_solve solve);

/*
** Structure for Operation Vector, Plan
*/

typedef struct		s_2point
{
	double			x;
	double			y;
}					t_2point;

typedef struct		s_3point
{
	double			x;
	double			y;
	double			z;
}					t_3point;

typedef struct		s_vec2d
{
	double			x;
	double			y;
}					t_vec2d;

typedef struct		s_vec3d
{
	double			x;
	double			y;
	double			z;
}					t_vec3d;

/*
** Operation Vector
*/

t_vec3d				vector_sum(t_vec3d a, t_vec3d b);
t_vec3d				vector_sub(t_vec3d a, t_vec3d b);
t_vec3d				vector_scalaire(t_vec3d a, double b);
t_vec3d				vector_neg(t_vec3d v);
t_3point			vector_to_point(t_vec3d m, t_3point a);

/*
** Properties Vector
*/

double				vector_square_root(t_vec3d v);
double				vector_dotproduct(t_vec3d a, t_vec3d b);
t_vec3d				vector_normalize(t_vec3d v);
t_vec3d				vector_crossproduct(t_vec3d a, t_vec3d b);

/*
** Find Vector and points
*/

t_vec3d				point_vect_sub(t_3point a, t_vec3d b);
t_vec3d				point_vect_add(t_3point a, t_vec3d b);
t_vec3d				point_to_vector(t_3point a, t_3point b);
t_3point			new_3point(double x, double y, double z);
t_3point			point_scalaire(t_3point a, double coeff);
t_3point			cpy_3point(t_3point p);
void				point_vector_scal(t_3point *p, t_vec3d *v, double coef);
double				distance_btw_3points(t_3point a, t_3point b);

/*
** Utils Vector
*/

t_vec2d				new_2dvector(double x, double y);
t_vec3d				new_3dvector(double x, double y, double z);
t_vec3d				cpy_3dvect(t_vec3d v);
t_vec2d				cpy_2dvect(t_vec2d v);

/*
** Transformation Vector
*/

void				vector_rot_x(t_vec3d *y, t_vec3d *z, double angle);
void				vector_rot_y(t_vec3d *z, t_vec3d *x, double angle);
void				vector_rot_z(t_vec3d *x, t_vec3d *y, double angle);
void				ft_rot_z(t_vec3d *x, double angle);
void				ft_rot_x(t_vec3d *y, double angle);
void				ft_rot_y(t_vec3d *z, double angle);

#endif
