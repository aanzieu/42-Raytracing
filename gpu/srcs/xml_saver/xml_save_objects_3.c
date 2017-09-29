/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_objects_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:10:07 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 19:22:36 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	save_torus_to_xml_next(t_world *world, xmlNodePtr node,
	xmlNodePtr object)
{
	node = xml_save_one_data(world->torus->reflection_coef, "reflection",
			object);
	node = xml_save_one_data(world->torus->refraction_coef, "refraction",
			object);
	node = xml_save_one_data(world->torus->transparence_coef,
			"transparence", object);
	node = xml_save_perlin(&world->torus->perlin, "perlin", object);
}

void	save_torus_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_torus		*ptr;

	ptr = world->torus;
	while (world->torus != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "torus", NULL);
		node = xml_save_vec3d(&world->torus->pos, "pos", object);
		node = xml_save_one_data(world->torus->radius_small, "radius_small",
				object);
		node = xml_save_one_data(world->torus->radius_big, "radius_big",\
				object);
		node = xml_save_rgb(&world->torus->color, "color", object);
		if (world->torus->chess.r != -1)
			node = xml_save_rgb(&world->torus->chess, "chess", object);
		save_torus_to_xml_next(world, node, object);
		world->torus = world->torus->next;
	}
	world->torus = ptr;
}

void	save_mobius_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_mobius	*ptr;

	ptr = world->mobius;
	while (world->mobius != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "mobius", NULL);
		node = xml_save_vec3d(&world->mobius->pos, "pos", object);
		node = xml_save_one_data(world->mobius->radius, "radius", object);
		node = xml_save_rgb(&world->mobius->color, "color", object);
		if (world->mobius->chess.r != -1)
			node = xml_save_rgb(&world->mobius->chess, "chess", object);
		node = xml_save_one_data(world->mobius->reflection_coef, "reflection",
				object);
		node = xml_save_one_data(world->mobius->refraction_coef, "refraction",
				object);
		node = xml_save_one_data(world->mobius->transparence_coef,
				"transparence", object);
		node = xml_save_perlin(&world->mobius->perlin, "perlin", object);
		world->mobius = world->mobius->next;
	}
	world->mobius = ptr;
}

void	save_h_cubes_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_h_cube	*ptr;

	ptr = world->h_cubes;
	while (world->h_cubes != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "h_cube", NULL);
		node = xml_save_vec3d(&world->h_cubes->pos, "pos", object);
		node = xml_save_rgb(&world->h_cubes->color, "color", object);
		if (world->h_cubes->chess.r != -1)
			node = xml_save_rgb(&world->h_cubes->chess, "chess", object);
		node = xml_save_one_data(world->h_cubes->reflection_coef, "reflection",
				object);
		node = xml_save_one_data(world->h_cubes->refraction_coef, "refraction",
				object);
		node = xml_save_one_data(world->h_cubes->transparence_coef,\
				"transparence", object);
		node = xml_save_perlin(&world->h_cubes->perlin, "perlin", object);
		world->h_cubes = world->h_cubes->next;
	}
	world->h_cubes = ptr;
}

void	save_cubes_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_cube		*ptr;

	ptr = world->cubes;
	while (world->cubes != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "cube", NULL);
		node = xml_save_vec3d(&world->cubes->min, "min", object);
		node = xml_save_vec3d(&world->cubes->max, "max", object);
		node = xml_save_rgb(&world->cubes->color, "color", object);
		if (world->cubes->chess.r != -1)
			node = xml_save_rgb(&world->cubes->chess, "chess", object);
		node = xml_save_one_data(world->cubes->reflection_coef, "reflection",
				object);
		node = xml_save_one_data(world->cubes->refraction_coef, "refraction",
				object);
		node = xml_save_one_data(world->cubes->transparence_coef,
				"transparence", object);
		node = xml_save_perlin(&world->cubes->perlin, "perlin", object);
		world->cubes = world->cubes->next;
	}
	world->cubes = ptr;
}
