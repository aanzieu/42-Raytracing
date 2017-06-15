/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:48:38 by aanzieu           #+#    #+#             */
/*   Updated: 2017/05/26 17:43:49 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rtv1.h"

void		parse_rotation_cam(t_camera *cam, char **tmp, int line)
{
	int	i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Tranlation", 1);
	}
	rotate(&cam->look_at, ft_atoi(tmp[i + 1]), 'x');
	rotate(&cam->look_at, ft_atoi(tmp[i + 2]), 'y');
	rotate(&cam->look_at, ft_atoi(tmp[i + 3]), 'z');
	cam->rotation = 1;
}
