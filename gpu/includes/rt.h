/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:42:01 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/25 15:16:43 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <dirent.h>
# include <light.h>
# include <object.h>

# include <pthread.h>

# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/GL.framework/glew/2.1.0/include/GL/glew.h"
# include "../frameworks/GL.framework/glfw/3.2.1/include/GLFW/glfw3.h"
# include "../libft/libft.h"

# define NB_TH 4

# define VERSION 1.03.3

# define WIN_WIDTH 896
# define WIN_HEIGHT 640

# define SHADOW_BIAS 0
# define MAX_DEPTH 4
# define CHESS_PATTERN 2
# define BACKGROUND_COLOR 0x42ADD4

typedef struct		s_screen
{
	int				width;
	int				height;
	int				display_width;
	int				display_height;
	t_vec2d			scale;
}					t_screen;

typedef struct		s_offsets
{
	int				y_min;
	int				y_max;
	int				render_factor;
	int				aa;
	int				mode;
	int				id_save;
	char			ob_save;
}					t_offsets;

typedef struct		s_window
{
	SDL_Surface		*screen;
	SDL_Window		*id;
}					t_window;

typedef struct		s_keys
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				space;
	int				rightbracket;
	int				leftbracket;
	int				pad_0;
	int				pad_1;
	int				pad_2;
	int				pad_3;
	int				pad_4;
	int				pad_5;
	int				pad_6;
	int				pad_7;
	int				pad_8;
	int				pad_9;
	int				j;
	int				k;
	int				light_none;
	int				i;
	int				q;
	int				e;
	int				w;
	int				s;
	int				a;
	int				d;
	int				four;
	int				five;
	int				six;
	int				eight;
	int				select;
}					t_keys;

typedef struct		s_camera
{
	t_vec3d			pos;
	t_vec3d			look_at;
	t_vec3d			dir_v;
	t_vec3d			up_v;
	t_vec3d			right_v;
	int				rotation;
	double			fov;
}					t_camera;

typedef struct		s_intersection
{
	t_vec3d			normal_v;
	t_vec3d			pos;
	t_color			color;
	t_color			chess;
	double			negative;
	double			reflection_coef;
	double			refraction_coef;
	double			transparence_coef;
	double			t;
	double			t1;
	double			t2;
	char			type;
	int				id;
	int				id_save;
	int				flag;
	int				depth;
}					t_intersection;

typedef struct		s_ray
{
	t_vec3d			origin;
	t_vec3d			dir;
	t_vec3d			dir_point;
}					t_ray;

typedef struct		s_viewplane
{
	int				x_res;
	int				y_res;
	double			x_indent;
	double			y_indent;
	double			dist;
	double			height;
	double			width;
	t_vec3d			up_left;
}					t_viewplane;

typedef struct		s_2deg
{
	double			a;
	double			b;
	double			c;
	double			det;
}					t_2deg;

/*
** Structure Thread
*/

typedef struct		s_thread_input
{
	int				th;
	int				aa;
	int				y_min;
	int				y_max;
	struct s_world	*world;
}					t_thread_input;

/*
** Structure World
*/

