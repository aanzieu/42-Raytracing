/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 08:16:19 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/07 09:08:00 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"

t_img		*new_image(t_env *e)
{
	t_img *img;

	if (!(img = (t_img *)ft_memalloc(sizeof(t_img))))
		return (NULL);
	if (!(img->img = mlx_new_image(e->mlx, WW, WH)))
		return (del_image(e, img));
	img->img_s = mlx_get_data_addr(img->img, &(img->bpp), &(img->s_l),
			&(img->endian));
	img->bpp /= 8;
	return (img);
}

t_img		*del_image(t_env *e, t_img *img)
{
	if (img != NULL)
	{
		if (img->img != NULL)
			mlx_destroy_image(e->mlx, img->img);
		ft_memdel((void **)&img);
	}
	return (NULL);
}
