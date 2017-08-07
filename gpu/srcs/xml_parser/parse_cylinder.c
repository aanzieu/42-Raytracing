/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/18 17:16:39 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_cylinder(t_cylinder **alst, t_cylinder *nw)
{
	t_cylinder *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = nw;
	}
}

void	parse_cylinder(t_world *world, xmlNodePtr cur)
{
	t_cylinder	*cy;

	cur = cur->xmlChildrenNode;
	if (!(cy = (t_cylinder*)ft_memalloc(sizeof(t_cylinder))))
		show_error("error malloc cylinder");
	cy->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			parse_vec3d(&cy->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
			parse_vec3d(&cy->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
			parse_radius(&cy->radius, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&cy->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
			parse_color(&cy->chess, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
			parse_rot(&cy->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&cy->reflection_coef, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
			parse_reflection(&cy->refraction_coef, cur);
		cur = cur->next;
	}
	add_cylinder(&world->cylinders_tmp, new_cylinder(cy, world->id++));
	free(cy);
}
