/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_cylinders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:40:37 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 18:20:42 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void	get_cylinder_next(t_scene *scene, char **tmp, int i, t_cy *cy)
{
	if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&cy->center, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&cy->normal, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		cy->angle = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<height>", ft_strlen("<height>")))
		cy->limit = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&cy->color, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&cy->center, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&cy->normal, tmp, scene->line);
}

void		get_cylinder(t_scene *scene, t_list *lst)
{
	t_cy	*cy;
	char	**tmp;
	int		i;

	if (!(cy = (t_cy *)ft_memalloc(sizeof(t_cy))))
		ft_putendl_fd("Error Malloc Cylinders", 1);
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_cylinder_next(scene, tmp, i, cy);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_cylinder(&scene->cy, new_cy(cy));
	free(cy);
}
