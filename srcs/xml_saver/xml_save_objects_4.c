/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_objects_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 19:22:27 by huweber           #+#    #+#             */
/*   Updated: 2017/09/29 19:25:14 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

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
		node = xml_save_one_data(world->hyperboloids->transparence_coef,
				"transparence", object);
		node = xml_save_perlin(&world->hyperboloids->perlin, "perlin", object);
		world->hyperboloids = world->hyperboloids->next;
	}
	world->hyperboloids = ptr;
}

void	save_triangles_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_triangle	*ptr;

	ptr = world->triangles;
	while (world->triangles != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "triangle", NULL);
		node = xml_save_vec3d(&world->triangles->pos, "pos", object);
		node = xml_save_vec3d(&world->triangles->v1, "v1", object);
		node = xml_save_vec3d(&world->triangles->v2, "v2", object);
		node = xml_save_rgb(&world->triangles->color, "color", object);
		if (world->triangles->chess.r != -1)
			node = xml_save_rgb(&world->triangles->chess, "chess", object);
		node = xml_save_one_data(world->triangles->reflection_coef,
				"reflection", object);
		node = xml_save_one_data(world->triangles->refraction_coef,
				"refraction", object);
		node = xml_save_one_data(world->triangles->transparence_coef,
				"transparence", object);
		world->triangles = world->triangles->next;
	}
	world->triangles = ptr;
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
		node = xml_save_one_data(world->disks->transparence_coef,
				"transparence", object);
		node = xml_save_perlin(&world->disks->perlin, "perlin", object);
		world->disks = world->disks->next;
	}
	world->disks = ptr;
}
