extern "C" {
#include "../../../../../includes/rt.h"
#include "../../../cudaheader/gpu_rt.h"
#include <equation.h>
#include <math.h>
}

__host__ __device__ void	delta_neg(double p, double q, double *res, double trans)
{
  int	nb_sol;

  nb_sol = 0;
  while (nb_sol <= 2)
    {
      res[nb_sol] = (2.0 * sqrt(- p / 3.0)
		     * cos((1.0 / 3.0)
			   * acos((-q / 2.0)
				  * sqrt(27.0 / (- p * p * p)))
			   + (2.0 * nb_sol * M_PI) / 3.0)) - trans;
      nb_sol++;
    }
}

__host__ __device__ int		cardan_method(double p, double q, double *res, double trans)
{
  double	delta;

  delta = q * q + (4.0 / 27.0) * p * p * p;
  if (delta > 0)
    {
      res[0] = (cbrt((-q + sqrt(delta)) / 2.0)
		+ cbrt((-q - sqrt(delta)) / 2.0)) - trans;
      return (1);
    }
  if (delta == 0.0)
    {
      res[0] = ((3.0 * q) / p) - trans;
      res[1] = ((-3.0 * q) / (2.0 * p)) - trans;
      return (2);
    }
  if (delta < 0.0)
    {
      delta_neg(p, q, res, trans);
      return (3);
    }
  return (0);
}

__host__ __device__ int		solve_quadratic(double *coef, double *res)
{
  double	delta;
  double	k;
  int		nb_sol;

  nb_sol = 0;
  delta = coef[1] * coef[1] - 4 * coef[0] * coef[2];
  if (delta < 0.0)
    return (0);
  if (delta >= 0.0)
    {
      k = (-coef[1] + sqrt(delta)) / (2 * coef[0]);
      res[nb_sol++] = k;
    }
  if (delta > 0.0)
    {
      k = (-coef[1] - sqrt(delta)) / (2 * coef[0]);
      res[nb_sol++] = k;
    }
  return (nb_sol);
}

__host__ __device__ int		solve_cubic(double *coef, double *res)
{
  double	p;
  double	q;

  if (fabs(coef[0]) <= SURFACE_TOLERANCE)
    return (solve_quadratic(&(coef[1]), res));
  p = -((coef[1] * coef[1]) / (3.0 * coef[0] * coef[0]))
    + (coef[2] / coef[0]);
  q = (coef[1] / (27.0 * coef[0])) *
    ((2.0 * coef[1] * coef[1]) / (coef[0] * coef[0]) -
     (9.0 * coef[2]) / coef[0]) + coef[3] / coef[0];
  return (cardan_method(p, q, res, coef[1] / (3.0 * coef[0])));
}
