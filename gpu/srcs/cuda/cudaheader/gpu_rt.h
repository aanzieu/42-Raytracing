#ifndef CUDA_MD_H
# define CUDA_MD_H
#ifndef CUDA_HOSTDEV
# ifdef __CUDA_ARCH__
# define CUDA_HOSTDEV __host__ __device__
# else
# define CUDA_HOSTDEV
# endif
#endif

#include <../../../includes/vectors.h>
#include <../../../includes/object.h>
#include <../../../includes/equation.h>
#include <../../../includes/rt.h>

/*******************************************************************************
**                     INTERSECTION_FONCTION_GET                              **
*******************************************************************************/

CUDA_HOSTDEV double		get_closest_intersection(t_world world, t_ray ray,
						t_intersection *intersection);
CUDA_HOSTDEV void		get_closest_sphere(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_mobius(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_plane(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_cone(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_cylinder(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_paraboloid(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_disk(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV int		get_plane(t_plane plane, t_ray ray,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV double		get_sphere(t_sphere sphere, t_ray ray,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV int		get_disk(t_disk disk, t_ray ray,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_hyperboloid(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_torus(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_triangle(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);

/*******************************************************************************
**                     COLOR_FCTS                                             **
*******************************************************************************/

CUDA_HOSTDEV t_color		color_multiply(t_color c1, t_color c2);
CUDA_HOSTDEV t_color		color_scalar(t_color c1, double coef);
CUDA_HOSTDEV t_color		color_add(t_color c1, t_color c2);
CUDA_HOSTDEV t_color		new_color(double r, double g, double b);
CUDA_HOSTDEV int				get_color(t_color color);

/*******************************************************************************
**                     LIGHTS_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV int		get_shadow(t_light light, t_intersection collision);
CUDA_HOSTDEV t_color	get_light_at(t_world world, t_color color, t_light light,
	t_intersection intersection, t_ray ray);

/*******************************************************************************
**                     CAMERA_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV void		move_forward(t_world *world);
CUDA_HOSTDEV void		move_backward(t_world *world);
CUDA_HOSTDEV void		move_left(t_world *world);
CUDA_HOSTDEV void		move_right(t_world *world);
CUDA_HOSTDEV void		cam_rot(t_camera *camera, double degrees, char axis);
CUDA_HOSTDEV void		get_camera_axes(t_camera *camera);

/*******************************************************************************
**                     VECTOR_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV void		rotate(t_vec3d *point, double degrees, char axis);
CUDA_HOSTDEV void		translate(t_vec3d *point, double x, double y, double z);
CUDA_HOSTDEV t_vec3d	new_vector(double x, double y, double z);
CUDA_HOSTDEV t_vec3d	vector_copy(t_vec3d cpy);
CUDA_HOSTDEV t_vec3d	vector_add(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_substract(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_cross(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_scalar(t_vec3d vect1, double scalar);
CUDA_HOSTDEV t_vec3d	vector_calculate(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_normalize(t_vec3d vect1);
CUDA_HOSTDEV double		vector_dot(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV double		vector_length(t_vec3d vect1);
CUDA_HOSTDEV double		vector_magnitude(t_vec3d vect1);

/*******************************************************************************
**                     MATH_UTILS                                             **
*******************************************************************************/

CUDA_HOSTDEV int		dblsgn(double x);
CUDA_HOSTDEV int		is_zero(double x);
CUDA_HOSTDEV void		swap_double(double *a, double *b);
CUDA_HOSTDEV double		ft_smaller(double a, double b);
CUDA_HOSTDEV double		sign_of(double a);
CUDA_HOSTDEV double		check_solution(double res);

/*******************************************************************************
**                     MATH_FCTS                                              **
*******************************************************************************/

CUDA_HOSTDEV double		deg_to_radians(double deg);
CUDA_HOSTDEV void		second_degres(t_eq *eq);
CUDA_HOSTDEV int		solve_fourth_case(t_dichotomie c, double *a, double *r);
CUDA_HOSTDEV int		solve_third_case(t_dichotomie c, double *a, double *r);
CUDA_HOSTDEV int		solve_second_case(t_dichotomie c, double *a, double *r);
CUDA_HOSTDEV double		solver_n_degree(double *coef, int degree, t_mobius m,
						t_ray ray);
CUDA_HOSTDEV double		solver_quadra(double *coef, int degree);

/*******************************************************************************
**                     TEXTURES_FCTS                                          **
*******************************************************************************/

CUDA_HOSTDEV t_color apply_materials(t_world world, t_ray ray,
	t_intersection intersection);
CUDA_HOSTDEV t_color 	handle_reflection(t_world world, t_ray ray,
	t_intersection *intersection);
CUDA_HOSTDEV t_color 	handle_refraction(t_world world,
	t_ray ray, t_intersection *intersection);
CUDA_HOSTDEV t_color 	handle_transparence(t_world world,
	t_ray ray, t_intersection *intersection);
CUDA_HOSTDEV t_color	handle_chess(t_ray ray, t_intersection *intersection);

/*******************************************************************************
**                     RAYTRACERS_FCTS                                        **
*******************************************************************************/
CUDA_HOSTDEV void			get_up_left(t_world *world);
CUDA_HOSTDEV t_color	ray_tracer_depth(t_world world, t_ray ray,
	t_intersection intersection);
CUDA_HOSTDEV int		ray_tracer(t_world world, int x, int y);

#endif
