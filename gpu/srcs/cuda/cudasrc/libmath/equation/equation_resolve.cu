/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_resolve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:32:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/20 11:44:40 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
#include "../../../cudaheader/gpu_rt.h"
}

__host__ __device__ int				solve_second_case(t_dichotomie c, double *a,
									double *r)
{
	c.sqrtbq = sqrt(c.bq);
	if (c.br > 0)
	{
		r[0] = -2 * c.sqrtbq - a[2] / 3;
		r[1] = c.sqrtbq - a[2] / 3;
		r[2] = c.sqrtbq - a[2] / 3;
	}
	else
	{
		r[0] = -c.sqrtbq - a[2] / 3;
		r[1] = -c.sqrtbq - a[2] / 3;
		r[2] = 2 * c.sqrtbq - a[2] / 3;
	}
	return (3);
}

__host__ __device__ int				solve_third_case(t_dichotomie c, double *a,
									double *r)
{
	c.ratio = c.sgnbr * sqrt(c.br2 / c.bq3);
	c.theta = acos(c.ratio);
	c.norm = -2 * sqrt(c.bq);
	c.r0 = c.norm * cos(c.theta / 3) - a[2] / 3;
	c.r1 = c.norm * cos((c.theta + 2.0 * M_PI) / 3) - a[2] / 3;
	c.r2 = c.norm * cos((c.theta - 2.0 * M_PI) / 3) - a[2] / 3;
	if (c.r0 > c.r1)
		swap_double(&c.r0, &c.r1);
	if (c.r1 > c.r2)
	{
		swap_double(&c.r1, &c.r2);
		if (c.r0 > c.r1)
			swap_double(&c.r0, &c.r1);
	}
	r[0] = c.r0;
	r[1] = c.r1;
	r[2] = c.r2;
	return (3);
}

__host__ __device__ int				solve_fourth_case(t_dichotomie c,
									double *a, double *r)
{
	c.ba = -c.sgnbr * pow(fabs(c.br) + sqrt(c.br2 - c.bq3), 1.0 / 3.0);
	c.bb = c.bq / c.ba;
	r[0] = c.ba + c.bb - a[2] / 3;
	return (1);
}

__host__ __device__ static double	check_solution_equation(double a, double b)
{
	if (a > 0.0000000001 && b > 0.0000000001)
		return (ft_smaller(a, b));
	else if (a > 0.0000000001)
		return (a);
	else if (b > 0.0000000001)
		return (b);
	return (-1.0);
}

__host__ __device__ void			second_degres(t_eq *eq)
{
	t_solve s;

	s.det = eq->b * eq->b - 4.0 * eq->a * eq->c;
	if (is_zero(s.det))
	{
		eq->res[0] = -1.0 * eq->b / (2.0 * eq->a);
		eq->res[0] = check_solution(s.res);
		eq->res[1] = eq->res[0];
		eq->res[2] = eq->res[0];
 	}
	else if (s.det >= 0.0)
	{
		s.tmp[0] = ((-1) * eq->b + sqrt(s.det)) / (2 * eq->a);
		s.tmp[1] = ((-1) * eq->b - sqrt(s.det)) / (2 * eq->a);
		s.tmp[0] = check_solution(s.tmp[0]);
		s.tmp[1] = check_solution(s.tmp[1]);
		eq->res[0] = check_solution_equation(s.tmp[0], s.tmp[1]);
		eq->res[1] = eq->res[0] == s.tmp[0] ? s.tmp[1] : s.tmp[0];
	}
	else
		eq->res[0] = NOT_A_SOLUTION;
}
