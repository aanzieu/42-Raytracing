/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/18 17:27:36 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	add_light(t_light **alst, t_light *nw)
{
	t_light *curr;

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

void	parse_light(t_world *world, xmlNodePtr cur)
{
	t_light *l;

	cur = cur->xmlChildrenNode;
	if (!(l = (t_light*)ft_memalloc(sizeof(t_light))))
		show_error("error malloc light");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			parse_vec3d(&l->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"dir")))
			parse_vec3d(&l->dir, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&l->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			parse_intensity(&l->intensity_coef, cur);
		cur = cur->next;
	}
	add_light(&world->lights_tmp, new_light(l));
	free(l);
}
