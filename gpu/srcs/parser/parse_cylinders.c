/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:40:37 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/26 17:42:18 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

static void	get_cylinder_next(t_world *world, char **tmp, int i, t_cylinder *cy)
{
	if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&cy->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&cy->up, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		cy->radius = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&cy->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&cy->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&cy->up, tmp, world->line);
}

void		parse_cylinder(t_world *world, t_list *lst)
{
	t_cylinder	*cy;
	char		**tmp;
	int			i;

	if (!(cy = (t_cylinder *)ft_memalloc(sizeof(t_cylinder))))
		ft_putendl_fd("Error Malloc Cylinders", 1);
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_cylinder_next(world, tmp, i, cy);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_cylinder(&world->cylinders_tmp, new_cylinder(cy));
	free(cy);
}
