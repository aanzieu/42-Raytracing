/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:24:17 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/29 13:04:38 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void		parse_camera(t_world *world, t_camera *cam, t_list *lst)
{
	char	**tmp;
	int		i;

	while (lst && !ft_strequ(lst->content, "</camera>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
		{
			if (ft_strnequ(tmp[i], "<viewpoint>", ft_strlen("<viewpoint>")))
				parse_point(&world->camera.pos, tmp, world->line);
			else if (ft_strnequ(tmp[i], "<viewdir>", ft_strlen("<viewdir>")))
				parse_point(&world->camera.look_at, tmp, world->line);
			else if (ft_strnequ(tmp[i], "<translation>",
						ft_strlen("<translation>")))
				parse_point_translation(&world->camera.pos, tmp, world->line);
			else if (ft_strnequ(tmp[i], "<rotation>",
				ft_strlen("<rotation>")))
				parse_rotation_cam(&world->camera, tmp, world->line);
		}
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	get_camera_axes(&world->camera);
}
