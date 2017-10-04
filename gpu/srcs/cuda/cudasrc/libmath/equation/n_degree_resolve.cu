/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_degree_resolve.cu                                :+:      :+:    :+:   */
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

__host__ __device__ static t_dichotomie		init_stru(double *a)
{
	t_dichotomie	ret;

	ret.q = a[2] * a[2] - 3 * a[1];
	ret.r = 2 * a[2] * a[2] * a[2] - 9 * a[2] * a[1] + 27 * a[0];
	ret.bq = ret.q / 9;
	ret.br = ret.r / 54;
	ret.bq3 = ret.bq * ret.bq * ret.bq;
	ret.br2 = ret.br * ret.br;
	ret.cr2 = 729 * ret.r * ret.r;
	ret.cq3 = 2916 * ret.q * ret.q * ret.q;
	ret.sgnbr = ret.br >= 0 ? 1 : -1;
	ret.i = 0;
	return (ret);
}

__host__ __device__ static int				solve_n(double *a, double *r)
{
	t_dichotomie	c;

	c = init_stru(a);
	if (c.br == 0 && c.bq == 0)
	{
		while (c.i++ < 3)
			r[c.i] = -a[2] / 3;
		return (3);
	}
	else if (c.cr2 == c.cq3)
		return (solve_second_case(c, a, r));
	else if (c.br2 < c.bq3)
		return (solve_third_case(c, a, r));
	else
		return (solve_fourth_case(c, a, r));
}

__host__ __device__ static int				find_inside(t_mobius m, t_vec3d h)
{
	double t;
	double s;

	t = atan2(h.y, h.x);
	if (dblsgn(sin(t / 2)) != 0)
		s = h.z / sin(t / 2);
	else
		s = dblsgn(cos(t)) ? (h.x / cos(t) - m.radius) / cos(t / 2) :
			(h.y / sin(t) - m.radius) / cos(t / 2);
	h.x -= (m.radius + s * cos(t / 2)) * cos(t);
	h.y -= (m.radius + s * cos(t / 2)) * sin(t);
	h.z -= s * sin(t / 2);
	if (dblsgn(h.x * h.x + h.y * h.y + h.z * h.z))
		return (0);
	return (s >= -0.5 && s <= 0.5);
}

__host__ __device__ double				solver_n_degree(double *coef,
		int degree, t_mobius m, t_ray ray)
{
	double	sols[3];
	int		i;
	int		ret;
	t_vec3d hit;

	if (degree < 1)
		return (-1.0);
	i = -1;
	ret = solve_n(coef, sols);
	while (++i < ret)
	{
		if (sols[i] > EPSILON)
		{
			hit = vector_add(vector_scalar(ray.dir, sols[i]), ray.origin);
			if (find_inside(m, hit))
				return (sols[i]);
		}
	}
	return (INFINITY);
}
