/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 16:32:09 by PZC               #+#    #+#             */
/*   Updated: 2017/07/06 15:44:39 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		add_sphere(t_sphere **alst, t_sphere *nw)
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

static void	parse_radius(double *radius, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
		*radius = ft_atoi_double((const char *)nb);
	else
		show_error_2("invalid sphere value > radius=", (const char *)nb);
	xmlFree(nb);
}

void		parse_sphere(t_world *world, xmlNodePtr cur)
{
	t_sphere	*s;
	cur = cur->xmlChildrenNode;

	if (!(s = (t_sphere*)ft_memalloc(sizeof(t_sphere))))
		show_error("error malloc sphere");
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
			parse_reflection(&s->reflexion_coef, cur);
		cur = cur->next;
	}
	add_sphere(&world->spheres_tmp, new_sphere(s));
	free(s);
}
