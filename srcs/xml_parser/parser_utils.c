/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:31:55 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/10/03 14:10:29 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		is_numeric(const char *str)
{
	int i;
	int p;

	i = 0;
	p = 0;
	if (str[i] == '\0')
		show_error("empty value in the xml file");
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			p++;
		else
		{
			if (!(ft_isdigit(str[i])))
				return (0);
		}
		if (p > 1)
			return (0);
		i++;
	}
	return (1);
}

int		parser_checker(char *argv)
{
	xmlParserCtxtPtr	ctxt;
	xmlDocPtr			doc;

	if (!(ctxt = xmlNewParserCtxt()))
		show_error("failed to allocate parser context");
	if (!(doc = xmlCtxtReadFile(ctxt, argv, NULL, XML_PARSE_DTDVALID)))
	{
		xmlFreeDoc(doc);
		xmlFreeParserCtxt(ctxt);
		return (0);
	}
	else
	{
		if (ctxt->valid == 0)
		{
			xmlFreeDoc(doc);
			xmlFreeParserCtxt(ctxt);
			return (0);
		}
		xmlFreeDoc(doc);
		xmlFreeParserCtxt(ctxt);
		return (1);
	}
}
