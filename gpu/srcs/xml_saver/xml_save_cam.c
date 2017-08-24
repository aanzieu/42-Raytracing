/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:03:42 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/24 18:54:10 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	save_cam_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;

	object = xmlNewChild(root_node, NULL, BAD_CAST "camera", NULL);
	node = xml_save_vec3d(&world->camera.pos, "pos", object);
	node = xml_save_vec3d(&world->camera.look_at, "dir", object);
}
