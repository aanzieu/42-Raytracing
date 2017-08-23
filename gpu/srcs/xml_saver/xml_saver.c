/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_saver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 13:52:50 by PZC               #+#    #+#             */
/*   Updated: 2017/08/23 20:08:52 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

static void	save_objects_to_xml(t_world *world, xmlNodePtr root_node)
{
	save_cam_to_xml(world, root_node);
	if (world->spheres_len != 0)
		save_spheres_to_xml(world, root_node);
}

void		save_xml_scene(t_world *world)
{
	xmlDocPtr	doc;
	xmlNodePtr	root_node;

	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL, BAD_CAST "scene");
	xmlDocSetRootElement(doc, root_node);
	xmlNewProp(root_node, BAD_CAST "name", BAD_CAST world->title + 13);
	xmlCreateIntSubset(doc, BAD_CAST "scene", NULL, BAD_CAST "norme.dtd");
	save_objects_to_xml(world, root_node);

	//printf("x:%f y:%f z:%f\n", world->camera.look_at.x, world->camera.look_at.y, world->camera.look_at.z);

	xmlSaveFormatFileEnc("./testfiles/save.xml", doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	ft_putendl("Scene saved ! -> ./testfiles/save.xml");
}
