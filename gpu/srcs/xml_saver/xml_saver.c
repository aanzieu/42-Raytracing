/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_saver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 17:20:24 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/28 15:04:37 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
static void save_objects_to_xml_next(t_world *world, xmlNodePtr root_node)
{
	if (world->lights_len != 0)
		save_lights_to_xml(world, root_node);
	if (world->ambient.intensity)
		save_ambient_to_xml(world, root_node);
	save_cam_to_xml(world, root_node);
}

static void	save_objects_to_xml(t_world *world, xmlNodePtr root_node)
{
	if (world->planes_len != 0)
		save_planes_to_xml(world, root_node);
	if (world->spheres_len != 0)
		save_spheres_to_xml(world, root_node);
	if (world->cylinders_len != 0)
		save_cylinders_to_xml(world, root_node);
	if (world->cones_len != 0)
		save_cones_to_xml(world, root_node);
	if (world->disks_len != 0)
		save_disks_to_xml(world, root_node);
	if (world->paraboloids_len != 0)
		save_paraboloids_to_xml(world, root_node);
	if (world->hyperboloids_len != 0)
		save_hyperboloids_to_xml(world, root_node);
	if (world->torus_len != 0)
		save_torus_to_xml(world, root_node);
	if (world->mobius_len != 0)
		save_mobius_to_xml(world, root_node);
	if (world->h_cubes_len != 0)
		save_h_cubes_to_xml(world, root_node);
	if (world->cubes_len != 0)
		save_cubes_to_xml(world, root_node);
	if (world->triangles_len != 0)
		save_triangles_to_xml(world, root_node);
	save_objects_to_xml_next(world, root_node);
}

void		save_xml_scene(t_world *world)
{
	xmlDocPtr	doc;
	xmlNodePtr	root_node;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL, BAD_CAST "scene");
	xmlDocSetRootElement(doc, root_node);
	xmlNewProp(root_node, BAD_CAST "name", BAD_CAST(world->title + 8));
	xmlCreateIntSubset(doc, BAD_CAST "scene", NULL, BAD_CAST "norme.dtd");
	save_objects_to_xml(world, root_node);
	xmlSaveFormatFileEnc("./testfiles/save.xml", doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	ft_putendl("Scene saved ! -> ./testfiles/save.xml");
}
