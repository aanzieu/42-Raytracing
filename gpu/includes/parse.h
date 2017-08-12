/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:45:49 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/18 17:34:14 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <libxml/xmlmemory.h>
# include <libxml/parser.h>
# include "gpu_rt.h"
# include "object.h"
# include "light.h"
# include "rt.h"

/*
**	parser.c
*/
void		parse_rtv1(t_world *world, char *argv);
/*
**	parse_camera.c
*/
void		parse_camera(t_world *world, xmlNodePtr cur);
/*
**	parse_light.c
*/
void		parse_light(t_world *world, xmlNodePtr cur);
/*
**	parse_plane.c
*/
void		parse_plane(t_world *world, xmlNodePtr cur);
/*
**	parse_sphere.c
*/
void		parse_sphere(t_world *world, xmlNodePtr cur);
/*
**	parse_cylinder.c
*/
void		parse_cylinder(t_world *world, xmlNodePtr cur);
/*
**	parse_disk.c
*/
void		parse_disk(t_world *world, xmlNodePtr cur);
/*
**	parse_cone.c
*/
void		parse_cone(t_world *world, xmlNodePtr cur);
/*
**	parse_paraboloid.c
*/
void		parse_paraboloid(t_world *world, xmlNodePtr cur);
/*
**	parse_hyperboloid.c
*/
void		parse_hyperboloid(t_world *world, xmlNodePtr cur);
/*
**	parse_mobius.c
*/
void		parse_mobius(t_world *world, xmlNodePtr cur);
/*
**	error_msg.c
*/
void		show_error(const char *str);
void		show_error_2(const char *s1, const char *s2);
/*
**	parse_init_pos.c
*/
void		parse_vec3d(t_vec3d *v, xmlNodePtr cur);
void		parse_tra(t_vec3d *v, xmlNodePtr cur);
void		parse_rot(t_vec3d *v, xmlNodePtr cur);
void		parse_radius(double *radius, xmlNodePtr cur);
void		parse_height(double *height, xmlNodePtr cur);
/*
**	parse_init_color.c
*/
void		parse_color(t_color *c, xmlNodePtr cur);
void		parse_intensity(double *intensity_coef, xmlNodePtr cur);
void		parse_reflection(double *reflexion_coef, xmlNodePtr cur);
void		parse_ambient(t_world *world, xmlNodePtr cur);
/*
**	parser_utils.c
*/
int			is_numeric(const char *str);


//void		parse_rtv1(t_world *world, char *argv);

//void		parse_camera(t_world *world, t_camera *cam, t_list *lst);
//void		parse_light(t_world *world, t_list *lst);
//void		parse_sphere(t_world *world, t_list *lst);
//void		parse_plane(t_world *world, t_list *lst);
//void		parse_disk(t_world *world, t_list *lst);
//void		parse_cylinder(t_world *world, t_list *lst);
//void		parse_cone(t_world *world, t_list *lst);
//void		parse_paraboloid(t_world *world, t_list *lst);
//void		parse_hyperboloid(t_world *world, t_list *lst);

//void		parse_rotation_object(t_vec3d *v, char **tmp, int line);
//void		parse_point_translation(t_vec3d *v, char **tmp, int line);
//void		parse_rotation_cam(t_camera *cam, char **tmp, int line);
//void		parse_color(t_color *c, char **tmp, int line);
//void		parse_vector(t_vec3d *v, char **tmp, int line);
//void		parse_point(t_vec3d *v, char **tmp, int line);
//void		parse_intensity(double *intensity_coef, char **tmp, int line);
//void		parse_reflexion(double *reflexion_coef, char **tmp, int line);
//void		parse_ambient(t_world *world, t_list *lst);

#endif
