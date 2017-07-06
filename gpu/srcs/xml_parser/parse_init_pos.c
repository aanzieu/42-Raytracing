/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 14:24:20 by PZC               #+#    #+#             */
/*   Updated: 2017/07/06 13:44:42 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_vec3d(t_vec3d *v, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"x");
	if (is_numeric((const char *)nb))
    	v->x = ft_atoi_double((const char *)nb);
    else
    	show_error_2("invalid pos value > x=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"y");
	if (is_numeric((const char *)nb))
    	v->y = ft_atoi_double((const char *)nb);
    else
    	show_error_2("invalid pos value > y=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"z");
	if (is_numeric((const char *)nb))
    	v->z = ft_atoi_double((const char *)nb);
    else
    	show_error_2("invalid pos value > z=", (const char *)nb);
    xmlFree(nb);
}

void	parse_tra(t_vec3d *v, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"x");
	if (is_numeric((const char *)nb))
    	v->x += ft_atoi_double((const char *)nb);
    else
    	show_error_2("invalid tra value > x=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"y");
	if (is_numeric((const char *)nb))
    	v->y += ft_atoi_double((const char *)nb);
    else
    	show_error_2("invalid tra value > y=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"z");
	if (is_numeric((const char *)nb))
    	v->z += ft_atoi_double((const char *)nb);
    else
    	show_error_2("invalid tra value > z=", (const char *)nb);
    xmlFree(nb);
}

void	parse_rot(t_vec3d *v, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"x");
	if (is_numeric((const char *)nb))
    	rotate(v, ft_atoi((char *)nb), 'x');
    else
    	show_error_2("invalid rot value > x=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"y");
	if (is_numeric((const char *)nb))
    	rotate(v, ft_atoi((char *)nb), 'y');
    else
    	show_error_2("invalid rot value > y=", (const char *)nb);
    xmlFree(nb);
    nb = xmlGetProp(cur, (const xmlChar *)"z");
	if (is_numeric((const char *)nb))
    	rotate(v, ft_atoi((char *)nb), 'z');
    else
    	show_error_2("invalid rot value > z=", (const char *)nb);
    xmlFree(nb);
}
