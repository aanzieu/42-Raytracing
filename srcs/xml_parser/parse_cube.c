/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:14:24 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 17:15:23 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	add_cube(t_cube **alst, t_cube *nw)
{
	t_cube *curr;

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

void	handle_input_cube(t_cube *c, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"min")))
		parse_vec3d(&c->min, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"max")))
		parse_vec3d(&c->max, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
		parse_vec3d(&c->up, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		parse_color(&c->color, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
		parse_color(&c->chess, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		parse_reflection(&c->reflection_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		parse_refraction(&c->refraction_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"transparence")))
		parse_transparence(&c->transparence_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"perlin")))
		parse_perlin(&c->perlin, cur);
}

void	parse_cube(t_world *world, xmlNodePtr cur)
{
	t_cube *c;

	cur = cur->xmlChildrenNode;
	if (!(c = (t_cube *)ft_memalloc(sizeof(t_cube))))
		show_error("error malloc cube");
	c->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		handle_input_cube(c, cur);
		cur = cur->next;
	}
	add_cube(&world->cubes_tmp, new_cube(c, world->id++));
	free(c);
}
