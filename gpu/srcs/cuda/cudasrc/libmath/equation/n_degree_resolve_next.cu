extern "C" {
#include "../../../../../includes/rt.h"
#include "../../../cudaheader/gpu_rt.h"
#include <equation.h>
#include <math.h>
}

#pragma hd_warning_disable

__host__ __device__ static void 	swap_double_cuda(double *a, double *b)
{
	double tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

__host__ __device__ static double	calc_poly(double *coef, int degree, double a)
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

__host__ __device__ static double	*get_dcoef(double *dcoef, double *coef,
  int deg)
{
  int		i;

  i = -1;
  while (++i < deg)
    dcoef[i] = coef[i] * (deg - i);
  return (dcoef);
}

__host__ __device__ static void	reduce_coef(double *coef, int *deg)
{
  int		i;

  while (IS_ZERO(coef[0]) && *deg > 1)
    {
      i = -1;
      while (++i < *deg)
	coef[i] = coef[i + 1];
      --(*deg);
    }
}

__host__ __device__ static void	solve_first(double *coef, double *sol)
{
  sol[0] = -MAX_ROOT;
  sol[1] = -coef[1] / coef[0];
  sol[2] = MAX_ROOT;
}

__host__ __device__ static void	solve_second(double *coef, double *sol)
{
  double	det;
  double	opti;

  sol[0] = -MAX_ROOT;
  opti = -2.0 * coef[0];
  det = coef[1] * coef[1] + 2.0 * opti * coef[2];
  if (det == 0.0)
    {
      sol[1] = coef[1] / opti;
      sol[2] = MAX_ROOT;
    }
  else if (det >= 0.0)
    {
      det = sqrt(det);
      sol[1] = (coef[1] - det) / opti;
      sol[2] = (coef[1] + det) / opti;
      if (sol[1] > sol[2])
				swap_double_cuda(sol + 1, sol + 2);
      sol[3] = MAX_ROOT;
    }
  else
    sol[1] = MAX_ROOT;
}

__host__ __device__ static double	loop_dicho(double *coeff, int deg,
    t_dichotomie *d)
{
  int		i;
  double	tmp;

  i = -1;
  while (++i < 1000000)
    {
      if (d->sl == 0 || d->sr == 0)
	return ((d->sl == 0) ? d->l : d->r);
      d->mid = d->l / 2.0 + d->r / 2.0;
      tmp = calc_poly(coeff, deg, d->mid);
      d->smid = SIGNOF(tmp);
      if (fabs(d->l - d->r) < 0.0001 || !d->smid)
	return (d->mid);
      else if (d->sl * d->smid > 0)
	{
	  d->l = d->mid;
	  d->sl = d->smid;
	}
      else
	{
	  d->r = d->mid;
	  d->sr = d->smid;
	}
    }
  return ((d->l + d->r) / 2.0);
}

__host__ __device__ static double		calc_root(double *coeff, int deg, double l,
    double r)
{
  t_dichotomie	d;
  double	tmp;

  d.l = l;
  d.r = r;
  tmp = calc_poly(coeff, deg, l);
  d.sl = SIGNOF(tmp);
  tmp = calc_poly(coeff, deg, r);
  d.sr = SIGNOF(tmp);
  if (d.sl * d.sr > 0)
    return (MAX_ROOT + 1);
  return (loop_dicho(coeff, deg, &d));
}

__host__ __device__ void		  solve_quadra_next(double *coef, double *sol,
    int deg)
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
  solve_quadra_next(dcoef, dsol, deg - 1);
  sol[0] = -MAX_ROOT;
  i = -(j = 1);
  while (++i < deg && dsol[i] != MAX_ROOT)
    if (fabs(tmp = calc_root(coef, deg, dsol[i], dsol[i + 1])) < MAX_ROOT)
      sol[j++] = tmp;
  sol[j] = MAX_ROOT;
}

__host__ __device__ double		solver_quadra(double *coef, int degree)
{
  double	sols[10];
  int		i;

  if (degree < 1)
    return (-1.0);
  i = -1;
  solve_quadra_next(coef, sols, degree);
  while (++i < 10)
    if (sols[i] > 0.0001)
      return ((sols[i] < MAX_ROOT) ? sols[i] : -1.0);
  return (-1.0);
}
