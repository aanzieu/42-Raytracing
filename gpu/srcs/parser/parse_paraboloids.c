/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paraboloids.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 11:22:36 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 14:17:50 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void				get_paraboloid_next(t_world *world, char **tmp,
		int i, t_paraboloid *para)
{
	if (ft_strnequ(tmp[i], "<top>", ft_strlen("<top>")))
		parse_point(&para->top, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&para->normal, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<rdistance>", ft_strlen("<rdistance>")))
		para->distance = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<height>", ft_strlen("<height>")))
		para->maxm = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&para->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&para->top, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&para->normal, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<reflexion>", ft_strlen("<reflexion>")))
		parse_reflexion(&para->reflexion_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<refraxion>", ft_strlen("<refraxion>")))
		parse_refraxion(&para->refraxion_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<chess>", ft_strlen("<chess>")))
		parse_color(&para->chess, tmp, world->line);
}

void					parse_paraboloid(t_world *world, t_list *lst)
{
	t_paraboloid	*para;
	char	**tmp;
	int		i;

	if (!(para = (t_paraboloid *)ft_memalloc(sizeof(t_paraboloid))))
		ft_putendl_fd("error malloc Paraboloid", 1);
	para->chess.r = -1;
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_paraboloid_next(world, tmp, i, para);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_paraboloid(&world->paraboloids_tmp, new_paraboloid(para, world->obj_id++));
	free(para);
}
