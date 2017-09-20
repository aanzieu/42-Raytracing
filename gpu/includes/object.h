/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:45:19 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/20 14:54:10 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "vectors.h"
# include "colors.h"
# include "light.h"

# define WOOD 1
# define GLASS 2
# define MARBLE 3

typedef struct				s_perlin
{
	int						is_set;
	int						pre_set;
	double					scale;
	double					amount;
}							t_perlin;

typedef struct				s_plane
{
	int						id;
	t_vec3d					up;
	t_vec3d					pos;
	t_color					color;
	t_color					chess;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_plane			*next;
}							t_plane;

typedef struct				s_disk
{
	int						id;
	t_vec3d					up;
	t_vec3d					pos;
	t_color					color;
	t_color					chess;
	double					radius;
	double					radius_squared;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_disk			*next;
}							t_disk;

typedef struct				s_cylinder
{
	int						id;
	t_vec3d					up;
	t_vec3d					pos;
	t_vec3d					up_v;
	t_color					color;
	t_color					chess;
	double					radius;
	double					height;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_cylinder		*next;
}							t_cylinder;

typedef struct				s_cone
{
	int						id;
	t_vec3d					up;
	t_vec3d					pos;
	t_color					color;
	t_color					chess;
	double					half_angle;
	double					height;
	t_vec3d					min;
	t_vec3d					max;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_cone			*next;
}							t_cone;

typedef struct				s_sphere
{
	int						id;
	double					radius;
	t_vec3d					pos;
	t_color					color;
	t_color					chess;
	t_color					rgba;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_sphere			*next;
}							t_sphere;

typedef struct				s_mobius
{
	int						id;
	double					radius;
	t_vec3d					pos;
	t_color					color;
	t_color					chess;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_mobius			*next;
}							t_mobius;

typedef struct				s_paraboloid
{
	int						id;
	t_vec3d					top;
	t_vec3d					normal;
	t_color					color;
	t_color					chess;
	double					distance;
	double					maxm;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_paraboloid		*next;
}							t_paraboloid;

typedef struct				s_hyperboloid
{
	int						id;
	t_vec3d					top;
	t_vec3d					normal;
	t_color					color;
	t_color					chess;
	double					radius;
	double					maxm;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_hyperboloid	*next;
}							t_hyperboloid;

typedef struct				s_torus
{
	int						id;
	t_vec3d					pos;
	t_vec3d					normal;
	t_color					color;
	t_color					chess;
	double					radius_small;
	double					radius_big;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_torus			*next;
}							t_torus;

typedef struct				s_triangle
{
	int						id;
	t_vec3d					pos;
	t_vec3d					up;
	t_vec3d					v1;
	t_vec3d					v2;
	t_color					color;
	t_color					chess;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_triangle		*next;
}							t_triangle;

typedef struct				s_cube
{
	int						id;
	t_vec3d					min;
	t_vec3d					max;
	t_vec3d					up;
	t_color					color;
	t_color					chess;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_cube			*next;
}							t_cube;

typedef struct				s_h_cube
{
	int						id;
	t_vec3d					pos;
	t_color					color;
	t_color					chess;
	double					reflection_coef;
	double					refraction_coef;
	double					transparence_coef;
	struct s_perlin			perlin;
	struct s_h_cube			*next;
}							t_h_cube;

/*
********************************************************************************
**                     FCTS_OBJ                                               **
********************************************************************************
*/

t_sphere					*new_sphere(t_sphere *nw, int id);
t_cone						*new_cone(t_cone *nw, int id);
t_plane						*new_plan(t_plane *nw, int id);
t_disk						*new_disk(t_disk *nw, int id);
t_cylinder					*new_cylinder(t_cylinder *nw, int id);
t_paraboloid				*new_paraboloid(t_paraboloid *nw, int id);
t_hyperboloid				*new_hyperboloid(t_hyperboloid *nw, int id);
t_torus						*new_torus(t_torus *nt, int id);
t_mobius					*new_mobius(t_mobius *nw, int id);
t_triangle					*new_triangle(t_triangle *nw, int id);
t_cube						*new_cube(t_cube *nw, int id);
t_h_cube					*new_h_cube(t_h_cube *nw, int id);
void						add_sphere(t_sphere **alst, t_sphere *nw);
void						add_plan(t_plane **alst, t_plane *nw);
void						add_disk(t_disk **alst, t_disk *nw);
void						add_cylinder(t_cylinder **alst, t_cylinder *nw);
void						add_cone(t_cone **alst, t_cone *nw);
void						add_paraboloid(t_paraboloid **alst,
							t_paraboloid *nw);
void						add_hyperboloid(t_hyperboloid **alst,
							t_hyperboloid *nw);
void						add_torus(t_torus **alst, t_torus *nw);
void						add_mobius(t_mobius **alst, t_mobius *nw);
void						add_triangle(t_triangle **alst, t_triangle *nw);
void						add_cube(t_cube **alst, t_cube *nw);
void						add_h_cube(t_h_cube **alst, t_h_cube *nw);

