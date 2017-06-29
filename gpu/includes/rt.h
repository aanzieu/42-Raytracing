/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:42:01 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/29 15:19:10 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

#include <light.h>
#include <object.h>
#include "../libft/libft.h"

#include <pthread.h>
#include <SDL2/SDL.h>

#define NB_TH 8

#define VERSION 1.03.3

#define WIN_WIDTH 640
#define WIN_HEIGHT 640

#define SHADOW_BIAS 0

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
	int pad_0;
	int pad_1;
	int pad_2;
	int pad_3;
	int pad_4;
	int pad_5;
	int pad_6;
	int pad_7;
	int pad_8;
	int pad_9;
	int j;
	int k;
	int l;
	int i;
	int q;
	int e;
	int w;
	int s;
	int a;
	int d;
	int	four;
	int five;
	int six;
	int eight;
}					t_keys;

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
	double	reflexion_coef;
	double	t;
	char	type;
}					t_intersection;

typedef struct		s_ray
{
	t_vec3d	origin;
	t_vec3d	dir;
	t_vec3d	dir_point;
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

typedef struct		s_2deg
{
	double	a;
	double	b;
	double	c;
	double	det;
}					t_2deg;

/*
** Structure Thread
*/

typedef struct		s_thread_input
{
	int				th;
	struct s_world	*world;
}					t_thread_input;

/*
** Structure World
*/

typedef struct		s_world
{
	t_window	window;
	
	t_sphere	*spheres;
	t_plane		*planes;
	t_disk		*disks;
	t_light		*lights;
	t_cylinder	*cylinders;
	t_cone		*cones;
	t_paraboloid*paraboloids;
	t_hyperboloid	*hyperboloids;

	t_sphere	*spheres_tmp;
	t_plane		*planes_tmp;
	t_disk		*disks_tmp;
	t_light		*lights_tmp;
	t_cylinder	*cylinders_tmp;
	t_cone		*cones_tmp;
	t_paraboloid*paraboloids_tmp;
	t_hyperboloid	*hyperboloids_tmp;

	int			spheres_len;
	int			planes_len;
	int			cylinders_len;
	int			cones_len;
	int			lights_len;
	int			paraboloids_len;
	int			hyperboloids_len;
	int			disks_len;

	pthread_t		thread[NB_TH];
	int				th;
	
	int				*a_h;
	size_t		size_main;
	
	t_camera	camera;
	t_viewplane	viewplane;

	t_keys		keys;
	int			mode;

	int			line;

	int			render_factor;
	
	t_ambient	ambient;
	int			light_type;
}					t_world;

void render_cuda(int *a_h, unsigned int constw, unsigned int consth, t_world world, int reset);
void				sphere_key_handler(t_world	*world);
void				plane_key_handler(t_world *world);
void				render(t_world *world);
int					event_handler(t_world *world, SDL_Event event);
void				memory_allocation_error();
void				free_world(t_world *world);
void				mouse_movement(t_world *world);

/*******************************************************************************
**                     KEY_FCTS_OPTS                                          **
*******************************************************************************/

void				key_release_handler1(t_world *world, SDL_Event event);
void				key_release_handler2(t_world *world, SDL_Event event);
void				key_press_handler1(t_world *world, SDL_Event event);
void				key_press_handler2(t_world *world, SDL_Event event);
void				key_press_handler3(t_world *world, SDL_Event event);
void				key_press_handler4(t_world *world, SDL_Event event);

t_light		*copy_light(t_light *obj);
t_sphere	*copy_sphere(t_sphere *obj);
t_plane		*copy_plan(t_plane *obj);
t_cone		*copy_cone(t_cone *obj);
t_cylinder		*copy_cylinder(t_cylinder *obj);

/*******************************************************************************
**                     KEY_FCTS_OPTS                                          **
*******************************************************************************/

void render_clustering(t_world *world);
void get_data_from_client(t_world *world);
void	master_cluster(t_world *world);

#endif
