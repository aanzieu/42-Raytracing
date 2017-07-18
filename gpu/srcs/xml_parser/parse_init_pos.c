/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 17:23:28 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/07/18 17:26:32 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	parse_radius(double *radius, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
		*radius = ft_atoi_double((const char *)nb);
	else
		show_error_2("invalid radius value > radius=", (const char *)nb);
	xmlFree(nb);
}

void	parse_height(double *height, xmlNodePtr cur)
{
	xmlChar *nb;

	nb = xmlGetProp(cur, (const xmlChar *)"data");
	if (is_numeric((const char *)nb))
		*height = ft_atoi_double((const char *)nb);
	else
		show_error_2("invalid height value > height=", (const char *)nb);
	xmlFree(nb);
}

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
