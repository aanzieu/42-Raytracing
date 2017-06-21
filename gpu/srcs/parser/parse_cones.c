/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:41:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/21 12:05:41 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void	get_cone_next(t_world *world, char **tmp, int i, t_cone *co)
{
	if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&co->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&co->up, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		co->half_angle = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&co->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&co->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&co->up, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<reflexion>", ft_strlen("<reflexion>")))
		parse_reflexion(&co->reflexion_coef, tmp, world->line);
}

void		parse_cone(t_world *world, t_list *lst)
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
			get_cone_next(world, tmp, i, co);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_cone(&world->cones_tmp, new_cone(co));
	free(co);
}
