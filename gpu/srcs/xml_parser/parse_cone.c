/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/16 13:02:32 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		add_cone(t_cone **alst, t_cone *nw)
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

static void	parse_cone_opt(t_cone *co, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
		parse_vec3d(&co->pos, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
		parse_tra(&co->pos, cur);
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
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
		parse_color(&co->chess, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
		parse_rot(&co->up, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		parse_reflection(&co->reflection_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		parse_reflection(&co->refraction_coef, cur);
}

void		parse_cone(t_world *world, xmlNodePtr cur)
{
	t_cone *co;

	cur = cur->xmlChildrenNode;
	if (!(co = (t_cone*)ft_memalloc(sizeof(t_cone))))
		show_error("error malloc cone");
	co->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		parse_cone_opt(co, cur);
		cur = cur->next;
	}
	add_cone(&world->cones_tmp, new_cone(co, world->id++));
	free(co);
}
