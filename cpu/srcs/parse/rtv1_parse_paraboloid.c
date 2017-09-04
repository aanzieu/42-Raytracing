/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_paraboloid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 17:45:05 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 19:10:35 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void				add_paraboloid(t_para **alst, t_para *nw)
{
	t_para *curr;

	if (!nw || !alst)
		return ;
	if (!*alst)
		*alst = nw;
	else
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = nw;
	}
}

t_para					*new_para(t_para *nw)
{
	t_para	*para;

	if (!(para = (t_para *)ft_memalloc(sizeof(t_para))))
		ft_putendl_fd("Erroc Malloc on paraboloid", 1);
	para->top = nw->top;
	para->normal = nw->normal;
	para->distance = nw->distance;
	para->maxm = nw->maxm;
	para->color = nw->color;
	para->next = NULL;
	return (para);
}

static void				get_paraboloid_next(t_scene *scene, char **tmp,
		int i, t_para *para)
{
	if (ft_strnequ(tmp[i], "<top>", ft_strlen("<top>")))
		parse_point(&para->top, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&para->normal, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<rdistance>", ft_strlen("<rdistance>")))
		para->distance = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<height>", ft_strlen("<height>")))
		para->maxm = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&para->color, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&para->top, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&para->normal, tmp, scene->line);
}

void					get_paraboloid(t_scene *scene, t_list *lst)
{
	t_para	*para;
	char	**tmp;
	int		i;

	if (!(para = (t_para *)ft_memalloc(sizeof(t_para))))
		ft_putendl_fd("error malloc Paraboloid", 1);
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_paraboloid_next(scene, tmp, i, para);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_paraboloid(&scene->para, new_para(para));
	free(para);
}
