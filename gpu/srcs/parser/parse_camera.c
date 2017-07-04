/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:24:17 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/04 17:12:21 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <parse.h>

static int is_numeric(const char *str)
{
	int i;
	int p;

	i = 0;
	p = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			p++;
		if (!(ft_isdigit(str[i])) && p > 1)
			return (0);
		i++;
	}
	return (1);
}

static void init_vec3d(t_vec3d *pos, xmlNodePtr cur)
{
	xmlChar *str;

	str = xmlGetProp(cur, (const xmlChar *)"x");
	if (is_numeric((const char *)str))
    	pos->x = ft_atoi_double((const char *)str);
    else
    	printf("ERROR\n");
    xmlFree(str);
    str = xmlGetProp(cur, (const xmlChar *)"y");
    pos->y = ft_atoi_double((const char *)str);
    xmlFree(str);
    str = xmlGetProp(cur, (const xmlChar *)"z");
    pos->z = ft_atoi_double((const char *)str);
    xmlFree(str);
}

void		parse_camera_xav(t_world *world, xmlNodePtr cur)
{
	cur = cur->xmlChildrenNode;

	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"viewPoint")))
			init_vec3d(&world->camera.pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"viewDir")))
			init_vec3d(&world->camera.look_at, cur);
		cur = cur->next;
	}
	get_camera_axes(&world->camera);
}

// void		parse_camera(t_world *world, t_camera *cam, t_list *lst)
// {
// 	(void)cam;
// 	char	**tmp;
// 	int		i;

// 	while (lst && !ft_strequ(lst->content, "</camera>"))
// 	{
// 		tmp = ft_strsplit(lst->content, ' ');
// 		i = -1;
// 		while (tmp[++i] != NULL)
// 		{
// 			if (ft_strnequ(tmp[i], "<viewpoint>", ft_strlen("<viewpoint>")))
// 				parse_point(&world->camera.pos, tmp, world->line);
// 			else if (ft_strnequ(tmp[i], "<viewdir>", ft_strlen("<viewdir>")))
// 				parse_point(&world->camera.look_at, tmp, world->line);
// 			else if (ft_strnequ(tmp[i], "<translation>",
// 						ft_strlen("<translation>")))
// 				parse_point_translation(&world->camera.pos, tmp, world->line);
// 			else if (ft_strnequ(tmp[i], "<rotation>",
// 				ft_strlen("<rotation>")))
// 				parse_rotation_cam(&world->camera, tmp, world->line);
// 		}
// 		ft_cleanup_str(tmp);
// 		ft_memdel((void**)&tmp);
// 		lst = lst->next;
// 	}
// 	get_camera_axes(&world->camera);
// }
