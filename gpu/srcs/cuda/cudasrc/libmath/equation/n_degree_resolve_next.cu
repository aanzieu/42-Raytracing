// extern "C" {
// #include "../../../../../includes/rt.h"
// #include "../../../cudaheader/gpu_rt.h"
// #include <equation.h>
// #include <math.h>
// }
// /*
// __host__ __device__ void	solve_first(double *coef, double *sol)
// {
// 	sol[0] = -MAX_ROOT;
// 	sol[1] = -coef[1] / coef[0];
// 	sol[2] = MAX_ROOT;
// }
// __host__ __device__ void	swap_double(double *a, double *b)
// {
// 	double tmp;
// 	tmp = *a;
// 	*a = *b;
// 	*b = tmp;
// }
//
// __host__ __device__ void	solve_second(double *coef, double *sol)
// {
// 	double	det;
// 	double	opti;
//
// 	sol[0] = -MAX_ROOT;
// 	opti = -2.0 * coef[0];
// 	det = coef[1] * coef[1] + 2.0 * opti * coef[2];
// 	if (det == 0.0)
// 	{
// 		sol[1] = coef[1] / opti;
// 		sol[2] = MAX_ROOT;
// 	}
// 	else if (det >= 0.0)
// 	{
// 		det = sqrt(det);
// 		sol[1] = (coef[1] - det) / opti;
// 		sol[2] = (coef[1] + det) / opti;
// 		if (sol[1] > sol[2])
// 			swap_double(sol + 1, sol + 2);
// 		sol[3] = MAX_ROOT;
// 	}
// 	else
// 		sol[1] = MAX_ROOT;
// }
//
// __host__ __device__ static double	loop_dicho(double *coeff, int deg, t_dichotomie *d)
// {
// 	int		i;
// 	double	tmp;
//
// 	i = -1;
// 	while (++i < 1000000)
// 	{
// 		if (d->sl == 0 || d->sr == 0)
// 			return ((d->sl == 0) ? d->l : d->r);
// 		d->mid = d->l / 2.0 + d->r / 2.0;
// 		tmp = calc_poly(coeff, deg, d->mid);
// 		d->smid = SIGNOF(tmp);
// 		if (fabs(d->l - d->r) < 0.0001 || !d->smid)
// 			return (d->mid);
// 		else if (d->sl * d->smid > 0)
// 		{
// 			d->l = d->mid;
// 			d->sl = d->smid;
// 		}
// 		else
// 		{
// 			d->r = d->mid;
// 			d->sr = d->smid;
// 		}
// 	}
// 	return ((d->l + d->r) / 2.0);
// }
//
// __host__ __device__ double		calc_root(double *coeff, int deg, double l, double r)
// {
// 	t_dichotomie d;
// 	double	tmp;
//
// 	d.l = l;
// 	d.r = r;
// 	tmp = calc_poly(coeff, deg, l);
// 	d.sl = SIGNOF(tmp);
// 	tmp = calc_poly(coeff, deg, r);
// 	d.sr = SIGNOF(tmp);
// 	if (d.sl * d.sr > 0)
// 		return (MAX_ROOT + 1);
// 	return (loop_dicho(coeff, deg, &d));
// }*/
