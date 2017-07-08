/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paraboloid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 16:25:26 by PZC               #+#    #+#             */
/*   Updated: 2017/07/07 16:33:13 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_paraboloid(t_paraboloid **alst, t_paraboloid *nw)
{
	t_paraboloid *curr;

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

void	parse_paraboloid(t_world *world, xmlNodePtr cur)
{
	t_paraboloid	*p;

	cur = cur->xmlChildrenNode;
	if (!(p = (t_paraboloid*)ft_memalloc(sizeof(t_paraboloid))))
		show_error("error malloc hyperboloid");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"top")))
			parse_vec3d(&p->top, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
			parse_vec3d(&p->normal, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
			parse_radius(&p->distance, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"height")))
			parse_height(&p->maxm, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&p->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
			parse_rot(&p->normal, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&p->reflexion_coef, cur);
		cur = cur->next;
	}
	add_paraboloid(&world->paraboloids_tmp, new_paraboloid(p));
	free(p);
}
