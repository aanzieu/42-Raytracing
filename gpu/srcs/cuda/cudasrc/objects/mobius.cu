
extern "C" {
#include "../../../../includes/rt.h"
#include "../../cudaheader/gpu_rt.h"
#include <vectors.h>
#include <equation.h>
#include <float.h>
}

__host__ __device__ static void			get_normal_mobius(t_intersection *inter, t_mobius m, t_ray ray)
{

//	t_vec3d       	dt;
//	t_vec3d       	dv;
//	double			v;
//	double			t;

//	v = atan(inter->pos.y / inter->pos.x);
//	t = (2.0 * inter->pos.z) / sin((v / 2.0));
//	if (!(v > 0 && v < 2 * M_PI && t >= -1.0 && t <= 1.0))
//		inter->t = -1;//INFINITY;
//	dt.x = (1.0 / 2.0) * cos(v) * cos(v / 2.0);
//	dt.y = (1.0 / 2.0) * sin(v) * cos(v / 2.0);
//	dt.z = (1.0 / 2.0) * sin(v / 2.0);
//	dv.y = -sin(v) - (t / 2.0) * sin(v) * cos(v / 2.0) - (t / 4.0) * cos(v) *
//		sin(v / 2);
//	dv.y = cos(v) + (t / 2.0) * cos(v) * cos(v / 2.0) - (t / 4.0) * sin(v) *
//		sin(v / 2);
//	dv.z = (t / 4.0) * cos(v / 2.0);
//	inter->normal_v.x = dt.y * dv.z - dt.z * dv.y;
//	inter->normal_v.y = dt.z * dv.x - dt.x * dv.z;
//	inter->normal_v.z = dt.x * dv.y - dt.y * dv.x;
		t_vec3d real;
		t_vec3d ret;

		real = vector_substract(inter->pos, m.pos);
		ret.x = -2 * m.radius * real.z + 2 * real.x * real.y - 4 * real.x * real.z;
		ret.y = -(m.radius * m.radius) + real.x * real.x + 3 * real.y * real.y - 4 * real.y * real.z + real.z * real.z;
		ret.z = -2 * m.radius * real.x - 2 * real.x * real.x - 2 * real.y * real.y + 2 * real.y * real.z;
		inter->normal_v = vector_normalize(ret);//inter->normal_v);
}

/*
 **	On envoie le rayon et la structure qui contient la sphere et la fonction
 **	ecrit sur 't_vec3d *intersection' les coordonees du point d'intersection
 **	avec la sphere
 */

__host__ __device__ static int			get_mobius(t_mobius m, t_ray ray, t_intersection *intersection_tmp)
{
	double	s[4];
	double  res;
	double	 a = m.radius;
	double	 b = ray.origin.x;
	double c = ray.dir.x;
	double d = ray.origin.y;
	double e = ray.dir.y;
	double f = ray.origin.z;
	double g = ray.dir.z;

	s[3] = c * c * e + e * e * e - 2 * c * c * g - 2 * e * e * g + e * g * g;
	s[0] = (b * b * d + d * d * d - 2 * b * b * f - 2 * d * d * f + d * f * f - 2 * b * f * a - d * a * a) / s[3];
	s[1] = (e * b * b - 2 * g * b * b + 2 * c * b * d + 3 * e * d * d - 2 * g * d * d - 4 * c * b * f - 4 * e * d * f + 2 * g * d * f + e * f * f - 2 * g * b * a - 2 * c * f * a - e * a * a) / s[3];
	s[2] = (2 * c * e * b - 4 * c * g * b + c * c * d + 3 * e * e * d - 4 * e * g * d + g * g * d - 2 * c * c * f - 2 * e * e * f + 2 * e * g * f - 2 * c * g * a) / s[3];

	res = solver_n_degree(s, 4, m, ray);
	if(res != NOT_A_SOLUTION)
	{
		intersection_tmp->t = res;
		intersection_tmp->type = 'm';
		return(1);
	}
	intersection_tmp->t = -1.0;
	return(0);
}



__host__ __device__ void	get_closest_mobius(t_world world, t_ray ray,
		t_intersection *intersection, t_intersection *intersection_tmp)
{
	int i;

	i = 0;
	while (i < world.mobius_len)
	{
//		printf("%lf posx \n", world.mobius[i].reflexion_coef);
		if(get_mobius(world.mobius[i], ray, intersection_tmp) == 1)
		{
			if (intersection_tmp->t < intersection->t && intersection_tmp->t != -1)
			{
				intersection->pos = vector_add(ray.origin,
						vector_scalar(ray.dir, intersection_tmp->t));
				intersection->t = intersection_tmp->t;
				intersection->type = intersection_tmp->type;
				intersection->reflexion_coef = world.mobius[i].reflexion_coef;
				intersection->color = &world.mobius[i].color;
			//	if(intersection->t != INFINITY)
				get_normal_mobius(intersection, world.mobius[i], ray);
			}
		}
		//	else
		//			intersection->t = INFINITY;
		i++;
	}
}
