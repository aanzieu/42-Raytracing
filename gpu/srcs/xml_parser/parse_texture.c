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

void			parse_texture(t_texture *tex, xmlNodePtr cur)
{
	xmlChar *file;
	char	*full_path;

	file = xmlGetProp(cur, (const xmlChar *)"file");
	full_path = ft_strjoin("./textures/", (char *)file);
	printf("%s\n", full_path);
	if (!full_path)
		show_error_2("invalid texture path (./textures/file_name.bmp), file=",
			(const char *)file);
	else
		tex->tex = SDL_LoadBMP(full_path);
	if (!tex->tex)
		show_error_2("invalid texture path (./textures/file_name.bmp), file=",
			(const char *)file);
	tex->is_set = 1;
	tex->repeat = 1;
	tex->offset_x = 0;
	tex->offset_y = 0;
	ft_strdel(&full_path);
	SDL_LockSurface(tex->tex);
	xmlFree(file);
}
