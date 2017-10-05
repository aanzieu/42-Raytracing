/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_utils.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:45:23 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 12:08:09 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
#include "../../../cudaheader/gpu_rt.h"
}

__host__ __device__ int			is_zero(double x)
{
	return(fabs(x) < ZERO_DP ? 1 : 0);
}

__host__ __device__ double		ft_smaller(double a, double b)
{
	return(a <= b ? a : b);
}

__host__ __device__ double		check_solution(double res)
{
	return((res > 0.0) ? res : -1);
}

__host__ __device__ int			dblsgn(double x)
{
	if (x < -EPSILON)
		return (-1);
	return (x > EPSILON);
}

__host__ __device__ void		swap_double(double *a, double *b)
{
	double tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

__host__ __device__ double    clamp(double min, double max, double value)
{
  if (value >= min && value <= max)
    return (value);
  if (value < min)
    return (min);
  return (max);
}
