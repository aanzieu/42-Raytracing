/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:33:11 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 17:25:39 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void	get_disk_next(t_world *world, char **tmp, int i, t_disk *d)
{
	if (ft_strnequ(tmp[i], "<origin>", ft_strlen("<origin>")))
		parse_point(&d->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&d->up, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&d->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&d->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&d->up, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<reflexion>", ft_strlen("<reflexion>")))
		parse_reflexion(&d->reflexion_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<refraxion>", ft_strlen("<refraxion>")))
		parse_refraxion(&d->refraxion_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<chess>", ft_strlen("<chess>")))
		parse_color(&d->chess, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<radius>", ft_strlen("<radius>")))
	{
		d->radius = ft_atoi_double((tmp[i + 1]));
		d->radius_squared = pow(d->radius, 2);
	}
}

void		parse_disk(t_world *world, t_list *lst)
{
	t_disk	*d;
	char	**tmp;
	int		i;

	if (!(d = (t_disk *)ft_memalloc(sizeof(t_disk))))
		ft_putendl_fd("Error Malloc Disk", 1);
	d->chess.r = -1;
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_disk_next(world, tmp, i, d);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_disk(&world->disks_tmp, new_disk(d, world->obj_id++));
	free(d);
}
