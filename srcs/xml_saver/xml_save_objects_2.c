/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_objects_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:10:07 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 19:28:43 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void		save_cylinders_to_xml(t_world *world, xmlNodePtr root_node)
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
		node = xml_save_one_data(world->cylinders->transparence_coef,
				"transparence", object);
		node = xml_save_perlin(&world->cylinders->perlin, "perlin", object);
		world->cylinders = world->cylinders->next;
	}
	world->cylinders = ptr;
}

void		save_cones_to_xml_next(t_world *world, xmlNodePtr node,
	xmlNodePtr object)
{
	node = xml_save_one_data(world->cones->reflection_coef,
			"reflection", object);
	node = xml_save_one_data(world->cones->refraction_coef,
			"refraction", object);
	node = xml_save_one_data(world->cones->transparence_coef,
			"transparence", object);
	node = xml_save_perlin(&world->cones->perlin, "perlin", object);
	world->cones = world->cones->next;
}

void		save_cones_to_xml(t_world *world, xmlNodePtr root_node)
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
		save_cones_to_xml_next(world, node, object);
	}
	world->cones = ptr;
}

void		save_paraboloids_to_xml_next(t_world *world, xmlNodePtr node,
	xmlNodePtr object)
{
	node = xml_save_one_data(world->paraboloids->reflection_coef,
			"reflection", object);
	node = xml_save_one_data(world->paraboloids->refraction_coef,
			"refraction", object);
	node = xml_save_one_data(world->paraboloids->transparence_coef,
			"transparence", object);
	node = xml_save_perlin(&world->paraboloids->perlin, "perlin", object);
}

void		save_paraboloids_to_xml(t_world *world, xmlNodePtr root_node)
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
		save_paraboloids_to_xml_next(world, node, object);
		world->paraboloids = world->paraboloids->next;
	}
	world->paraboloids = ptr;
}
