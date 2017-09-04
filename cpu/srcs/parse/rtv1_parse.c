/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:24:17 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/12 17:05:09 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

static void		free_lst(t_list **lst)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->content);
		(*lst)->content_size = 0;
		free(*lst);
		(*lst) = next;
	}
}

static void		get_type(t_scene *scene, t_list *lst, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '"')
		i++;
	tmp = ft_strsub(str, ++i, ft_strlen(str));
	if (ft_strnequ(tmp, "sphere", ft_strlen("sphere")))
		get_sphere(scene, lst->next);
	else if (ft_strnequ(tmp, "plan", ft_strlen("plan")))
		get_plan(scene, lst->next);
	else if (ft_strnequ(tmp, "cylinder", ft_strlen("cylinder")))
		get_cylinder(scene, lst->next);
	else if (ft_strnequ(tmp, "cone", ft_strlen("cone")))
		get_cone(scene, lst->next);
	else if (ft_strnequ(tmp, "paraboloid", ft_strlen("paraboloid")))
		get_paraboloid(scene, lst->next);
	else if (ft_strnequ(tmp, "elipsoid", ft_strlen("elipsoid")))
		get_elipsoid(scene, lst->next);
	ft_memdel((void**)&tmp);
	lst = lst->next;
}

static void		get_surface(t_scene *scene, t_list *lst)
{
	char	**tmp;
	int		i;

	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		i = 0;
		tmp = ft_strsplit(lst->content, ' ');
		while (tmp[i] != NULL)
		{
			if (ft_strstr(tmp[i], "type="))
				get_type(scene, lst, tmp[i]);
			i++;
		}
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
}

static void		parse_lst(t_env *e, t_list *lst)
{
	e->scene = get_scene(lst);
	while (lst && !ft_strequ(lst->content, "</scene>"))
	{
		if (ft_strnequ(lst->content, "<scene", ft_strlen("<scene")))
			e->scene = get_scene(lst);
		else if (ft_strnequ(lst->content, "<surface", ft_strlen("<surface")))
			get_surface(e->scene, lst);
		else if (ft_strnequ(lst->content, "<camera", ft_strlen("<camera")))
			get_camera(e->scene, &e->scene->camera, lst);
		else if (ft_strnequ(lst->content, "<light", ft_strlen("<light")))
			get_light(e->scene, lst->next);
		if (lst)
			lst = lst->next;
		e->scene->line++;
	}
}

void			parse_rtv1(t_env *e, char *argv)
{
	int		ret;
	char	*line;
	char	*tmp;
	int		fd;
	t_list	*lst;

	if ((fd = open(argv, O_RDONLY)) < 0)
		ft_putendl_fd("Error file don't open", 1);
	lst = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		tmp = ft_strtrim(line);
		ft_lst_add_back(&lst,
				ft_lstnew(ft_strtolower(tmp), ft_strlen(line) + 1));
		free(line);
		free(tmp);
	}
	if (ret == -1)
		ft_putendl_fd("Error file don't read", 1);
	free(line);
	parse_lst(e, lst);
	free_lst(&lst);
	close(fd);
}
