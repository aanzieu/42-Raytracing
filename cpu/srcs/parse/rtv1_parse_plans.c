/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_plans.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:33:11 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 09:12:33 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void	get_plan_next(t_scene *scene, char **tmp, int i, t_plan *p)
{
	if (ft_strnequ(tmp[i], "<origin>", ft_strlen("<origin>")))
		parse_point(&p->origin, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&p->normal, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&p->color, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&p->origin, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&p->normal, tmp, scene->line);
}

void		get_plan(t_scene *scene, t_list *lst)
{
	t_plan	*p;
	char	**tmp;
	int		i;

	if (!(p = (t_plan *)ft_memalloc(sizeof(t_plan))))
		ft_putendl_fd("Error Malloc Plan", 1);
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_plan_next(scene, tmp, i, p);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_plan(&scene->p, new_plan(p));
	free(p);
}
