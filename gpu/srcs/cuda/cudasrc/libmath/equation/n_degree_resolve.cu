extern "C" {
#include "../../../../../includes/rt.h"
#include "../../../cudaheader/gpu_rt.h"
#include <equation.h>
#include <math.h>
}

#define EPSILON (1e-9)

__host__ __device__ void	swap_double(double *a, double *b)
{
	double tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

__host__ __device__ static t_dichotomie	init_stru(double *a)
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

__host__ __device__ static int		solve_second_case(t_dichotomie c, double *a, double *r)
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

__host__ __device__ static int		solve_third_case(t_dichotomie c, double *a, double *r)
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

__host__ __device__ static int		solve_fourth_case(t_dichotomie c, double *a, double *r)
{
	c.ba = -c.sgnbr * pow(fabs(c.br) + sqrt(c.br2 - c.bq3), 1.0 / 3.0);
	c.bb = c.bq / c.ba;
	r[0] = c.ba + c.bb - a[2] / 3;
	return (1);
}

__host__ __device__ int				solve_n(double *a, double *r)
{
	t_dichotomie		c;
	
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

__host__ __device__ int		dblsgn(double x)
{
	if (x < -EPSILON)
		return (-1);
	return (x > EPSILON);
}

__host__ __device__ int	 find_inside(t_mobius m, t_vec3d h)
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
	//define un max pour le mobius
}

__host__ __device__ double		solver_n_degree(double *coef, int degree, t_mobius m, t_ray ray)
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
//			return ((sols[i] < MAX_ROOT) ? sols[i] : -1.0);
		}
	}
	return (INFINITY);
}

/*
__host__ __device__ double	calc_poly(double *coef, int degree, double a)
{
	double	res;
	double	x;
	int		i;

	res = 0;
	x = 1.0;
	i = -1;
	while (++i < degree + 1)
	{
		res += coef[degree - i] * x;
		x *= a;
	}
	return (res);
}

__host__ __device__ static double	*get_dcoef(double *dcoef, double *coef, int deg)
{
	int		i;

	i = -1;
	while (++i < deg)
		dcoef[i] = coef[i] * (deg - i);
	return (dcoef);
}

__host__ __device__ void	reduce_coef(double *coef, int *deg)
{
	int		i;

	while (is_zero(coef[0]) && *deg > 1)
	{
		i = -1;
		while (++i < *deg)
			coef[i] = coef[i + 1];
		--(*deg);
	}
}

__host__ __device__ void		solve_n(double *coef, double *sol, int deg)
{
	double	dcoef[10];
	double	dsol[10];
	int		i;
	int		j;
	double	tmp;

	reduce_coef(coef, &deg);
	if (deg == 1)
		solve_first(coef, sol);
	else if (deg == 2)
		solve_second(coef, sol);
	if (deg < 3)
		return ;
	get_dcoef(dcoef, coef, deg);
	solve_n(dcoef, dsol, deg - 1);
	sol[0] = -MAX_ROOT;
	i = -(j = 1);
	while (++i < deg && dsol[i] != MAX_ROOT)
		if (fabs(tmp = calc_root(coef, deg, dsol[i], dsol[i + 1])) < MAX_ROOT)
			sol[j++] = tmp;
	sol[j] = MAX_ROOT;
}*/
