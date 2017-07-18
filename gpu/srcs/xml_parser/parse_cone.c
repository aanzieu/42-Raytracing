/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/18 17:16:31 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_cone(t_cone **alst, t_cone *nw)
{
	t_cone *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
		{
			curr = curr->next;
		}
		curr->next = nw;
	}
}

void	parse_cone(t_world *world, xmlNodePtr cur)
{
	t_cone *co;

	cur = cur->xmlChildrenNode;
	if (!(co = (t_cone*)ft_memalloc(sizeof(t_cone))))
		show_error("error malloc cone");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			parse_vec3d(&co->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
			parse_vec3d(&co->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
			parse_radius(&co->half_angle, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"height")))
			parse_height(&co->height, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"min")))
			parse_vec3d(&co->min, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"max")))
			parse_vec3d(&co->max, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&co->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
			parse_rot(&co->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&co->reflexion_coef, cur);
		cur = cur->next;
	}
	add_cone(&world->cones_tmp, new_cone(co));
	free(co);
}
