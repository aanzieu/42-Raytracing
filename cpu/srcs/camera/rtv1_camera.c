/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 08:09:15 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/14 16:22:00 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

void		parse_rotation_cam(t_cam *cam, char **tmp, int line)
{
	int	i;

	i = 0;
	if (ft_count_word(tmp) != 5)
	{
		ft_putstr_fd("Line : ", 1);
		ft_putnbr(line);
		ft_putendl_fd(" Wrong Tranlation", 1);
	}
	cam->dir = point_to_vector(cam->pos, cam->look_at);
	cam->posreset = cam->pos;
	cam->look_at_reset = cam->look_at;
	cam->axe_z = vector_normalize(cam->dir);
	cam->axe_x = vector_normalize(vector_crossproduct(new_3dvector(0, 1, 0),
			cam->axe_z));
	cam->axe_y = vector_normalize(vector_crossproduct(cam->axe_x, cam->axe_z));
	vector_rot_x(&cam->axe_y, &cam->axe_z,
			deg_to_radian(ft_atoi(tmp[i + 1]) % 360));
	vector_rot_y(&cam->axe_x, &cam->axe_z,
			deg_to_radian(ft_atoi(tmp[i + 2]) % 360));
	vector_rot_z(&cam->axe_x, &cam->axe_y,
			deg_to_radian(ft_atoi(tmp[i + 3]) % 360));
	cam->rotation = 1;
}

void		cam_reset(t_cam *cam)
{
	cam->pos = cam->posreset;
	cam->look_at = cam->look_at_reset;
	cam->dir = point_to_vector(cam->pos, cam->look_at);
	cam->axe_z = vector_normalize(cam->dir);
	cam->axe_x = vector_normalize(vector_crossproduct(new_3dvector(0, 1, 0),
				cam->axe_z));
	cam->axe_y = vector_normalize(vector_crossproduct(cam->axe_x, cam->axe_z));
}

void		cam_axes(t_cam *cam)
{
	cam->dir = point_to_vector(cam->pos, cam->look_at);
	cam->axe_z = vector_normalize(cam->dir);
	cam->axe_x = vector_normalize(vector_crossproduct(new_3dvector(0, 1, 0),
				cam->axe_z));
	cam->axe_y = vector_normalize(vector_crossproduct(cam->axe_x, cam->axe_z));
}

void		get_camera(t_scene *scene, t_cam *cam, t_list *lst)
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
				parse_point(&cam->pos, tmp, scene->line);
			else if (ft_strnequ(tmp[i], "<viewdir>", ft_strlen("<viewdir>")))
				parse_point(&cam->look_at, tmp, scene->line);
			else if (ft_strnequ(tmp[i], "<translation>",
						ft_strlen("<translation>")))
				parse_point_translation(&cam->pos, tmp, scene->line);
			else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
				parse_rotation_cam(cam, tmp, scene->line);
		}
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	cam->posreset = cam->pos;
	cam->look_at_reset = cam->look_at;
	if (cam->rotation != 1)
		cam_axes(cam);
}

void		cam_position(t_cam *cam, int x, int y)
{
	double	ndc_x;
	double	ndc_y;
	int		resx;
	int		resy;
	double ratio;
	
	resx = WW / FAST_RENDER_PRECISION;
	resy = WH / FAST_RENDER_PRECISION;
	ratio = (double)resx / (double)resy;

	ndc_x = (x + 0.5) / WW;//resx;//RESX;
	ndc_y = (y + 0.5) / WH;//resy;//RESY;
	if (WW > WH)
	{

//		cam->x = ndc_x * (180/120) - (((180 - 120) / (double)120) / 2);
//		cam->x = ndc_x * ratio - (((resx - resy) / (double)resy) / 2);
		cam->x = ndc_x * IMG_RATIO - (((WW - WH) / (double)WH) / 2);
		cam->y = ndc_y;
	}
	else
	{
		cam->x = ndc_x;
		cam->y = ndc_y / IMG_RATIO - (((WH - WW) / (double)WW) / 2);
	}
}
