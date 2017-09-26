/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:03:42 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/18 17:31:24 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	save_cam_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;

	object = xmlNewChild(root_node, NULL, BAD_CAST "camera", NULL);
	node = xml_save_vec3d(&world->camera.pos, "pos", object);
	node = xml_save_vec3d(&world->camera.look_at, "dir", object);
}

void	save_lights_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_light		*ptr;

	ptr = world->lights;
	while (world->lights != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "light", NULL);
		node = xml_save_vec3d(&world->lights->pos, "pos", object);
		node = xml_save_rgb(&world->lights->color, "color", object);
		node = xml_save_one_data(world->lights->intensity_coef, "intensity",
				object);
		node = xml_save_one_data_str(world->lights->type, "type",
				object);
		world->lights = world->lights->next;
	}
	world->lights = ptr;
}

void	save_ambient_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;

	object = xmlNewChild(root_node, NULL, BAD_CAST "ambient", NULL);
	node = xml_save_rgb(&world->ambient.color, "color", object);
	node = xml_save_one_data(world->ambient.intensity, "intensity", object);
}

void	save_planes_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_plane		*ptr;

	ptr = world->planes;
	while (world->planes != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "plane", NULL);
		node = xml_save_vec3d(&world->planes->pos, "origin", object);
		node = xml_save_vec3d(&world->planes->up, "normal", object);
		node = xml_save_rgb(&world->planes->color, "color", object);
		if (world->planes->chess.r != -1)
			node = xml_save_rgb(&world->planes->chess, "chess", object);
		node = xml_save_one_data(world->planes->reflection_coef, "reflection",
				object);
		node = xml_save_one_data(world->planes->refraction_coef, "refraction",
				object);
		world->planes = world->planes->next;
	}
	world->planes = ptr;
}

void	save_spheres_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_sphere	*ptr;

	ptr = world->spheres;
	while (world->spheres != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "sphere", NULL);
		node = xml_save_vec3d(&world->spheres->pos, "pos", object);
		node = xml_save_one_data(world->spheres->radius, "radius", object);
		node = xml_save_rgb(&world->spheres->color, "color", object);
		if (world->spheres->chess.r != -1)
			node = xml_save_rgb(&world->spheres->chess, "chess", object);
		node = xml_save_one_data(world->spheres->reflection_coef, "reflection",
				object);
		node = xml_save_one_data(world->spheres->refraction_coef, "refraction",
				object);
		world->spheres = world->spheres->next;
	}
	world->spheres = ptr;
}
