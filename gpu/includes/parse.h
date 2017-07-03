/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:45:49 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/21 11:48:05 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "rt.h"

/*******************************************************************************
**                     PARSING_FCTS_OPTS                                      **
*******************************************************************************/

void				parse_rtv1(t_world *world, char *argv);

void				parse_rotation_object(t_vec3d *v, char **tmp, int line);
void				parse_point_translation(t_vec3d *v, char **tmp, int line);
void				parse_rotation_cam(t_camera *cam, char **tmp, int line);
void				parse_camera(t_world *world, t_camera *cam, t_list *lst);

void				parse_light(t_world *world, t_list *lst);

void				parse_sphere(t_world *world, t_list *lst);
void				parse_plane(t_world *world, t_list *lst);
void				parse_disk(t_world *world, t_list *lst);
void				parse_cylinder(t_world *world, t_list *lst);
void				parse_cone(t_world *world, t_list *lst);
void				parse_paraboloid(t_world *world, t_list *lst);

void				parse_hyperboloid(t_world *world, t_list *lst);
void				parse_color(t_color *c, char **tmp, int line);
void				parse_vector(t_vec3d *v, char **tmp, int line);
void				parse_point(t_vec3d *v, char **tmp, int line);
void				parse_intensity(double *intensity_coef, char **tmp, int line);
void				parse_reflexion(double *reflexion_coef, char **tmp, int line);
void        parse_refraxion(double *refraxion_coef, char **tmp, int line);
void				parse_ambient(t_world *world, t_list *lst);

#endif
