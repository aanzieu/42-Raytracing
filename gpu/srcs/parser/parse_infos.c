/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:48:38 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/19 09:43:05 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>

void	parse_point(t_vec3d *v, char **tmp, int line)
{
	int i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Position", 1);
		exit(EXIT_FAILURE);
	}
	v->x = ft_atoi_double(tmp[i + 1]);
	v->y = ft_atoi_double(tmp[i + 2]);
	v->z = ft_atoi_double(tmp[i + 3]);
}

void	parse_point_translation(t_vec3d *v, char **tmp, int line)
{
	int i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Tranlation", 1);
		exit(EXIT_FAILURE);
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
		exit(EXIT_FAILURE);
	}
	rotate(v, ft_atoi(tmp[i + 1]), 'x');
	rotate(v, ft_atoi(tmp[i + 2]), 'y');
	rotate(v, ft_atoi(tmp[i + 3]), 'z');
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
		exit(EXIT_FAILURE);
	}
	v->x = ft_atoi_double(tmp[i + 1]);
	v->y = ft_atoi_double(tmp[i + 2]);
	v->z = ft_atoi_double(tmp[i + 3]);
}

float	color_to_coef(unsigned int color)
{
	if (color == 0)
		return (0);
	else
		return (color / (float)255);
}

void	parse_color(t_color *c, char **tmp, int line)
{
	int	i;

	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Color", 1);
		exit(EXIT_FAILURE);
	}
	i = 0;
	c->r = color_to_coef(ft_atoi_double(tmp[i + 1]));
	c->g = color_to_coef(ft_atoi_double(tmp[i + 2]));
	c->b = color_to_coef(ft_atoi_double(tmp[i + 3]));
	// c->light = ft_atoi_double(tmp[i + 4]);
}
