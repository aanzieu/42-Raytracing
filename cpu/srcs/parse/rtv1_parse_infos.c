/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_parse_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:48:38 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 09:12:15 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void	parse_point(t_3point *v, char **tmp, int line)
{
	int i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Position", 1);
	}
	v->x = ft_atoi_double(tmp[i + 1]);
	v->y = ft_atoi_double(tmp[i + 2]);
	v->z = ft_atoi_double(tmp[i + 3]);
}

void	parse_point_translation(t_3point *v, char **tmp, int line)
{
	int i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Tranlation", 1);
	}
	v->x += ft_atoi_double(tmp[i + 1]);
	v->y += ft_atoi_double(tmp[i + 2]);
	v->z += ft_atoi_double(tmp[i + 3]);
}

void	parse_rotation_object(t_vec3d *v, char **tmp, int line)
{
	int		i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Tranlation", 1);
	}
	ft_rot_x(v, deg_to_radian(ft_atoi(tmp[i + 1]) % 360));
	ft_rot_y(v, deg_to_radian(ft_atoi(tmp[i + 2]) % 360));
	ft_rot_z(v, deg_to_radian(ft_atoi(tmp[i + 3]) % 360));
}

void	parse_vector(t_vec3d *v, char **tmp, int line)
{
	int i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Position", 1);
	}
	v->x = ft_atoi_double(tmp[i + 1]);
	v->y = ft_atoi_double(tmp[i + 2]);
	v->z = ft_atoi_double(tmp[i + 3]);
}

void	parse_color(t_color *c, char **tmp, int line)
{
	int	i;

	if (ft_count_word(tmp) != 6)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Color", 1);
	}
	i = 0;
	c->r = ft_atoi_double(tmp[i + 1]);
	c->g = ft_atoi_double(tmp[i + 2]);
	c->b = ft_atoi_double(tmp[i + 3]);
	c->light = ft_atoi_double(tmp[i + 4]);
}
