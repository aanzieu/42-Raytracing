/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_objects_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:10:07 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 17:21:31 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	save_cylinders_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_cylinder	*ptr;

	ptr = world->cylinders;
	while (world->cylinders != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "cylinder", NULL);
		node = xml_save_vec3d(&world->cylinders->pos, "pos", object);
		node = xml_save_vec3d(&world->cylinders->up, "normal", object);
		node = xml_save_one_data(world->cylinders->radius, "radius", object);
		node = xml_save_rgb(&world->cylinders->color, "color", object);
		if (world->cylinders->chess.r != -1)
			node = xml_save_rgb(&world->cylinders->chess, "chess", object);
		node = xml_save_one_data(world->cylinders->reflection_coef,
				"reflection", object);
		node = xml_save_one_data(world->cylinders->refraction_coef,
				"refraction", object);
		world->cylinders = world->cylinders->next;
	}
	world->cylinders = ptr;
}

void	save_cones_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_cone		*ptr;

	ptr = world->cones;
	while (world->cones != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "cone", NULL);
		node = xml_save_vec3d(&world->cones->pos, "pos", object);
		node = xml_save_vec3d(&world->cones->up, "normal", object);
		node = xml_save_one_data(world->cones->half_angle, "radius", object);
		node = xml_save_one_data(world->cones->height, "height", object);
		node = xml_save_vec3d(&world->cones->min, "min", object);
		node = xml_save_vec3d(&world->cones->max, "max", object);
		node = xml_save_rgb(&world->cones->color, "color", object);
		if (world->cones->chess.r != -1)
			node = xml_save_rgb(&world->cones->chess, "chess", object);
		node = xml_save_one_data(world->cones->reflection_coef,
				"reflection", object);
		node = xml_save_one_data(world->cones->refraction_coef,
				"refraction", object);
		world->cones = world->cones->next;
	}
	world->cones = ptr;
}

void	save_disks_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_disk		*ptr;

	ptr = world->disks;
	while (world->disks != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "disk", NULL);
		node = xml_save_vec3d(&world->disks->pos, "origin", object);
		node = xml_save_vec3d(&world->disks->up, "normal", object);
		node = xml_save_one_data(world->disks->radius, "radius", object);
		node = xml_save_rgb(&world->disks->color, "color", object);
		if (world->disks->chess.r != -1)
			node = xml_save_rgb(&world->disks->chess, "chess", object);
		node = xml_save_one_data(world->disks->reflection_coef, "reflection",
				object);
		node = xml_save_one_data(world->disks->refraction_coef, "refraction",
				object);
		world->disks = world->disks->next;
	}
	world->disks = ptr;
}

void	save_paraboloids_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr		object;
	xmlNodePtr		node;
	t_paraboloid	*ptr;

	ptr = world->paraboloids;
	while (world->paraboloids != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "paraboloid", NULL);
		node = xml_save_vec3d(&world->paraboloids->top, "top", object);
		node = xml_save_vec3d(&world->paraboloids->normal, "normal", object);
		node = xml_save_one_data(world->paraboloids->distance,
				"radius", object);
		node = xml_save_one_data(world->paraboloids->maxm, "height", object);
		node = xml_save_rgb(&world->paraboloids->color, "color", object);
		if (world->paraboloids->chess.r != -1)
			node = xml_save_rgb(&world->paraboloids->chess, "chess", object);
		node = xml_save_one_data(world->paraboloids->reflection_coef,
				"reflection", object);
		node = xml_save_one_data(world->paraboloids->refraction_coef,
				"refraction", object);
		world->paraboloids = world->paraboloids->next;
	}
	world->paraboloids = ptr;
}

void	save_hyperboloids_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr		object;
	xmlNodePtr		node;
	t_hyperboloid	*ptr;

	ptr = world->hyperboloids;
	while (world->hyperboloids != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "hyperboloid", NULL);
		node = xml_save_vec3d(&world->hyperboloids->top, "top", object);
		node = xml_save_vec3d(&world->hyperboloids->normal, "normal", object);
		node = xml_save_one_data(world->hyperboloids->radius, "radius", object);
		node = xml_save_one_data(world->hyperboloids->maxm, "height", object);
		node = xml_save_rgb(&world->hyperboloids->color, "color", object);
		if (world->hyperboloids->chess.r != -1)
			node = xml_save_rgb(&world->hyperboloids->chess, "chess", object);
		node = xml_save_one_data(world->hyperboloids->reflection_coef,
				"reflection", object);
		node = xml_save_one_data(world->hyperboloids->refraction_coef,
				"refraction", object);
		world->hyperboloids = world->hyperboloids->next;
	}
	world->hyperboloids = ptr;
}
