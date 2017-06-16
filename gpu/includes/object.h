/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 12:45:19 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 17:07:03 by aanzieu          ###   ########.fr       */
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

/*******************************************************************************
**                     FCTS_OBJ                                               **
*******************************************************************************/

t_sphere				*new_sphere(t_sphere *nw);
t_cone					*new_cone(t_cone *nw);
t_plane					*new_plan(t_plane *nw);
t_cylinder				*new_cylinder(t_cylinder *nw);

void					add_sphere(t_sphere **alst, t_sphere *nw);
void					add_plan(t_plane **alst, t_plane *nw);
void					add_cylinder(t_cylinder **alst, t_cylinder *nw);
void					add_cone(t_cone **alst, t_cone *nw);

#endif
