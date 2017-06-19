#ifndef CUDA_MD_H
# define CUDA_MD_H
#ifndef CUDA_HOSTDEV
# ifdef __CUDA_ARCH__
# define CUDA_HOSTDEV __host__ __device__
# else
# define CUDA_HOSTDEV
# endif
#endif

#include <vectors.h>
#include <object.h>
#include <rt.h>

/*******************************************************************************
**                     INTERSECTION_FONCTION_GET                              **
*******************************************************************************/

CUDA_HOSTDEV double		get_closest_intersection(t_world world, t_ray ray,
						t_intersection *intersection);
CUDA_HOSTDEV void		get_closest_sphere(t_world world, t_ray ray,
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

/*******************************************************************************
**                     OBJECT_GET                                             **
*******************************************************************************/


/*******************************************************************************
**                     COLOR_FCTS                                             **
*******************************************************************************/

CUDA_HOSTDEV void		color_multiply(t_color *color1, t_color color2);
CUDA_HOSTDEV void		color_scalar(t_color *color, double coeficient);
CUDA_HOSTDEV void		color_add(t_color *color1, t_color color2);
CUDA_HOSTDEV int		get_color(double r, double g, double b);

/*******************************************************************************
**                     LIGHTS_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV int		get_shadow(t_world world,
						t_intersection collision, t_light light);
CUDA_HOSTDEV double		get_light_at(t_light light,
						t_intersection intersection, t_index indexes);

/*******************************************************************************
**                     CAMERA_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV void		cam_rot(t_camera *camera, double degrees, char axis);
CUDA_HOSTDEV void		get_camera_axes(t_camera *camera);

/*******************************************************************************
**                     VECTOR_FCTS                                            **
*******************************************************************************/

CUDA_HOSTDEV void		rotate(t_vec3d *point, double degrees, char axis);
CUDA_HOSTDEV void		translate(t_vec3d *point, double x, double y, double z);
CUDA_HOSTDEV t_vec3d	new_vector(double x, double y, double z);
CUDA_HOSTDEV t_vec3d	vector_add(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_substract(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_cross(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_scalar(t_vec3d vect1, double scalar);
CUDA_HOSTDEV t_vec3d	vector_calculate(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV t_vec3d	vector_normalize(t_vec3d vect1);
CUDA_HOSTDEV double		vector_dot(t_vec3d vect1, t_vec3d vect2);
CUDA_HOSTDEV double		vector_length(t_vec3d vect1);

/*******************************************************************************
**                     MATH_FCTS                                              **
*******************************************************************************/

CUDA_HOSTDEV double		deg_to_radians(double deg);

/*******************************************************************************
**                     RAYTRACERS_FCTS                                        **
*******************************************************************************/

CUDA_HOSTDEV void				get_up_left(t_world *world);
CUDA_HOSTDEV int				ray_tracer(t_world world, int x, int y);

#endif
