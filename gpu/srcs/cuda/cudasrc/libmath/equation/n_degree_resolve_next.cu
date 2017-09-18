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

__host__ __device__ void	set_pqr_quartic(double *pqr, double *coef)
{
  pqr[0] = -3.0 * (coef[1] * coef[1]) / (8.0 * coef[0] * coef[0])
    + (coef[2] / coef[0]);
  pqr[1] = (pow(coef[1] / 2.0, 3) / pow(coef[0], 3))
    - (0.5 * coef[1] * coef[2])
    / pow(coef[0], 2) + coef[3] / coef[0];
  pqr[2] = -3.0 * pow((coef[1] / 4.0) / coef[0], 4)
    + coef[2] * (pow(coef[1] / 4.0, 2) / pow(coef[0], 3))
    - ((0.25 * coef[1] * coef[3]) / (coef[0] * coef[0]))
    + (coef[4] / coef[0]);
}

__host__ __device__ void	init_to_send_cubic(double p, double q,
			   double r, double *coef)
{
  coef[0] = 8.0;
  coef[1] = -4.0 * p;
  coef[2] = -8.0 * r;
  coef[3] = 4.0 * r * p - q * q;
}

__host__ __device__ int		init_and_send_second(double *pqr, double y0, double *res)
{
  double	a0;
  double	b0;
  double	coef[3];
  int		nb_sol;

  nb_sol = 0;
  a0 = sqrt(-pqr[0] + 2.0 * y0);
  if ((2.0 * y0 - pqr[0]) != 0.0)
    b0 = -pqr[1] / (2.0 * a0);
  else
    b0 = sqrt(y0 * y0 - pqr[2]);
  coef[0] = 1.0;
  coef[1] = -a0;
  coef[2] = y0 - b0;
  nb_sol = solve_quadratic(coef, res);
  coef[0] = 1.0;
  coef[1] = a0;
  coef[2] = y0 + b0;
  nb_sol += solve_quadratic(coef, &(res[nb_sol]));
  return (nb_sol);
}

__host__ __device__ int		solve_quartic(double *coef, double *res)
{
  double	pqr[3];
  double	coef_tmp[4];
  double	res_tmp[3];
  int		nb_sol;
  int		count;

  count = 0;
  nb_sol = 0;
  if (fabs(coef[0]) <= SURFACE_TOLERANCE)
    return (solve_cubic(&(coef[1]), res));
  set_pqr_quartic(pqr, coef);
  init_to_send_cubic(pqr[0], pqr[1], pqr[2], coef_tmp);
  if (solve_cubic(coef_tmp, res_tmp) == 0)
    return (0);
  nb_sol = init_and_send_second(pqr, res_tmp[0], res);
  while (count < nb_sol)
    res[count++] -= coef[1] / (4.0 * coef[0]);
  return (nb_sol);
}
