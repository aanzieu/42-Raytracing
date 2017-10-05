/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_perlin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 19:03:54 by huweber           #+#    #+#             */
/*   Updated: 2017/09/29 19:06:06 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		parse_perlin_next(t_perlin *p, xmlNodePtr cur, xmlChar *nb)
{
	nb = xmlGetProp(cur, (const xmlChar *)"amount");
	if (is_numeric((const char *)nb))
		p->amount = ft_atoi_double((const char *)nb);
	else
		show_error_2("invalid amount value (0 to +inf)> amount=",
					(const char *)nb);
	xmlFree(nb);
}

void			parse_perlin(t_perlin *p, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"is_set");
	if (is_numeric((const char *)nb))
		p->is_set = ft_atoi((char *)nb);
	else
		show_error_2("invalid set value (0 || 1) isSet=", (const char *)nb);
	xmlFree(nb);
	nb = xmlGetProp(cur, (const xmlChar *)"pre_set");
	if (is_numeric((const char *)nb))
		p->pre_set = ft_atoi((char *)nb);
	else
		show_error_2("invalid pre_set value (0 || 1)> preSet=",
					(const char *)nb);
	xmlFree(nb);
	nb = xmlGetProp(cur, (const xmlChar *)"scale");
	if (is_numeric((const char *)nb))
		p->scale = ft_atoi_double((const char *)nb);
	else
		show_error_2("invalid scale value (0 to 1)> scale=",
					(const char *)nb);
	xmlFree(nb);
	parse_perlin_next(p, cur, nb);
}
