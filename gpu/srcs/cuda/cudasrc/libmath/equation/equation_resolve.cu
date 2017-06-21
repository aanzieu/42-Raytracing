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
#include <rt.h>
#include <gpu_rt.h>
#include <equation.h>
}

__host__ __device__ inline double		ft_smaller(double a, double b)
{
	return(a < b ? a : b);
}

__host__ __device__ inline double		check_solution(double res)
{
	return((res > 0.0) ? res : -1);
}

__host__ __device__ double		check_solution_equation(double a, double b)
{
	if (a > 0.0 && b > 0.0)
		return (ft_smaller(a, b));
	else if (a > 0.0)
		return (a);
	else if (b > 0.0)
		return (b);
	return (-1.0);
}
__host__ __device__ int		is_zero(double x)
{
	return(fabs(x) < ZERO_DP ? 1 : 0);
}
__host__ __device__ double		second_degres(double a, double b, double c)
{
//	double	res;
//	double	det;
//	double	tmp[4];
	t_solve s;

	s.det = b * b - 4.0 * a * c;
//	else if (det > 0.0)
	if (is_zero(s.det))
	{
		s.res = -1.0 * b / (2.0 * a);
		s.res = check_solution(s.res);
	}
	else if (s.det > 0.0)
	{
		s.tmp[0] = ((-1) * b + sqrt(s.det)) / (2 * a);
		s.tmp[1] = ((-1) * b - sqrt(s.det)) / (2 * a);
		s.tmp[0] = check_solution(s.tmp[0]);
		s.tmp[1] = check_solution(s.tmp[1]);
		s.res = check_solution_equation(s.tmp[0], s.tmp[1]);
	}
	else
		s.res = NOT_A_SOLUTION;//-1;
	return (s.res);
/*
	t_solve s;
	s.det = b * b - 4.0 * a * c;
	if (ZERO(s.det))
	{
		s.res = -1.0 * b / (2.0 * a);
		s.res = check_solution(s.res);
	}
	else if (s.det > 0.0)
	{
		s.tmp[2] = sqrt(s.det);
		s.tmp[3] = 2.0 * a;
		s.tmp[0] = -(b - s.tmp[2]) / s.tmp[3];
		s.tmp[1] = -(b + s.tmp[2]) / s.tmp[3];
		s.tmp[0] = check_solution(s.tmp[0]);
		s.tmp[1] = check_solution(s.tmp[1]);
		s.res = check_solution_equation(s.tmp[0], s.tmp[1]);
	}
	else
		s.res = NOT_A_SOLUTION;
	return (s.res);
	*/
}
