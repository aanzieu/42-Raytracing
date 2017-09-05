/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_lights.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:34:12 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 09:12:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void	get_light_next(t_scene *scene, char **tmp, int i, t_light *l)
{
	if (ft_strnequ(tmp[i], "<position>", ft_strlen("<position>")))
		parse_point(&l->position, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<intensity>", ft_strlen("<intensity>")))
		parse_color(&l->color, tmp, scene->line);
}

void		get_light(t_scene *scene, t_list *lst)
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
			get_light_next(scene, tmp, i, l);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_light(&scene->l, new_light(l));
	free(l);
}
