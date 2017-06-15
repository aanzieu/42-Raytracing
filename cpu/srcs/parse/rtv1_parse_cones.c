/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_cones.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:41:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 09:12:02 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void	get_cone_next(t_scene *scene, char **tmp, int i, t_cone *co)
{
	if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&co->center, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&co->normal, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		co->angle = tan(deg_to_radian(ft_atoi_double(tmp[i + 1]) / 2));
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&co->color, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&co->center, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&co->normal, tmp, scene->line);
}

void		get_cone(t_scene *scene, t_list *lst)
{
	t_cone		*co;
	char		**tmp;
	int			i;

	if (!(co = (t_cone *)ft_memalloc(sizeof(t_cone))))
		ft_putendl_fd("error malloc Cones", 1);
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_cone_next(scene, tmp, i, co);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_cone(&scene->co, new_cone(co));
	free(co);
}
