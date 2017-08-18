/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_saver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 13:52:50 by PZC               #+#    #+#             */
/*   Updated: 2017/08/18 14:04:54 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	save_xml_scene(t_world *world)
{
	xmlDocPtr	doc;
	xmlNodePtr	root_node;
	xmlNodePtr	camera;
	xmlNodePtr	node;

	doc = NULL;
	root_node = NULL;
	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL, BAD_CAST "scene");
	xmlDocSetRootElement(doc, root_node);
	xmlNewProp(root_node, BAD_CAST "name", BAD_CAST world->title + 13);
	xmlCreateIntSubset(doc, BAD_CAST "scene", NULL, BAD_CAST "norme.dtd");

	camera = xmlNewChild(root_node, NULL, BAD_CAST "camera", NULL);
	node = xmlNewChild(camera, NULL, BAD_CAST "pos", NULL);
	xmlNewProp(node, BAD_CAST "x", BAD_CAST ft_itoa(world->camera.pos.x));
	xmlNewProp(node, BAD_CAST "y", BAD_CAST ft_itoa(world->camera.pos.y));
	xmlNewProp(node, BAD_CAST "z", BAD_CAST ft_itoa(world->camera.pos.z));

	xmlSaveFormatFileEnc("./testfiles/save.xml", doc, "UTF-8", 1);

	printf("x=%f y=%f z=%f\n", world->camera.pos.x, world->camera.pos.y, world->camera.pos.z);
	printf("x=%f y=%f z=%f\n", world->camera.look_at.x, world->camera.look_at.y, world->camera.look_at.z);

	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	ft_putendl("Scene saved ! -> ./testfiles/save.xml");
}
