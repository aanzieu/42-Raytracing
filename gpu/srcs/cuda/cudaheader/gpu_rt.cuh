#ifndef CUDA_MD_H
# define CUDA_MD_H
#ifndef CUDA_HOSTDEV
# ifdef __CUDA_ARCH__
# define CUDA_HOSTDEV __host__ __device__
# else
# define CUDA_HOSTDEV
# endif
#endif

CUDA_HOSTDEV int		ray_tracer(t_world world, int x, int y);
CUDA_HOSTDEV double		get_closest_intersection(t_world world, t_ray ray,
							t_intersection *intersection);

CUDA_HOSTDEV double		get_closest_sphere(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp);

CUDA_HOSTDEV void		get_closest_plane(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp);

CUDA_HOSTDEV void		get_closest_cone(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp);

CUDA_HOSTDEV void		get_closest_cylinder(t_world world, t_ray ray,
			t_intersection *intersection, t_intersection *intersection_tmp);

CUDA_HOSTDEV int		get_plane(t_plane plane, t_ray ray,
										t_intersection *intersection_tmp);

CUDA_HOSTDEV int		get_cylinder(t_cylinder cylinder,
			t_camera camera, t_ray ray, t_intersection *intersection_tmp);

CUDA_HOSTDEV int		get_cone(t_cone cone, t_camera camera, t_ray ray,
										t_intersection *intersection_tmp);

CUDA_HOSTDEV t_vec3d	get_normal_sphere(t_sphere sphere,
			t_intersection intersection);

CUDA_HOSTDEV t_vec3d	get_normal_cylinder(t_cylinder cylinder,
			t_camera camera, t_ray ray, t_intersection intersection);

CUDA_HOSTDEV t_vec3d	get_normal_cone(t_cone cone, t_ray ray,
			t_intersection intersection);

CUDA_HOSTDEV void	color_multiply(t_color *color1, t_color color2);

CUDA_HOSTDEV void	color_scalar(t_color *color, double coeficient);

CUDA_HOSTDEV void	color_add(t_color *color1, t_color color2);

CUDA_HOSTDEV int	get_shadow(t_world world, t_intersection collision, t_light light);

CUDA_HOSTDEV double	get_light_at(t_light light, t_intersection intersection);

CUDA_HOSTDEV void		rotate(t_vec3d *point, double degrees, char axis);

CUDA_HOSTDEV void		cam_rot(t_camera *camera, double degrees, char axis);

CUDA_HOSTDEV void		get_camera_axes(t_camera *camera);

#endif