/*
********************************************************************************
**                     FREE FTCS                                              **
********************************************************************************
*/
void						thread_free_and_add_sphere(t_sphere **s,
							t_sphere **s_tmp, int *spheres_len, int id);
void						init_sphere_add(t_sphere *s);
void						thread_free_and_add_cone(t_cone **c,
							t_cone **c_tmp, int *len, int id);
void						init_cone_add(t_cone *c);
void						thread_free_and_add_plane(t_plane **p,
							t_plane **p_tmp, int *len, int id);
void						init_plane_add(t_plane *p);
void						thread_free_and_add_cylinder(t_cylinder **cy,
							t_cylinder **cy_tmp, int *len, int id);
void						init_cylinder_add(t_cylinder *cy);
void						thread_free_and_add_torus(t_torus **to,
							t_torus **to_tmp, int *len, int id);
void						init_torus_add(t_torus *to);
void						thread_free_and_add_mobius(t_mobius **mo,
							t_mobius **mo_tmp, int *len, int id);
void						init_mobius_add(t_mobius *mo);
void						thread_free_and_add_disk(t_disk **di,
							t_disk **di_tmp, int *len, int id);
void						init_disk_add(t_disk *di);
void						thread_free_and_add_cube(t_cube **cu,
							t_cube **cu_tmp, int *len, int id);
void						init_cube_add(t_cube *cu);
void						thread_free_and_add_h_cube(t_h_cube **cu,
							t_h_cube **cu_tmp, int *len, int id);
void						init_h_cube_add(t_h_cube *cu);
void						thread_free_and_add_hyperboloid(t_hyperboloid **hy,
							t_hyperboloid **hy_tmp, int *len, int id);
void						init_hyperboloid_add(t_hyperboloid *hy);
void						thread_free_and_add_paraboloid(t_paraboloid **p,
							t_paraboloid **p_tmp, int *len, int id);
void						init_paraboloid_add(t_paraboloid *p);
void						thread_free_and_add_triangle(t_triangle **t,
							t_triangle **t_tmp, int *len, int id);
void						init_triangle_add(t_triangle *t);
void						thread_free_and_add_light(t_light **l,
							t_light **l_tmp, int *len, int id);
void						init_light_add(t_light *l);

/*
********************************************************************************
**                     LOAD_FTCS                                              **
********************************************************************************
*/

void						load_planes(t_plane **planes, t_plane *planes_tmp,
							int *planes_len);
void						load_disks(t_disk **disks, t_disk *disks_tmp,
							int *disks_len);
void						load_spheres(t_sphere **spheres,
							t_sphere *spheres_tmp, int *spheres_len);
void						load_cylinders(t_cylinder **cylinders,
							t_cylinder *cylinders_tmp, int *cylinders_len);
void						load_cones(t_cone **cones, t_cone *cones_tmp,
							int *cones_len);
void						load_paraboloids(t_paraboloid **paraboloids,
							t_paraboloid *paraboloids_tmp,
							int *cones_len);
void						load_hyperboloids(t_hyperboloid **hyperboloids,
							t_hyperboloid *hyperboloids_tmp,
							int *hyperboloids_len);
void						load_torus(t_torus **torus,
							t_torus *torus_tmp,
							int *torus_len);
void						load_mobius(t_mobius **mobius,
							t_mobius *mobius_tmp, int *mobius_len);
void						load_triangles(t_triangle **triangles,
							t_triangle *triangles_tmp, int *triangles_len);
void						load_cubes(t_cube **cubes,
							t_cube *cubes_tmp, int *cubes_len);
void						load_h_cubes(t_h_cube **cubes,
							t_h_cube *cubes_tmp, int *cubes_len);

/*
********************************************************************************
**                     FREE_OBJS                                              **
********************************************************************************
*/

void						free_plan(t_plane **p_tmp, t_plane **p, int *len);
void						free_sphere(t_sphere **s_tmp,
							t_sphere **s, int *len);
void						free_cone(t_cone **c_tmp, t_cone **c, int *len);
void						free_cy(t_cylinder **c_tmp,
							t_cylinder **c, int *len);
void						free_mobius(t_mobius **l_tmp,
							t_mobius **l, int *len);
void						free_torus(t_torus **c_tmp, t_torus **c, int *len);
void						free_hyper(t_hyperboloid **c_tmp,
							t_hyperboloid **c, int *len);
void						free_para(t_paraboloid **p_tmp,
							t_paraboloid **p, int *len);
void						free_disk(t_disk **d_tmp, t_disk **d, int *len);
void						free_cube(t_cube **d_tmp, t_cube **d, int *len);
void						free_h_cube(t_h_cube **d_tmp,
							t_h_cube **d, int *len);
void						free_triangle(t_triangle **p_tmp,
							t_triangle **p, int *len);

#endif
