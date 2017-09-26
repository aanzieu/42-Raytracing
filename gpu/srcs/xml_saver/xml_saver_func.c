/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_saver_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 18:46:19 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/18 17:47:16 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

static unsigned int	coef_to_color(double color)
{
	if (color == 0)
		return (0);
	else
		return (color * (double)255);
}

xmlNodePtr			xml_save_vec3d(t_vec3d *v, char *str, xmlNodePtr object)
{
	xmlNodePtr	node;
	char		*data;

	node = xmlNewChild(object, NULL, BAD_CAST(str), NULL);
	data = ft_itoa_double(v->x);
	xmlNewProp(node, BAD_CAST "x", BAD_CAST(data));
	ft_strdel(&data);
	data = ft_itoa_double(v->y);
	xmlNewProp(node, BAD_CAST "y", BAD_CAST(data));
	ft_strdel(&data);
	data = ft_itoa_double(v->z);
	xmlNewProp(node, BAD_CAST "z", BAD_CAST(data));
	ft_strdel(&data);
	return (node);
}

xmlNodePtr			xml_save_rgb(t_color *c, char *str, xmlNodePtr object)
{
	xmlNodePtr	node;
	char		*data;

	node = xmlNewChild(object, NULL, BAD_CAST(str), NULL);
	data = ft_itoa(coef_to_color(c->r));
	xmlNewProp(node, BAD_CAST "r", BAD_CAST(data));
	ft_strdel(&data);
	data = ft_itoa(coef_to_color(c->g));
	xmlNewProp(node, BAD_CAST "g", BAD_CAST(data));
	ft_strdel(&data);
	data = ft_itoa(coef_to_color(c->b));
	xmlNewProp(node, BAD_CAST "b", BAD_CAST(data));
	ft_strdel(&data);
	return (node);
}

xmlNodePtr			xml_save_one_data(double d, char *str, xmlNodePtr object)
{
	xmlNodePtr	node;
	char		*data;

	node = xmlNewChild(object, NULL, BAD_CAST(str), NULL);
	data = ft_itoa_double(d);
	xmlNewProp(node, BAD_CAST "data", BAD_CAST(data));
	ft_strdel(&data);
	return (node);
}

xmlNodePtr			xml_save_one_data_str(int t, char *str, xmlNodePtr object)
{
	xmlNodePtr	node;
	char		*data;

	node = xmlNewChild(object, NULL, BAD_CAST(str), NULL);
	if (t == LIGHT_P)
		data = ft_strdup("POINT");
	else if (t == LIGHT_BOX)
		data = ft_strdup("BOX");
	else
		data = ft_strdup("SPHERE");
	if (!data)
		show_error("Error on light type malloc in xmlSaver.");
	xmlNewProp(node, BAD_CAST "data", BAD_CAST(data));
	ft_strdel(&data);
	return (node);
}
