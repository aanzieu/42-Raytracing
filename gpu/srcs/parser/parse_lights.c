/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:34:12 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/04 18:08:14 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

// static void	get_light_next(t_world *world, char **tmp, int i, t_light *l)
// {
// 	if (ft_strnequ(tmp[i], "<position>", ft_strlen("<position>")))
// 		parse_point(&l->pos, tmp, world->line);
// 	else if (ft_strnequ(tmp[i], "<direction>", ft_strlen("<direction>")))
// 		parse_point(&l->dir, tmp, world->line);
// 	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
// 		parse_color(&l->color, tmp, world->line);
// 	else if (ft_strnequ(tmp[i], "<intensity>", ft_strlen("<intensity>")))
// 		parse_intensity(&l->intensity_coef, tmp, world->line);
// }

static void init_intensity(double *intensity_coef, xmlNodePtr cur)
{
	xmlChar *str;

	str = xmlGetProp(cur, (const xmlChar *)"data");
    *intensity_coef = ft_atoi_double((const char *)str);
    xmlFree(str);
}

static void init_vec3d(t_vec3d *pos, xmlNodePtr cur)
{
	xmlChar *str;

	str = xmlGetProp(cur, (const xmlChar *)"x");
    pos->x = ft_atoi_double((const char *)str);
    xmlFree(str);
    str = xmlGetProp(cur, (const xmlChar *)"y");
    pos->y = ft_atoi_double((const char *)str);
    xmlFree(str);
    str = xmlGetProp(cur, (const xmlChar *)"z");
    pos->z = ft_atoi_double((const char *)str);
    xmlFree(str);
}

void		parse_light_xav(t_world *world, xmlNodePtr cur)
{
	t_light *l;
	cur = cur->xmlChildrenNode;

	if (!(l = (t_light *)ft_memalloc(sizeof(t_light))))
 		ft_putendl_fd("Error Malloc Light", 2);
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			init_vec3d(&l->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"intensity")))
			init_intensity(&l->intensity_coef, cur);
		cur = cur->next;
	}
	add_light(&world->lights_tmp, new_light(l));
 	free(l);
}

// void		parse_light(t_world *world, t_list *lst)
// {
// 	t_light *l;
// 	char	**tmp;
// 	int		i;

// 	if (!(l = (t_light *)ft_memalloc(sizeof(t_light))))
// 		ft_putendl_fd("Error Malloc Light", 1);
// 	while (lst && !ft_strequ(lst->content, "</light>"))
// 	{
// 		tmp = ft_strsplit(lst->content, ' ');
// 		i = -1;
// 		while (tmp[++i] != NULL)
// 		{
// 			get_light_next(world, tmp, i, l);
// 		}
// 		ft_cleanup_str(tmp);
// 		ft_memdel((void**)&tmp);
// 		lst = lst->next;
// 	}
// 	add_light(&world->lights_tmp, new_light(l));
// 	free(l);
// }
