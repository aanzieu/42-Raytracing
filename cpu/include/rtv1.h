/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:30:46 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/15 11:58:14 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define WW 720
# define WH 480

# define HSL(r,g,b)(256 * 256 * (r) + 256 * (g) + (b))
# define RGB(r,g,b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

# define ALPHA 45
# define IMG_RATIO ((double)WW / (double)WH)
# define AMBIENT 0.2
# define PRECISION 100
# define MIN 0.000001
# define MAX 80000

# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define P_UP 116
# define P_DOWN 121

# define PLUS 69
# define MINUS 78

# define W 13
# define A 0
# define S 1
# define D 2

# define DEL 117
# define SHIFT 257
# define CTRL 256
# define ALT 261
# define TAB 48
# define SPACE 49

# define ECHAP 53

# define PAD_0 82
# define PAD_1 83
# define PAD_2 84
# define PAD_3 85
# define PAD_4 86
# define PAD_5 87
# define PAD_6 88
# define PAD_7 89
# define PAD_8 91
# define PAD_9 92

# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6

# define NB_TH 20
# define FAST_RENDER_PRECISION 8

# define CONE 1
# define SPHERE 2
# define CYLINDRE 3
# define PLAN 4

# include "../minilibx_macos/mlx.h"
# include "../srcs/libft/libft.h"
# include "../srcs/libmath/libmath.h"
# include <fcntl.h>
# include <limits.h>
# include <float.h>
# include <pthread.h>
# include <OpenCL/opencl.h>

typedef struct		s_ray
{
	t_3point		org;
	t_vec3d			dir;
}					t_ray;

typedef	struct		s_img
{
	void			*img;
	char			*img_s;
	int				bpp;
	int				s_l;
	int				endian;
}					t_img;

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
	double			light;
}					t_color;

/*
** Structure Mouse Position
*/

typedef struct		s_mouse
{
	char			id;
	int				x;
	int				y;
	int				lastx;
	int				lasty;
//	int				pressed_mouse;
}					t_mouse;

/*
** Structure Mouse Position
*/

typedef struct		s_keypress
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				p_up;
	int				p_down;
	int				plus;
	int				minus;
	int				w;
	int				a;
	int				s;
	int				d;
	int				del;
	int				shift;
	int				ctrl;
	int				alt;
	int				tab;
	int				space;
	int				pad_1;
	int				pad_2;
	int				pad_4;
	int				pad_5;
	int				pad_7;
	int				pad_8;
	int				pad_3;
	int				pad_0;
}					t_keypress;

/*
** Structure Objects
*/

typedef struct		s_light
{
	t_3point		position;
	t_color			color;
	t_vec3d			light_lenght;
	double			light_distance;
	float			angle;
	struct s_light	*next;
}					t_light;

typedef struct		s_plan
{
	t_3point		origin;
	t_vec3d			normal;
	t_color			color;
	struct s_plan	*next;
}					t_plan;

