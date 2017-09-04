/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paraboloid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/16 13:20:34 by PZC              ###   ########.fr       */
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

void	handle_input_paraboloid(t_paraboloid *p, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"top")))
		parse_vec3d(&p->top, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
		parse_tra(&p->top, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
		parse_vec3d(&p->normal, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
		parse_radius(&p->distance, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"height")))
		parse_height(&p->maxm, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		parse_color(&p->color, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
		parse_color(&p->chess, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
		parse_rot(&p->normal, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		parse_reflection(&p->reflection_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		parse_refraction(&p->refraction_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"transparence")))
		parse_transparence(&p->transparence_coef, cur);
}

void	parse_paraboloid(t_world *world, xmlNodePtr cur)
{
	t_paraboloid	*p;

	cur = cur->xmlChildrenNode;
	if (!(p = (t_paraboloid*)ft_memalloc(sizeof(t_paraboloid))))
		show_error("error malloc hyperboloid");
	p->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		handle_input_paraboloid(p, cur);
		cur = cur->next;
	}
	add_paraboloid(&world->paraboloids_tmp, new_paraboloid(p, world->id++));
	free(p);
}
