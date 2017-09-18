/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:45:49 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/29 16:34:56 by PZC              ###   ########.fr       */
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
**	parse_torus.c
*/
void		parse_torus(t_world *world, xmlNodePtr cur);
/*
**	parse_cube.c
*/
void		parse_cube(t_world *world, xmlNodePtr cur);
/*
**	parse_h_cube.c
*/
void		parse_h_cube(t_world *world, xmlNodePtr cur);
/*
**	parse_triangle.c
*/
void		parse_triangle(t_world *world, xmlNodePtr cur);
/*
**	parse_mobius.c
*/
void		parse_mobius(t_world *world, xmlNodePtr cur);
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
/*
**	parse_material.c
*/
void 		parse_negative(int *negative, xmlNodePtr cur);
void		parse_reflection(double *reflection_coef, xmlNodePtr cur);
void		parse_refraction(double *refraction_coef, xmlNodePtr cur);
void		parse_transparence(double *transparence_coef, xmlNodePtr cur);

void		parse_ambient(t_world *world, xmlNodePtr cur);
/*
**	parser_utils.c
*/
int			is_numeric(const char *str);
/*
**	xml_save_objects.c
*/
void		save_cam_to_xml(t_world *world, xmlNodePtr root_node);
void		save_lights_to_xml(t_world *world, xmlNodePtr root_node);
void		save_ambient_to_xml(t_world *world, xmlNodePtr root_node);
void		save_planes_to_xml(t_world *world, xmlNodePtr root_node);
void		save_spheres_to_xml(t_world *world, xmlNodePtr root_node);
/*
**	xml_save_objects_2.c
*/
void		save_cylinders_to_xml(t_world *world, xmlNodePtr root_node);
void		save_cones_to_xml(t_world *world, xmlNodePtr root_node);
void		save_disks_to_xml(t_world *world, xmlNodePtr root_node);
void		save_paraboloids_to_xml(t_world *world, xmlNodePtr root_node);
void		save_hyperboloids_to_xml(t_world *world, xmlNodePtr root_node);
/*
**	xml_saver_func.c
*/
xmlNodePtr	xml_save_vec3d(t_vec3d *v, char *str, xmlNodePtr object);
xmlNodePtr	xml_save_one_data(double data, char *str, xmlNodePtr object);
xmlNodePtr	xml_save_rgb(t_color *c, char *str, xmlNodePtr object);
/*
**	ft_itoa_double.c
*/
char		*ft_itoa_double(double n);

#endif
