/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_save_spheres.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:10:07 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/24 19:14:52 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	save_spheres_to_xml(t_world *world, xmlNodePtr root_node)
{
	xmlNodePtr	object;
	xmlNodePtr	node;
	t_sphere	*ptr;

	ptr = world->spheres;
	while (world->spheres != NULL)
	{
		object = xmlNewChild(root_node, NULL, BAD_CAST "sphere", NULL);
		node = xml_save_vec3d(&world->spheres->pos, "pos", object);
		node = xml_save_one_data(world->spheres->radius, "radius", object);
		node = xml_save_rgb(&world->spheres->color, "color", object);
		if (world->spheres->chess.r != -1)
			node = xml_save_rgb(&world->spheres->chess, "chess", object);
		node = xml_save_one_data(world->spheres->reflection_coef, "reflection", object);
		node = xml_save_one_data(world->spheres->refraction_coef, "refraction", object);
		world->spheres = world->spheres->next;
	}
	world->spheres = ptr;
}
