/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 13:20:02 by PZC               #+#    #+#             */
/*   Updated: 2017/07/06 16:02:11 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
**	Find objects and execute their own parsing associate
*/

static void		get_object_node(t_world *world, xmlNodePtr obj)
{
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"camera")))
		parse_camera(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"light")))
		parse_light(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"plane")))
		parse_plane(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"sphere")))
		parse_sphere(world, obj);
	if (!(xmlStrcmp(obj->name, (const xmlChar *)"ambient")))
		parse_ambient(world, obj);
}

/*
**	Initialize the title of the scene
**  Parse all the objects inside the scene
*/

static void		parse_file(t_world *world, const char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlChar *title;

	if (!(doc = xmlParseFile(docname)))
		show_error("xml file not parsed successfully");
	if (!(cur = xmlDocGetRootElement(doc)))
	{
		xmlFreeDoc(doc);
		show_error("empty file");
	}
	title = xmlGetProp(cur, (const xmlChar *)"name");
	world->title = ft_strjoin("RT - Scene : ",(char*)title);
	xmlFree(title);
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if (xmlStrcmp(cur->name, (const xmlChar *)"text"))
			get_object_node(world, cur);
		cur = cur->next;
	}
	xmlFreeDoc(doc);
}

/*
**	Parser that use libxml2 to well parse the xml file
**  who describe the scene. If it's not valid it quit properly
*/

void			parse_rtv1(t_world *world, char *argv)
{
	xmlParserCtxtPtr ctxt;
	xmlDocPtr doc;

	if (!(ctxt = xmlNewParserCtxt()))
		show_error("failed to allocate parser context");
	if (!(doc = xmlCtxtReadFile(ctxt, argv, NULL, XML_PARSE_DTDVALID)))
		show_error("failed to parse the xml file");
	else
	{
		if (ctxt->valid == 0)
			show_error("xml file error");
		else
			parse_file(world, argv);
		xmlFreeDoc(doc);
	}
	xmlFreeParserCtxt(ctxt);
}