typedef struct		s_sphere
{
	t_3point		pos;
	t_color			color;
	double			radius;
	int				data;
	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_para
{
	t_3point		top;
	t_vec3d			normal;
	t_color			color;
	double			distance;
	double			maxm;
	struct s_para	*next;
}					t_para;

typedef struct		s_cone
{
	t_3point		center;
	t_vec3d			normal;
	t_color			color;
	double			angle;
	struct s_cone	*next;
}					t_cone;

typedef struct		s_cy
{
	t_3point		center;
	t_vec3d			normal;
	t_color			color;
	double			angle;
	double			limit;
	struct s_cy		*next;
}					t_cy;

typedef struct		s_elips
{
	t_3point		center;
	t_vec3d			normal;
	double			radius;
	double			kdistance;
	t_color			color;
	t_eq			sol;
	struct s_elips	*next;
}					t_elips;

/*
** Structure Intersection RayT
*/

typedef struct		s_object
{
	t_ray			point;
	t_vec3d			normal;
	t_vec3d			specular;
	t_color			color;
	t_para			*para;
	t_elips			*elips;
	t_sphere		*sphere;
	t_cone			*cone;
	t_plan			*plan;
	t_cy			*cy;
	double			tclose;
	int				type;
	int				data;
}					t_object;

/*
** Structure Camera
*/

typedef struct		s_cam
{
	t_3point		pos;
	t_3point		look_at;
	t_vec3d			dir;
	t_vec3d			axe_x;
	t_vec3d			axe_y;
	t_vec3d			axe_z;
	t_3point		posreset;
	t_3point		look_at_reset;
	int				x_res;
	int				y_res;
	double			ratio;
	double			rotation;
	double			x;
	double			y;
}					t_cam;

/*
** Structure Scene
*/

typedef struct		s_scene
{
	char			*name;
	t_cam			camera;
	t_light			*l;
	t_plan			*p;
	t_sphere		*s;
	t_cone			*co;
	t_cy			*cy;
	t_para			*para;
	t_elips			*elips;
	int				line;
	int				light;
	int				brillance;
	int				shadow;
}					t_scene;

/*
** Structure Thread
*/

typedef struct		s_thread_cpy
{
	char			*img_s;
	int				bpp;
	int				s_l;
	void			*mlx;
	int				endian;
	int				x;
	int				y;
	unsigned int	co;
	t_ray			r;
	t_color			color;
	t_scene			*scene;

}					t_thread_cpy;

typedef struct		s_thread_input
{
	int				th;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	struct s_env	*e;
}					t_thread_input;

/*
** Structure World
*/

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			*image;
	int				color;
	int				mouse_event;
	struct s_mouse	mouse;
	t_keypress		keys;
	int				block_events;

	t_scene			*scene;
	t_sphere		*sphere;
	t_object		*selected_object;
	pthread_t		thread[NB_TH];
	int				th;
}					t_env;

/*
** colors.c
*/

void				black_white(t_env *e);
void				negative_color(t_env *e);//, char *pix);
void				bayer_color(t_env *e);//, char *pix)
void				sepia_color(t_env *e);//, char *pix);
int					get_color(t_color c);
int					get_special_color(int i, double m, double h);
t_color				get_color_object(t_ray	r, t_scene *s);
t_color				get_light_at(t_object *i, t_scene *s);
t_color				color_def(t_color c);

/*
** camera.c
*/

void				get_camera(t_scene *scene, t_cam *cam, t_list *lst);
void				cam_position(t_cam *cam, int x, int y);
void				cam_reset(t_cam *cam);

/*
** colors_calcul.c
*/

t_color				color_add(t_color c1, t_color c2);
t_color				color_sub(t_color c1, t_color c2);
t_color				color_scalar(double scalar, t_color c1);
t_color				color_multiply(t_color c1, t_color c2);

/*
** Mouse_and_Key.c
*/

void				check_pressed_keys(t_keypress *keys,
					t_scene *e, t_env *env);
int					mouse_hook(int button, int x, int y, t_env *e);
int					key_hook(int button, t_env *e);
int					expose_hook(t_env *e);
int					one_keypressed(t_keypress *keys);
int					mousepress(int button, int x, int y, t_env *e);
int					mouserelease(int button, int x, int y, t_env *e);

/*
** Mouse_remove.c
*/

void		cam_axes(t_cam *cam);
int				motionnotify_env(int x, int y, t_env *e);
void				remove_plan(t_plan **s, t_plan *i);
void				remove_cyl(t_cy **s, t_cy *i);
void				remove_cone(t_cone **s, t_cone *i);
void				remove_sphere(t_sphere **s, t_sphere *i);

/*
** mlx.c
*/

void				ft_mlx_del(t_env *e);
void				mlx_del(t_env *e);

/*
** malloc.c
*/

t_color				new_color(double r, double g, double b, double light);
t_ray				new_ray(t_3point org, t_vec3d dir);
t_scene				*new_scene(void);
t_scene				*ft_copy_scene(t_env *e);

