/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hyperboloid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/18 17:17:41 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_hyperboloid(t_hyperboloid **alst, t_hyperboloid *nw)
{
	t_hyperboloid *curr;

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

void	parse_hyperboloid(t_world *world, xmlNodePtr cur)
{
	t_hyperboloid *h;

	cur = cur->xmlChildrenNode;
	if (!(h = (t_hyperboloid*)ft_memalloc(sizeof(t_hyperboloid))))
		show_error("error malloc hyperboloid");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"top")))
			parse_vec3d(&h->top, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
			parse_vec3d(&h->normal, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
			parse_radius(&h->radius, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"height")))
			parse_height(&h->maxm, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&h->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
			parse_rot(&h->normal, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&h->reflexion_coef, cur);
		cur = cur->next;
	}
	add_hyperboloid(&world->hyperboloids_tmp, new_hyperboloid(h));
	free(h);
}
