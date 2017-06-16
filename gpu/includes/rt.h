/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:42:01 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 13:32:58 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
#ifndef CUDA_HOSTDEV
# ifdef __CUDA_ARCH__
# define CUDA_HOSTDEV __host__ __device__
# else
# define CUDA_HOSTDEV
# endif
#endif

# include <SDL2/SDL.h>
# include "vectors.h"
# include "../libft/libft.h"

# define VERSION 1.03.3

# define WIN_WIDTH 640
# define WIN_HEIGHT 640

# define BLACK 0
# define WHITE 16777215
# define RED 16737380
# define BLUE 49151
# define GREEN 8190976
# define ORANGE 16753920
# define DARK_PINK 16711935
# define SKY_BLUE 8900331
# define LIGHT_BROWN 12624511

# define AMBIENT_LIGHT WHITE
# define SHADOW_BIAS 0

typedef struct		s_window
{
	SDL_Surface		*screen;
	SDL_Window		*id;
}					t_window;

typedef struct		s_keys
{
	int up;
	int down;
	int left;
	int right;
	int space;
	int rightbracket;
	int leftbracket;
	int j;
	int k;
	int l;
	int i;
	int q;
	int w;
	int s;
	int a;
	int d;
	int	four;
	int five;
	int six;
	int eight;
}					t_keys;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			light;
}					t_color;

typedef struct		s_camera
{
	t_vec3d	pos;
	t_vec3d look_at;
	t_vec3d	dir_v;
	t_vec3d	up_v;
	t_vec3d	right_v;
	int		rotation;
	double	fov;
}					t_camera;

typedef struct		s_intersection
{
	t_vec3d normal_v;
	t_vec3d	pos;
	t_color *color;
	double	t;
	char	type;
}					t_intersection;

typedef struct		s_ray
{
	t_vec3d	origin;
	t_vec3d	dir;
	t_vec3d	v;
}					t_ray;

typedef struct		s_viewplane
{
	int		x_res;
	int		y_res;
	double	x_indent;
	double	y_indent;
	double	dist;
	double	height;
	double	width;
	t_vec3d	up_left;
}					t_viewplane;

typedef struct		s_plane
{
	t_vec3d			up;
	t_vec3d			pos;
	t_color			color;
	struct s_plane	*next;
}					t_plane;

typedef struct		s_cylinder
{
	t_vec3d				up;
	t_vec3d				pos;
	t_vec3d				up_v;
	double				radius;
	t_color				color;
	struct s_cylinder	*next;
}					t_cylinder;

typedef struct		s_cone
{
	t_vec3d			up;
	t_vec3d			pos;
	double			half_angle;
	t_color			color;
	struct s_cone	*next;
}					t_cone;

typedef struct		s_sphere
{
	double			radius;
	t_vec3d			pos;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_light
{
	t_vec3d			pos;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct		s_2deg
{
	double	a;
	double	b;
	double	c;
	double	det;
}					t_2deg;

typedef struct		s_world
{
	t_sphere	*spheres;
	t_plane		*planes;
	t_light		*lights;
	t_cylinder	*cylinders;
	t_cone		*cones;
	t_sphere	*spheres_tmp;
	t_plane		*planes_tmp;
	t_light		*lights_tmp;
	t_cylinder	*cylinders_tmp;
	t_cone		*cones_tmp;
	t_viewplane	viewplane;
	t_camera	camera;
	t_camera	camera_tmp;
	t_window	window;
	t_keys		keys;
	int			spheres_len;
	int			planes_len;
	int			cylinders_len;
	int			cones_len;
	int			lights_len;
	int			line;
	int			render_factor;
}					t_world;

void render_cuda(int *a_h, unsigned int constw, unsigned int consth, t_world world, int reset);

void				rotate_c(t_vec3d *point, double degrees, char axis);

CUDA_HOSTDEV void	translate(t_vec3d *point, double x, double y, double z);

void				sphere_key_handler(t_world	*world);

void				plane_key_handler(t_world *world);

CUDA_HOSTDEV void				get_up_left(t_world *world);

void				render(t_world *world);

int					event_handler(t_world *world, SDL_Event event);

CUDA_HOSTDEV double				deg_to_radians(double deg);

void				memory_allocation_error();

void				free_world(t_world *world);

void				parse_rtv1(t_world *world, char *argv);

void				parse_sphere(t_world *world, t_list *lst);

void				parse_plane(t_world *world, t_list *lst);

void				parse_cylinder(t_world *world, t_list *lst);

void				parse_cone(t_world *world, t_list *lst);

void				parse_light(t_world *world, t_list *lst);

void				parse_camera(t_world *world, t_camera *cam, t_list *lst);

void				parse_color(t_color *c, char **tmp, int line);

void				parse_vector(t_vec3d *v, char **tmp, int line);

void				parse_rotation_object(t_vec3d *v, char **tmp, int line);

void				parse_point_translation(t_vec3d *v, char **tmp, int line);

void				parse_point(t_vec3d *v, char **tmp, int line);

void				add_sphere(t_sphere **alst, t_sphere *nw);

void				add_light(t_light **alst, t_light *nw);

void				add_plan(t_plane **alst, t_plane *nw);

void				add_cylinder(t_cylinder **alst, t_cylinder *nw);

void				add_cone(t_cone **alst, t_cone *nw);

t_sphere			*new_sphere(t_sphere *nw);

t_light				*new_light(t_light *nw);

t_plane				*new_plan(t_plane *nw);

t_cylinder			*new_cylinder(t_cylinder *nw);

t_cone				*new_cone(t_cone *nw);

void				parse_rotation_cam(t_camera *cam, char **tmp, int line);

CUDA_HOSTDEV int	get_color(double r, double g, double b);

void				mouse_movement(t_world *world);

#endif
