/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mobius.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:21:13 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:21:14 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	add_mobius(t_mobius **alst, t_mobius *nw)
{
	t_mobius *curr;

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

void	parse_mobius(t_world *world, xmlNodePtr cur)
{
	t_mobius	*s;

	cur = cur->xmlChildrenNode;
	if (!(s = (t_mobius*)ft_memalloc(sizeof(t_mobius))))
		show_error("error malloc mobius");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			parse_vec3d(&s->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
			parse_tra(&s->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
			parse_radius(&s->radius, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&s->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&s->reflection_coef, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
			parse_refraction(&s->refraction_coef, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"transparence")))
			parse_transparence(&s->transparence_coef, cur);
		cur = cur->next;
	}
	add_mobius(&world->mobius_tmp, new_mobius(s, world->id++));
	free(s);
}
