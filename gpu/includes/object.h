/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:45:19 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/27 09:41:34 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

#include "vectors.h"
#include "colors.h"

typedef struct			s_plane
{
	int						id;
	t_vec3d				up;
	t_vec3d				pos;
	t_color				color;
	double				reflexion_coef;
	double				refraxion_coef;
	struct s_plane		*next;
}						t_plane;

typedef struct			s_disk
{
	int						id;
	t_vec3d				up;
	t_vec3d				pos;
	t_color				color;
	double				radius;
	double				radius_squared;
	double				reflexion_coef;
	double				refraxion_coef;
	struct s_disk		*next;
}						t_disk;

typedef struct			s_cylinder
{
	int						id;
	t_vec3d				up;
	t_vec3d				pos;
	t_vec3d				up_v;
	t_color				color;
	double				radius;
	double				reflexion_coef;
	double				refraxion_coef;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct			s_cone
{
	int						id;
	t_vec3d				up;
	t_vec3d				pos;
	t_color				color;
	double				half_angle;
	double				height;
	t_vec3d				min;
	t_vec3d				max;
	double				reflexion_coef;
	double				refraxion_coef;
	struct s_cone		*next;
}						t_cone;

typedef struct			s_sphere
{
	int						id;
	double				radius;
	t_vec3d				pos;
	t_color				color;
	double				reflexion_coef;
	double		refraxion_coef;
	struct s_sphere		*next;
}						t_sphere;

typedef struct			s_paraboloid
{
	int						id;
	t_vec3d				top;
	t_vec3d				normal;
	t_color				color;
	double				distance;
	double				maxm;
	double				reflexion_coef;
	double				refraxion_coef;
	struct s_paraboloid	*next;
}						t_paraboloid;

typedef struct			s_hyperboloid
{
	int						id;
	t_vec3d				top;
	t_vec3d				normal;
	t_color				color;
	double				radius;
	double				maxm;
	double				reflexion_coef;
	double				refraxion_coef;
	struct s_hyperboloid *next;
}						t_hyperboloid;

/*******************************************************************************
**                     FCTS_OBJ                                               **
*******************************************************************************/

t_sphere				*new_sphere(t_sphere *nw, int id);
t_cone					*new_cone(t_cone *nw, int id);
t_plane					*new_plan(t_plane *nw, int id);
t_disk					*new_disk(t_disk *nw, int id);
t_cylinder				*new_cylinder(t_cylinder *nw, int id);
t_paraboloid			*new_paraboloid(t_paraboloid *nw, int id);
t_hyperboloid				*new_hyperboloid(t_hyperboloid *nw, int id);

void					add_sphere(t_sphere **alst, t_sphere *nw);
void					add_plan(t_plane **alst, t_plane *nw);
void					add_disk(t_disk **alst, t_disk *nw);
void					add_cylinder(t_cylinder **alst, t_cylinder *nw);
void					add_cone(t_cone **alst, t_cone *nw);
void					add_paraboloid(t_paraboloid **alst, t_paraboloid *nw);
void				add_hyperboloid(t_hyperboloid **alst, t_hyperboloid *nw);



void					load_planes(t_plane **planes, t_plane *planes_tmp,
						int *planes_len);
void					load_disks(t_disk **disks, t_disk *disks_tmp,
						int *disks_len);
void					load_spheres(t_sphere **spheres, t_sphere *spheres_tmp,
						int *spheres_len);
void					load_cylinders(t_cylinder **cylinders,
						t_cylinder *cylinders_tmp, int *cylinders_len);
void					load_cones(t_cone **cones, t_cone *cones_tmp,
						int *cones_len);
void					load_paraboloids(t_paraboloid **paraboloids,
						t_paraboloid *paraboloids_tmp,
						int *cones_len);
void			load_hyperboloids(t_hyperboloid **hyperboloids, t_hyperboloid *hyperboloids_tmp, int *hyperboloids_len);






#endif
