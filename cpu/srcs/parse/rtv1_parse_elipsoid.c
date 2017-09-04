/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_elipsoid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:46:09 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 19:09:32 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void				add_elipsoid(t_elips **alst, t_elips *nw)
{
	t_elips *curr;

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

t_elips					*new_elips(t_elips *nw)
{
	t_elips		*elips;

	if (!(elips = (t_elips *)ft_memalloc(sizeof(t_elips))))
		ft_putendl_fd("Erroc Malloc on paraboloid", 1);
	elips->center = nw->center;
	elips->normal = nw->normal;
	elips->kdistance = nw->kdistance;
	elips->radius = nw->radius;
	elips->color = nw->color;
	elips->sol = nw->sol;
	elips->next = NULL;
	return (elips);
}

static void				get_elipsoid_next(t_scene *scene, char **tmp,
		int i, t_elips *elips)
{
	if (ft_strnequ(tmp[i], "<center>", ft_strlen("<center>")))
		parse_point(&elips->center, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&elips->normal, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<kdistance>", ft_strlen("<kdistance>")))
		elips->kdistance = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
		elips->radius = ft_atoi_double(tmp[i + 1]);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&elips->color, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&elips->center, tmp, scene->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&elips->normal, tmp, scene->line);
}

void					get_elipsoid(t_scene *scene, t_list *lst)
{
	t_elips	*elips;
	char	**tmp;
	int		i;

	if (!(elips = (t_elips *)ft_memalloc(sizeof(t_elips))))
		ft_putendl_fd("error malloc Paraboloid", 1);
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_elipsoid_next(scene, tmp, i, elips);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_elipsoid(&scene->elips, new_elips(elips));
	free(elips);
}
