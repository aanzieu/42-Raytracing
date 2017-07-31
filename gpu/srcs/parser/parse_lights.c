/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:34:12 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/21 18:13:17 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void	get_light_next(t_world *world, char **tmp, int i, t_light *l)
{
	if (ft_strnequ(tmp[i], "<position>", ft_strlen("<position>")))
		parse_point(&l->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<direction>", ft_strlen("<direction>")))
		parse_point(&l->dir, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&l->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<intensity>", ft_strlen("<intensity>")))
		parse_intensity(&l->intensity_coef, tmp, world->line);
}

void		parse_light(t_world *world, t_list *lst)
{
	t_light *l;
	char	**tmp;
	int		i;

	if (!(l = (t_light *)ft_memalloc(sizeof(t_light))))
		ft_putendl_fd("Error Malloc Light", 1);
	while (lst && !ft_strequ(lst->content, "</light>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
		{
			get_light_next(world, tmp, i, l);
		}
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_light(&world->lights_tmp, new_light(l));
	free(l);
}
