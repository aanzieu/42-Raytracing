/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:19:31 by PZC               #+#    #+#             */
/*   Updated: 2017/08/24 00:04:57 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	save_spheres_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object = NULL;
	xmlNodePtr	node = NULL;
	t_sphere	*ptr;

	ptr = world->spheres;
	while (world->spheres != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "sphere", NULL);
		node = xmlNewChild(object, NULL, BAD_CAST "pos", NULL);
		xmlNewProp(node, BAD_CAST "x", BAD_CAST ft_itoa_double(world->spheres->pos.x));
		xmlNewProp(node, BAD_CAST "y", BAD_CAST ft_itoa_double(world->spheres->pos.y));
		xmlNewProp(node, BAD_CAST "z", BAD_CAST ft_itoa_double(world->spheres->pos.z));
		world->spheres = world->spheres->next;
	}
	world->spheres = ptr;
}

void	save_cam_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object = NULL;
	xmlNodePtr	node = NULL;

	object = xmlNewChild(root_node, NULL, BAD_CAST "camera", NULL);
	node = xmlNewChild(object, NULL, BAD_CAST "pos", NULL);
	xmlNewProp(node, BAD_CAST "x", BAD_CAST ft_itoa_double(world->camera.pos.x));
	xmlNewProp(node, BAD_CAST "y", BAD_CAST ft_itoa_double(world->camera.pos.y));
	xmlNewProp(node, BAD_CAST "z", BAD_CAST ft_itoa_double(world->camera.pos.z));
	node = xmlNewChild(object, NULL, BAD_CAST "dir", NULL);
	xmlNewProp(node, BAD_CAST "x", BAD_CAST ft_itoa_double(world->camera.look_at.x));
	xmlNewProp(node, BAD_CAST "y", BAD_CAST ft_itoa_double(world->camera.look_at.y));
	xmlNewProp(node, BAD_CAST "z", BAD_CAST ft_itoa_double(world->camera.look_at.z));
}
