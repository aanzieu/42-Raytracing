/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 14:16:22 by PZC               #+#    #+#             */
/*   Updated: 2017/07/07 13:58:03 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	parse_rot_cam(t_camera *cam, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"x");
	if (is_numeric((const char *)nb))
    	rotate(&cam->look_at, ft_atoi((char *)nb), 'x');
    else
    	show_error_2("invalid rot camera value > x=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"y");
	if (is_numeric((const char *)nb))
    	rotate(&cam->look_at, ft_atoi((char *)nb), 'y');
    else
    	show_error_2("invalid rot camera value > y=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"z");
	if (is_numeric((const char *)nb))
    	rotate(&cam->look_at, ft_atoi((char *)nb), 'z');
    else
    	show_error_2("invalid rot camera value > z=", (const char *)nb);
    xmlFree(nb);
    cam->rotation = 1;
}

void		parse_camera(t_world *world, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;

	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			parse_vec3d(&world->camera.pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"dir")))
			parse_vec3d(&world->camera.look_at, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
			parse_tra(&world->camera.pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
			parse_rot_cam(&world->camera, cur);
		cur = cur->next;
	}
	get_camera_axes(&world->camera);
}
