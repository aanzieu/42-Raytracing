/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/08/24 16:23:07 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_sphere(t_sphere **alst, t_sphere *nw)
{
	t_sphere *curr;

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

void	handle_input_sphere(t_sphere *s, xmlNodePtr cur)
{
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
		parse_vec3d(&s->pos, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"tra")))
		parse_tra(&s->pos, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
		parse_radius(&s->radius, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
		parse_color(&s->color, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
		parse_color(&s->chess, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"negative")))
		parse_negative(&s->negative, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
		parse_reflection(&s->reflection_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
		parse_refraction(&s->refraction_coef, cur);
	if ((!xmlStrcmp(cur->name, (const xmlChar *)"transparence")))
		parse_transparence(&s->transparence_coef, cur);
}

void	parse_sphere(t_world *world, xmlNodePtr cur)
{
	t_sphere	*s;

	cur = cur->xmlChildrenNode;
	if (!(s = (t_sphere*)ft_memalloc(sizeof(t_sphere))))
		show_error("error malloc sphere");
	s->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		handle_input_sphere(s, cur);
		cur = cur->next;
	}
	add_sphere(&world->spheres_tmp, new_sphere(s, world->id++));
	free(s);
}
