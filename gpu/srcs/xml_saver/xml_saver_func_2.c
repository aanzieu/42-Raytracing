/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_saver_func_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huweber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 19:28:00 by huweber           #+#    #+#             */
/*   Updated: 2017/09/29 19:29:04 by huweber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

xmlNodePtr	xml_save_perlin(t_perlin *p, char *str, xmlNodePtr object)
{
	xmlNodePtr	node;
	char		*data;

	node = xmlNewChild(object, NULL, BAD_CAST(str), NULL);
	data = ft_itoa(p->is_set);
	xmlNewProp(node, BAD_CAST "is_set", BAD_CAST(data));
	ft_strdel(&data);
	data = ft_itoa(p->pre_set);
	xmlNewProp(node, BAD_CAST "pre_set", BAD_CAST(data));
	ft_strdel(&data);
	data = ft_itoa_double(p->scale);
	xmlNewProp(node, BAD_CAST "scale", BAD_CAST(data));
	ft_strdel(&data);
	data = ft_itoa_double(p->amount);
	xmlNewProp(node, BAD_CAST "amount", BAD_CAST(data));
	ft_strdel(&data);
	return (node);
}
