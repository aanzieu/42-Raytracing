/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hyperboloid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/29 16:37:02 by PZC              ###   ########.fr       */
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

void	handle_input_hyperboloid(t_hyperboloid *h, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"top")))
		parse_vec3d(&h->top, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
		parse_tra(&h->top, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
		parse_vec3d(&h->normal, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
		parse_radius(&h->radius, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"height")))
		parse_height(&h->maxm, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		parse_color(&h->color, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
		parse_color(&h->chess, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
		parse_rot(&h->normal, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		parse_reflection(&h->reflection_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		parse_reflection(&h->refraction_coef, cur);
}

void	parse_hyperboloid(t_world *world, xmlNodePtr cur)
{
	t_hyperboloid *h;

	cur = cur->xmlChildrenNode;
	if (!(h = (t_hyperboloid*)ft_memalloc(sizeof(t_hyperboloid))))
		show_error("error malloc hyperboloid");
	h->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		handle_input_hyperboloid(h, cur);
		cur = cur->next;
	}
	add_hyperboloid(&world->hyperboloids_tmp, new_hyperboloid(h, world->id++));
	free(h);
}
