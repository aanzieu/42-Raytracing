// extern "C" {
// #include <../../../../../includes/rt.h>
// #include <../../../cudaheader/gpu_rt.h>
// #include <equation.h>
// #include <math.h>
// }
//
// #define	MAXPOS 100000000000000.0
//
// __host__ __device__ static void	third_degree_calc_trigo(t_solve s)
// {
//   double	k;
//
// 	s.trigo[0] = sqrt(((s.val[1] * s.val[1]) / 4.0) - s.val[2]);
// 	k = (s.trigo[0] < 0) ? -1 : 1;
// 	s.trigo[1] = pow(s.trigo[0] * k, (1.0 / 3.0)) * k;
// 	s.trigo[2] = (acos((-s.val[1]) / (2.0 * (s.trigo[0])))) / 3.0;
// }
//
// __host__ __device__ static void	third_degree_calc_tmp(double *tmp, double rc, double theta, double val)
// {
// 	tmp[0] = rc;
// 	tmp[1] = cos(theta);
// 	tmp[2] = sqrt(3.0) * sin(theta);
// 	tmp[3] = val * -1.0;
// }
//
// __host__ __device__ static void third_degree_round(double *x, double *tmp, double val)
// {
// 	x[1] = (tmp[0] * (tmp[1] + tmp[2])) - val;
// 	x[2] = (tmp[0] * (tmp[1] - tmp[2])) - val;
// 	x[0] = check_solution(round(x[0] * MAXPOS) / MAXPOS);
// 	x[1] = check_solution(round(x[1] * MAXPOS) / MAXPOS);
// 	x[2] = check_solution(round(x[2] * MAXPOS) / MAXPOS);
// 	x[1] = check_solution_equation(x[1], x[2]);
// }
//
// __host__ __device__ static double	third_degree_neg(double g, double h, double val)
// {
// 	double	m[2];
// 	double	n[2];
// 	double	k;
//
// 	m[0] = (-g / 2.0) + sqrt(h);
// 	k = (m[0] < 0) ? -1 : 1;
// 	m[1] = pow(m[0] * k, val) * k;
// 	n[0] = (-g / 2.0) - sqrt(h);
// 	k = (n[0] < 0) ? -1 : 1;
// 	n[1] = pow(n[0] * k, val) * k;
// 	return (n[1] + m[1]);
// }
//
// __host__ __device__ double		third_degree(double a, double b, double c, double d)
// {
// 	t_solve s;
//
// 	s.val[0] = (((3.0 * c) / a) - (((b * b) / (a * a)))) / 3.0;
// 	s.val[1] = ((2.0 * ((b * b * b) / (a * a * a))) - ((9.0 * b * c) / (a * a)) + ((27.0 * (d / a)))) / 27.0;
// 	s.val[2] = ((s.val[1] * s.val[1]) / 4.0) + ((s.val[0] * s.val[0] * s.val[0]) / 27.0);
// 	if (s.val[2] > 0)
// 	s.x[0] = s.x[1] = s.x[2] = (third_degree_neg(s.val[1], s.val[2], (1.0 / 3.0))) - (b / (3.0 * a));
// 	else
// 	{
// 		third_degree_calc_trigo(s);
// 		s.x[0] = (2.0 * (s.trigo[1] * cos(s.trigo[2]))) - (b / (3.0 * a));
// 		third_degree_calc_tmp(s.tmp, -1 * s.trigo[1], s.trigo[2], (b / (3.0 * a)));
// 		third_degree_round(s.x, s.tmp, (b / (3.0 * a)));
// 	}
// 	if (is_zero(s.val[0] + s.val[1] + s.val[2]))
// 		s.x[0] = s.x[1] = s.x[2] = (d < 0) ? pow(d / a, (1.0 / 3.0)) * -1 :
// 	pow((-d) / a, (1.0 / 3.0));
// 	return (check_solution_equation(check_solution(s.x[0]), check_solution(s.x[1])));
// }
