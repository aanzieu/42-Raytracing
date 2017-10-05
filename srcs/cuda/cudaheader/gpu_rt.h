/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_rt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 12:17:45 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/05 14:59:04 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUDA_MD_H
# define CUDA_MD_H
#  ifndef CUDA_HOSTDEV
#   ifdef __CUDA_ARCH__
#    define CUDA_HOSTDEV __host__ __device__
#   else
#    define CUDA_HOSTDEV
#   endif
# endif

# include <../../../includes/vectors.h>
# include <../../../includes/object.h>
# include <../../../includes/equation.h>
# include <../../../includes/rt.h>

# define MAX_DEPTH_GPU		4
# define SURFACE_TOLERANCE	0.00000001

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
CUDA_HOSTDEV double		get_sphere(t_world world, t_sphere sphere, t_ray ray,
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
CUDA_HOSTDEV void		get_closest_cube(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV int		get_cube(t_cube cu, t_ray ray,
						t_intersection *intersection_tmp);
CUDA_HOSTDEV void		get_closest_hollow_cube(t_world world, t_ray ray,
						t_intersection *intersection,
						t_intersection *intersection_tmp);

/*******************************************************************************
**                     COLOR_FCTS                                             **
*******************************************************************************/

CUDA_HOSTDEV t_color 	color_divide(t_color color, int quo);
CUDA_HOSTDEV t_color	color_multiply(t_color c1, t_color c2);
CUDA_HOSTDEV t_color	color_scalar(t_color c1, double coef);
CUDA_HOSTDEV t_color	color_divide(t_color c1, int coef);
CUDA_HOSTDEV t_color	color_add(t_color c1, t_color c2);
CUDA_HOSTDEV t_color	new_color(double r, double g, double b);
CUDA_HOSTDEV int		get_color(t_color color);
CUDA_HOSTDEV t_color	int_to_rgb(int color);
CUDA_HOSTDEV int		rgb_to_int(t_color color);

/*******************************************************************************
**                     LIGHTS_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV double		get_shadow(t_light light, t_intersection collision);
CUDA_HOSTDEV t_color	get_light_at(t_world world, t_color color,
						t_light light, t_intersection intersection, t_ray ray);

/*******************************************************************************
**                     CAMERA_FCTS                                            **
*******************************************************************************/
CUDA_HOSTDEV void		move_forward(t_world *world);
CUDA_HOSTDEV void		move_backward(t_world *world);
CUDA_HOSTDEV void		move_left(t_world *world);
CUDA_HOSTDEV void		move_right(t_world *world);
CUDA_HOSTDEV void		move_up(t_world *world);
CUDA_HOSTDEV void		move_down(t_world *world);
CUDA_HOSTDEV void		cam_rot(t_camera *camera, double degrees, char axis);
CUDA_HOSTDEV void		get_camera_axes(t_camera *camera);

/*******************************************************************************
**                     VECTOR_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV void		rotate(t_vec3d *point, double degrees, char axis);
CUDA_HOSTDEV void		translate(t_vec3d *point, double x,
						double y, double z);
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
CUDA_HOSTDEV void		vector_rot_y(t_vec3d *z, t_vec3d *x, double angle);
CUDA_HOSTDEV void		vector_rot_x(t_vec3d *y, t_vec3d *z, double angle);
CUDA_HOSTDEV void		vector_rot_z(t_vec3d *x, t_vec3d *y, double angle);

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
**                     MATH_UTILS                                             **
*******************************************************************************/

CUDA_HOSTDEV int		dblsgn(double x);
CUDA_HOSTDEV int		is_zero(double x);
CUDA_HOSTDEV double		ft_smaller(double a, double b);
CUDA_HOSTDEV double		sign_of(double a);
CUDA_HOSTDEV double		check_solution(double res);
CUDA_HOSTDEV double		clamp(double min, double max, double value);

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
CUDA_HOSTDEV void		delta_neg(double p, double q, double *res,
						double trans);
CUDA_HOSTDEV int		cardan_method(double p, double q, double *res,
						double trans);
CUDA_HOSTDEV int		solve_quadratic(double *coef, double *res);
CUDA_HOSTDEV int		solve_cubic(double *coef, double *res);
CUDA_HOSTDEV void		set_pqr_quartic(double *pqr, double *coef);
CUDA_HOSTDEV void		init_to_send_cubic(double p, double q, double r,
						double *coef);
CUDA_HOSTDEV int		init_and_send_second(double *pqr, double y0,
						double *res);
CUDA_HOSTDEV int		solve_quartic(double *coef, double *res);

/*******************************************************************************
**                     TEXTURES_CPU_FCTS                                      **
*******************************************************************************/

CUDA_HOSTDEV t_color	apply_materials_cpu(t_world world, t_ray ray,
						t_intersection intersection, t_color color);
CUDA_HOSTDEV t_color 	handle_reflection_cpu(t_world world, t_ray ray,
						t_intersection *intersection);
CUDA_HOSTDEV t_color 	handle_refraction_cpu(t_world world,
						t_ray ray, t_intersection *intersection);
CUDA_HOSTDEV t_color 	handle_transparence_cpu(t_world world,
						t_ray ray, t_intersection *intersection);
CUDA_HOSTDEV t_color 	load_texture_at(t_texture texture, t_ray ray,
						t_intersection *intersection, t_world world);

/*******************************************************************************
**                     TEXTURES_GPU_FCTS                                      **
*******************************************************************************/

CUDA_HOSTDEV t_color	apply_materials_gpu(t_world world, t_ray ray,
						t_intersection intersection, t_color color);
CUDA_HOSTDEV t_color	handle_reflection_gpu(t_world world, t_ray *ray,
						t_intersection *intersection, int *flag);
CUDA_HOSTDEV t_color	handle_refraction_gpu(t_world world,
						t_ray *ray, t_intersection *intersection, int *flag);
CUDA_HOSTDEV t_color	handle_transparence_gpu(t_world world,
						t_ray *ray, t_intersection *intersection, int *flag);
CUDA_HOSTDEV t_color	handle_chess(t_ray ray, t_intersection intersection);

/*******************************************************************************
**                     RAYTRACER_CPU_FCTS                                     **
*******************************************************************************/

CUDA_HOSTDEV void 		new_intersection(t_intersection *new_i);
CUDA_HOSTDEV void		get_up_left(t_world *world);
CUDA_HOSTDEV int		ray_tracer_cpu(t_world world, int x, int y);
CUDA_HOSTDEV t_color	ray_tracer_depth_cpu(t_world world, t_ray ray,
						t_intersection intersection);

/*******************************************************************************
**                     RAYTRACER_GPU_FCTS                                     **
*******************************************************************************/

CUDA_HOSTDEV int		ray_tracer_gpu(t_world world, int x, int y);
CUDA_HOSTDEV t_color	ray_tracer_depth_gpu(t_world world, t_ray ray,
						t_intersection intersection);
CUDA_HOSTDEV void		get_ray_direction(t_world world, t_ray *ray,
						int x, int y);

/*******************************************************************************
**                     RAYTRACER_UTILS_FCTS        	                          **
*******************************************************************************/

CUDA_HOSTDEV void		perlin_noise_setup(t_world *world);
CUDA_HOSTDEV void		cartoon_effect(t_world world, t_color *color,
						t_intersection intersection, t_ray ray);
CUDA_HOSTDEV int		get_light_box(t_light light,
						t_intersection intersection, t_ray ray);

/*******************************************************************************
**                     PERLIN_NOISE_FCTS                                      **
*******************************************************************************/

CUDA_HOSTDEV double		apply_noise(t_world world, double x, double y,
						double z, int *p);
CUDA_HOSTDEV t_vec3d	normal_perturbation(t_world world, t_vec3d normal,
						t_vec3d intersection_pos, t_perlin perlin, int *p);

/*******************************************************************************
**                     PERLIN_PRESETS_FCTS                                    **
*******************************************************************************/

CUDA_HOSTDEV void		apply_noise_dist(t_world world,\
						t_intersection *intersection, t_perlin perlin);

#endif