/*
** malloc_cpy.c
*/

t_para				*copy_para(t_para *obj);
t_elips				*copy_elips(t_elips *obj);
t_plan				*copy_plan(t_plan *obj);
t_light				*copy_light(t_light *obj);
t_sphere			*copy_sphere(t_sphere *obj);
t_cone				*copy_cone(t_cone *obj);
t_cy				*copy_cy(t_cy *obj);

/*
** malloc_object.c
*/

t_elips				*new_elips(t_elips *nw);
t_para				*new_para(t_para *nw);
t_plan				*new_plan(t_plan *nw);
t_sphere			*new_sphere(t_sphere *nw);
t_light				*new_light(t_light *nw);
t_cone				*new_cone(t_cone *nw);
t_cy				*new_cy(t_cy *nw);
t_object			*new_object(void);
t_scene				*get_scene(t_list *curr);

/*
** image_mlx.c
*/

t_img				*del_image(t_env *e, t_img *img);
t_img				*new_image(t_env *e);

/*
** cpy.c
*/

t_ray				cpy_ray(t_ray r);
t_color				cpy_color(t_color c);
void				thread_copy(t_env *e, t_thread_cpy *cpy);

/*
** thread_free.c
*/

void				thread_free_lists(t_thread_cpy *cpy);
void				thread_free_plan(t_plan *p);
void				thread_free_sphere(t_sphere *s);
void				thread_free_cone(t_cone *c);
void				thread_free_cy(t_cy *cy);
void				thread_free_light(t_light *l);

/*
** intersection.c
*/

int					get_intersection_point(t_env *e, int x, int y);
t_object			*intersection_value(t_object *i, t_object *i2);
t_object			*find_intersection(t_ray r, t_scene *e);
t_object			*find_spheres_intersection(t_ray ray, t_scene *e);
t_object			*find_plans_intersection(t_ray ray, t_scene *e);
t_object			*find_cones_intersection(t_ray ray, t_scene *scene);
t_object			*find_cylindres_intersection(t_ray ray, t_scene *scene);
t_object			*find_paraboloids_intersection(t_ray ray, t_scene *scene);
t_object			*find_elipsoids_intersection(t_ray ray, t_scene *scene);

/*
** iray.c
*/

t_vec3d				get_ref_ray(t_vec3d n, t_ray r);
t_ray				point_from_ray(t_ray r, double inter);
t_ray				get_objet(t_cam cam, float viewwidth, float viewheight);
t_ray				get_raytracing(t_cam *c);

/*
** delete.c
*/

void				delete_vect(t_vec3d v);
void				delete_ray(t_ray v);
void				delete_color(t_color c);
void				delete_inter(t_object *i);

/*
** parse_add.c
*/

void				add_cylinder(t_cy **alst, t_cy *nw);
void				add_cone(t_cone **alst, t_cone *nw);
void				add_sphere(t_sphere **alst, t_sphere *nw);
void				add_light(t_light **alst, t_light *nw);
void				add_plan(t_plan **alst, t_plan *nw);

/*
** parse_infos.c
*/

void				parse_rtv1(t_env *e, char *argv);
void				parse_vector(t_vec3d *v, char **tmp, int line);
void				parse_point(t_3point *v, char **tmp, int line);
void				parse_color(t_color *c, char **tmp, int line);
void				parse_point_translation(t_3point *v, char **tmp, int line);
void				parse_rotation_object(t_vec3d *v, char **tmp, int line);

/*
** parse_objects.c
*/

void				get_sphere(t_scene *scene, t_list *lst);
void				get_light(t_scene *scene, t_list *lst);
void				get_plan(t_scene *scene, t_list *lst);
void				get_cylinder(t_scene *scene, t_list *lst);
void				get_cone(t_scene *scene, t_list *lst);
void				get_paraboloid(t_scene *scene, t_list *lst);
void				get_elipsoid(t_scene *scene, t_list *lst);

/*
** draw_RT.c
*/

int					launch_rtv1(t_env *e);

#endif
