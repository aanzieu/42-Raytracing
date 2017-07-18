/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/18 17:28:28 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_plan(t_plane **alst, t_plane *nw)
{
	t_plane *curr;

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

void	parse_plane(t_world *world, xmlNodePtr cur)
{
	t_plane *p;

	cur = cur->xmlChildrenNode;
	if (!(p = (t_plane *)ft_memalloc(sizeof(t_plane))))
		show_error("error malloc plane");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"origin")))
			parse_vec3d(&p->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
			parse_vec3d(&p->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
			parse_rot(&p->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&p->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&p->reflexion_coef, cur);
		cur = cur->next;
	}
	add_plan(&world->planes_tmp, new_plan(p));
	free(p);
}
