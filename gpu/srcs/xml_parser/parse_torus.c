/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_torus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:25:36 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:50:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void			add_torus(t_torus **alst, t_torus *nw)
{
	t_torus *curr;

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

static void		handle_input_torus(t_torus *t, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
		parse_vec3d(&t->pos, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
		parse_tra(&t->pos, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius_small")))
		parse_radius(&t->radius_small, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius_big")))
		parse_radius(&t->radius_big, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		parse_color(&t->color, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
		parse_color(&t->chess, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		parse_reflection(&t->reflection_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		parse_refraction(&t->refraction_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"transparence")))
		parse_transparence(&t->transparence_coef, cur);
}

void			parse_torus(t_world *world, xmlNodePtr cur)
{
	t_torus *t;

	cur = cur->xmlChildrenNode;
	if (!(t = (t_torus *)ft_memalloc(sizeof(t_torus))))
		show_error("error malloc torus");
	t->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		handle_input_torus(t, cur);
		cur = cur->next;
	}
	add_torus(&world->torus_tmp, new_torus(t, world->id++));
	free(t);
}