typedef struct		s_world
{
	t_window		window;
	char			*title;
	t_sphere		*spheres;
	t_plane			*planes;
	t_disk			*disks;
	t_light			*lights;
	t_cylinder		*cylinders;
	t_cone			*cones;
	t_paraboloid	*paraboloids;
	t_hyperboloid	*hyperboloids;
	t_torus			*torus;
	t_mobius		*mobius;
	t_triangle		*triangles;
	t_cube			*cubes;
	t_h_cube		*h_cubes;
	t_sphere		*spheres_tmp;
	t_plane			*planes_tmp;
	t_disk			*disks_tmp;
	t_light			*lights_tmp;
	t_cylinder		*cylinders_tmp;
	t_cone			*cones_tmp;
	t_paraboloid	*paraboloids_tmp;
	t_hyperboloid	*hyperboloids_tmp;
	t_torus			*torus_tmp;
	t_mobius		*mobius_tmp;
	t_triangle		*triangles_tmp;
	t_cube			*cubes_tmp;
	t_h_cube		*h_cubes_tmp;
	t_sphere		*spheres_d;
	t_plane			*planes_d;
	t_light			*lights_d;
	t_cone			*cones_d;
	int				spheres_len;
	int				planes_len;
	int				cylinders_len;
	int				cones_len;
	int				lights_len;
	int				paraboloids_len;
	int				hyperboloids_len;
	int				disks_len;
	int				torus_len;
	int				mobius_len;
	int				triangles_len;
	int				cubes_len;
	int				h_cubes_len;
	pthread_t		thread[NB_TH];
	int				th;
	int				clientrender;
	int				*a_h;
	unsigned char	*video_buffer;
	size_t			size_main;
	int				reload_buffer;
	t_camera		camera;
	t_viewplane		viewplane;
	t_viewplane		viewplane_aa;
	t_keys			keys;
	int				mode;
	int				anaglyph_depth;
	int				animation_forward;
	int				recording;
	int				line;
	int				render_factor;
	t_offsets		offsets;
	t_ambient		ambient;
	int				light_type;
	double			intensity;
	int				id;
	int				id_save;
	char			ob_save;
	t_screen		screen;
	t_vec2d			xy;
	t_vec2d			pos_render;
	int				redraw;
	int				img_scene;
	int				aa;
	int				win_width;
	int				win_height;
	int				mode_cluster;
	t_vec3d			save_dir;
	t_vec3d			save_pos;

	int				*p;
}					t_world;

void 			perlin_noise_setup(t_world *world);
void				refresh_viewplane(t_world *world);
void				data_setup(t_world *world);
void				load_data(t_world *world);
void				get_viewplane(t_world *world);
int					launch_thread(t_world *world,
					int y_min, int y_max, int aam);
void				launch_cpu(t_world *world);
void				launch_gpu(t_world *world);
void				send_buffer(t_world *world, int port);
void				rt(t_world *world);
void				render_cuda(int *a_h, unsigned int constw,
					unsigned int consth, t_world world, int reset);
void				sphere_key_handler(t_world	*world);
void				plane_key_handler(t_world *world);
void				render(t_world *world);
int					event_handler(t_world *world, SDL_Event event);
void				memory_allocation_error();
void				free_world(t_world *world);
void				mouse_movement(t_world *world);
int					interface_launch(t_world *world, char *argv);

/*
********************************************************************************
**                     KEY_FCTS_OPTS                                          **
********************************************************************************
*/

void				key_release_handler1(t_world *world, SDL_Event event);
void				key_release_handler2(t_world *world, SDL_Event event);
void				key_press_handler1(t_world *world, SDL_Event event);
void				key_press_handler2(t_world *world, SDL_Event event);
void				key_press_handler3(t_world *world, SDL_Event event);
void				key_press_handler4(t_world *world);
void				key_press_handler5(t_world *world);
void				savebmp(t_world *world);
void				save_xml_scene(t_world *world);

/*
********************************************************************************
**                     CLUSTERING                                        	  **
********************************************************************************
*/

void				master_cluster(t_world *world);
void				client_cluster(t_world *world, int port);
void				*get_data_from_client_thread(void *arg);
void				get_data_from_client(char *hostname, unsigned short port,
					t_world *world);

/*
********************************************************************************
**                     LAUNCH_CONFIG                                      	  **
********************************************************************************
*/

void				choose_main_launcher(char **argv, int flags);
void				local_config(t_world *world, char *argv);
void				master_config(t_world *world, char *argv);
void				client_config(t_world *world, char *argv);
/*
**	error_msg.c
*/
void				show_error(const char *str);
void				show_error_2(const char *s1, const char *s2);

void				int_to_int(int *src, int *dst, int width, int height);
void				effect_application(t_world *world);
void				clear_world(t_world *world);

#endif
