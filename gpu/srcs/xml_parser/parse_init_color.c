/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/18 17:19:35 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static double	color_to_coef(unsigned int color)
{
	if (color == 0)
		return (0);
	else
		return (color / (double)255);
}

void			parse_color(t_color *c, xmlNodePtr cur)
{
	xmlChar *str;

	str = xmlGetProp(cur, (const xmlChar *)"r");
	c->r = color_to_coef(ft_atoi_double((const char *)str));
	xmlFree(str);
	str = xmlGetProp(cur, (const xmlChar *)"g");
	c->g = color_to_coef(ft_atoi_double((const char *)str));
	xmlFree(str);
	str = xmlGetProp(cur, (const xmlChar *)"b");
	c->b = color_to_coef(ft_atoi_double((const char *)str));
	xmlFree(str);
}

void			parse_ambient(t_world *world, xmlNodePtr cur)
{
	t_ambient *a;

	cur = cur->xmlChildrenNode;
	if (!(a = (t_ambient*)ft_memalloc(sizeof(t_ambient))))
		show_error("error malloc ambient");
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			parse_color(&a->color, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			parse_intensity(&a->intensity, cur);
		cur = cur->next;
	}
	world->ambient.color = a->color;
	world->ambient.intensity = a->intensity;
	free(a);
}

void			parse_intensity(double *intensity_coef, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
		*intensity_coef = ft_atoi_double((const char *)nb);
	else
		show_error_2("invalid intensity value > data=", (const char *)nb);
	xmlFree(nb);
}
