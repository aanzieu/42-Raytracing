/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:38:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/04 18:25:42 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void init_radius(double *radius, xmlNodePtr cur)
{
	xmlChar *str;

	str = xmlGetProp(cur, (const xmlChar *)"data");
    *radius = ft_atoi_double((const char *)str);
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

static float	color_to_coef(unsigned int color)
{
	if (color == 0)
		return (0);
	else
		return (color / (float)255);
}

static void init_color(t_color *c, xmlNodePtr cur)
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

// static void	parse_sphere_next(t_world *world, char **tmp, int i, t_sphere *s)
// {
// 	if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
// 		s->radius = ft_atoi_double((tmp[i + 1]));
// 	else if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
// 		parse_point(&s->pos, tmp, world->line);
// 	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
// 		parse_color(&s->color, tmp, world->line);
// 	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
// 		parse_point_translation(&s->pos, tmp, world->line);
// 	else if (ft_strnequ(tmp[i], "<reflexion>", ft_strlen("<reflexion>")))
// 		parse_reflexion(&s->reflexion_coef, tmp, world->line);
// }

void		parse_sphere_xav(t_world *world, xmlNodePtr cur)
{
	t_sphere	*s;
	cur = cur->xmlChildrenNode;

	if (!(s = (t_sphere *)ft_memalloc(sizeof(t_sphere))))
		ft_putendl_fd("Error Malloc Sphere", 2);
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"pos")))
			init_vec3d(&s->pos, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"radius")))
			init_radius(&s->radius, cur);
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"color")))
			init_color(&s->color, cur);
		cur = cur->next;
	}
	add_sphere(&world->spheres_tmp, new_sphere(s));
	free(s);
}

// void		parse_sphere(t_world *world, t_list *lst)
// {
// 	t_sphere	*s;
// 	char		**tmp;
// 	int			i;

// 	if (!(s = (t_sphere *)ft_memalloc(sizeof(t_sphere))))
// 		ft_putendl_fd("Error Malloc Sphere", 1);
// 	while (lst && !ft_strequ(lst->content, "</surface>"))
// 	{
// 		tmp = ft_strsplit(lst->content, ' ');
// 		i = -1;
// 		while (tmp[++i] != NULL)
// 			parse_sphere_next(world, tmp, i, s);
// 		ft_cleanup_str(tmp);
// 		ft_memdel((void**)&tmp);
// 		lst = lst->next;
// 	}
// 	add_sphere(&world->spheres_tmp, new_sphere(s));
// 	free(s);
// }
