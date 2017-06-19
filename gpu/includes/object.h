/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:45:19 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 12:11:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

#include "vectors.h"
#include "colors.h"

typedef struct			s_plane
{
	t_vec3d				up;
	t_vec3d				pos;
	t_color				color;
	struct s_plane		*next;
}						t_plane;

typedef struct			s_cylinder
{
	t_vec3d				up;
	t_vec3d				pos;
	t_vec3d				up_v;
	double				radius;
	t_color				color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct			s_cone
{
	t_vec3d				up;
	t_vec3d				pos;
	double				half_angle;
	t_color				color;
	struct s_cone		*next;
}						t_cone;

typedef struct			s_sphere
{
	double				radius;
	t_vec3d				pos;
	t_color				color;
	struct s_sphere		*next;
}						t_sphere;

typedef struct			s_paraboloid
{
	t_vec3d				top;
	t_vec3d				normal;
	t_color				color;
	double				distance;
	double				maxm;
	struct s_paraboloid	*next;
}						t_paraboloid;

/*******************************************************************************
**                     FCTS_OBJ                                               **
*******************************************************************************/

t_sphere				*new_sphere(t_sphere *nw);
t_cone					*new_cone(t_cone *nw);
t_plane					*new_plan(t_plane *nw);
t_cylinder				*new_cylinder(t_cylinder *nw);
t_paraboloid			*new_paraboloid(t_paraboloid *nw);

void					add_sphere(t_sphere **alst, t_sphere *nw);
void					add_plan(t_plane **alst, t_plane *nw);
void					add_cylinder(t_cylinder **alst, t_cylinder *nw);
void					add_cone(t_cone **alst, t_cone *nw);
void					add_paraboloid(t_paraboloid **alst, t_paraboloid *nw);

void					load_planes(t_plane **planes, t_plane *planes_tmp,
						int *planes_len);
void					load_spheres(t_sphere **spheres, t_sphere *spheres_tmp,
						int *spheres_len);
void					load_cylinders(t_cylinder **cylinders,
						t_cylinder *cylinders_tmp, int *cylinders_len);
void					load_cones(t_cone **cones, t_cone *cones_tmp,
						int *cones_len);
void			load_paraboloids(t_paraboloid **paraboloids, t_paraboloid *paraboloids_tmp, int *cones_len);

#endif
