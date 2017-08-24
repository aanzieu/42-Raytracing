/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_saver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 17:20:24 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/24 18:09:07 by xpouzenc         ###   ########.fr       */
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

	//printf("r:%f g:%f b:%f\n", world->spheres->color.r, world->spheres->color.g, world->spheres->color.b);

	xmlSaveFormatFileEnc("./testfiles/save.xml", doc, "UTF-8", 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	ft_putendl("Scene saved ! -> ./testfiles/save.xml");
}
