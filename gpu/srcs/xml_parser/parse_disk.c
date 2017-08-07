/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 14:15:35 by PZC               #+#    #+#             */
/*   Updated: 2017/07/18 17:16:55 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void		add_disk(t_disk **alst, t_disk *nw)
{
	t_disk *curr;

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

static void	parse_radius_disk(t_disk *d, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
	{
		d->radius = ft_atoi_double((const char *)nb);
		d->radius_squared = pow(d->radius, 2);
	}
	else
		show_error_2("invalid disk value > radius=", (const char *)nb);
	xmlFree(nb);
}

void		parse_disk(t_world *world, xmlNodePtr cur)
{
	t_disk	*d;

	cur = cur->xmlChildrenNode;
	if (!(d = (t_disk*)ft_memalloc(sizeof(t_disk))))
		show_error("error malloc disk");
	d->chess = (t_color){-1, -1, -1};
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"origin")))
			parse_vec3d(&d->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"normal")))
			parse_vec3d(&d->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
			parse_radius_disk(d, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&d->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"chess")))
			parse_color(&d->chess, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"rot")))
			parse_rot(&d->up, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"reflection")))
			parse_reflection(&d->reflection_coef, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"refraction")))
			parse_reflection(&d->refraction_coef, cur);
		cur = cur->next;
	}
	add_disk(&world->disks_tmp, new_disk(d, world->id++));
	free(d);
}
