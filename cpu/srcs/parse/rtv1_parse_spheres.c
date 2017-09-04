/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_spheres.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:38:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 19:10:03 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void	get_sphere_next(t_scene *scene, char **tmp, int i, t_sphere *s)
{
	if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		s->radius = ft_atoi_double((tmp[i + 1]));
	else if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&s->pos, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&s->color, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&s->pos, tmp, scene->line);
}

void		get_sphere(t_scene *scene, t_list *lst)
{
	t_sphere	*s;
	char		**tmp;
	int			i;

	if (!(s = (t_sphere *)ft_memalloc(sizeof(t_sphere))))
		ft_putendl_fd("Error Malloc Sphere", 1);
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_sphere_next(scene, tmp, i, s);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_sphere(&scene->s, new_sphere(s));
	free(s);
}
