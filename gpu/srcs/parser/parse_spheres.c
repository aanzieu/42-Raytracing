/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:38:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/05 16:33:43 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void	parse_sphere_next(t_world *world, char **tmp, int i, t_sphere *s)
{
	if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		s->radius = ft_atoi_double((tmp[i + 1]));
	else if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&s->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&s->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&s->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<reflection>", ft_strlen("<reflection>")))
		parse_reflection(&s->reflection_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<refraction>", ft_strlen("<refraction>")))
		parse_refraction(&s->refraction_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<chess>", ft_strlen("<chess>")))
		parse_color(&s->chess, tmp, world->line);
}

void		parse_sphere(t_world *world, t_list *lst)
{
	t_sphere	*s;
	char		**tmp;
	int			i;

	if (!(s = (t_sphere *)ft_memalloc(sizeof(t_sphere))))
		ft_putendl_fd("Error Malloc Sphere", 1);
	s->chess = (t_color){-1, -1, -1};
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			parse_sphere_next(world, tmp, i, s);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_sphere(&world->spheres_tmp, new_sphere(s, world->id++));
	free(s);
}
