/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:48:38 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/07 14:04:57 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gpu_rt.h>

void		parse_rotation_cam(t_camera *cam, char **tmp, int line)
{
	int	i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Tranlation", 1);
		exit (EXIT_FAILURE);
	}
	rotate(&cam->look_at, ft_atoi(tmp[i + 1]), 'x');
	rotate(&cam->look_at, ft_atoi(tmp[i + 2]), 'y');
	rotate(&cam->look_at, ft_atoi(tmp[i + 3]), 'z');
	cam->rotation = 1;
}

void	parse_intensity(double *intensity_coef, char **tmp, int line)
{
	if (ft_count_word(tmp) != 3)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong intensity format", 1);
		exit (EXIT_FAILURE);
	}
	*intensity_coef = ft_atoi_double(tmp[1]);
}

void	parse_reflection(double *reflection_coef, char **tmp, int line)
{
	if (ft_count_word(tmp) != 3)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong reflection coeficient format", 1);
		exit (EXIT_FAILURE);
	}
	*reflection_coef = ft_atoi_double(tmp[1]);
}

void	parse_refraction(double *refraction_coef, char **tmp, int line)
{
	if (ft_count_word(tmp) != 3)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong refraction coeficient format", 1);
		exit (EXIT_FAILURE);
	}
	*refraction_coef = ft_atoi_double(tmp[1]);
}
