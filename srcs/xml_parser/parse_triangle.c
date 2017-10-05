/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:21:24 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:26:04 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void			add_triangle(t_triangle **alst, t_triangle *nw)
{
	t_triangle *curr;

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

static void		handle_input_triangle(t_triangle *t, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
		parse_vec3d(&t->pos, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
		parse_vec3d(&t->up, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"v1")))
		parse_tra(&t->v1, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"v2")))
		parse_tra(&t->v2, cur);
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
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"perlin")))
		parse_perlin(&t->perlin, cur);
}

void			parse_triangle(t_world *world, xmlNodePtr cur)
{
	t_triangle *t;

	cur = cur->xmlChildrenNode;
	if (!(t = (t_triangle *)ft_memalloc(sizeof(t_triangle))))
		show_error("error malloc triangle");
	t->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		handle_input_triangle(t, cur);
		cur = cur->next;
	}
	add_triangle(&world->triangles_tmp, new_triangle(t, world->id++));
	free(t);
}
