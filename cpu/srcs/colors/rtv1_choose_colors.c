/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_choose_colors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:59:18 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/22 16:06:22 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rtv1.h"
void		bayer_color(t_env *e)
{
	int		x;
	int		y;
	int		cur;
	int		bayervalue = 2;
	
	y = -1;
	while (++y < WH)
	{
		x = -1;
		while (++x < WW)
		{
			cur = ((y * WW) + x) * e->image->bpp;
			if((y / bayervalue) & 1)
				(e->image->img_s + cur)[2] = 0;
			else
				(e->image->img_s + cur)[0] = 0;
			if((x / bayervalue) & 1)
				(e->image->img_s + cur)[1] = 0;
		}
	}
}

void		black_white(t_env *e)//, char *pix)
{
	int		x;
	int		y;
	int		cur;
	int	tmp;
	double a;
	double b;
	double c;
	
	y = -1;
	while (++y < WH)
	{
		x = -1;
		while (++x < WW)
		{
			cur = ((y * WW) + x) * e->image->bpp;
			a = (e->image->img_s + cur)[0] * 0.3;
			b = (e->image->img_s + cur)[1] * 0.3;
			c = (e->image->img_s + cur)[2] * 0.3;
			tmp = a + b + c;
			(e->image->img_s + cur)[0] = (tmp & 0x0000FF);
			(e->image->img_s + cur)[1] = (tmp & 0x00FF00) >> 8;
			(e->image->img_s + cur)[3] = tmp >> 16;

			//			tmp = (tmp1 + cur)[2] * 0.393
			//				+ (tmp1 + cur)[1] * 0.769
			//				+ (tmp1 + cur)[0] * 0.189;
			//			(e->image->img_s + cur)[0] = (tmp > 255) ? 255 >> 16: tmp >> 16;
			//			tmp = (tmp1 + cur)[2] * 0.349
			//				+ (tmp1 + cur)[1] * 0.686
			//				+ (tmp1 + cur)[0] * 0.168;
			//			(e->image->img_s + cur)[1] = (tmp > 255) ? 255 >> 8 : tmp >> 8;
			//			tmp  = (tmp1 + cur)[2] * 0.272
			//				+ (tmp1 + cur)[1] * 0.534
			//				+ (tmp1 + cur)[0] * 0.131;
			//			(e->image->img_s + cur)[2] = (tmp > 255) ? 255 : tmp;
		}
	}
}

void		negative_color(t_env *e)//, char *pix)
{
	int		x;
	int		y;
	int		cur;

	y = -1;
	while (++y < WH)
	{
		x = -1;
		while (++x < WW)
		{
			cur = ((y * WW) + x) * e->image->bpp;
			(e->image->img_s + cur)[0] ^= 0x00FFFFFF;
			(e->image->img_s + cur)[1] ^= 0x00FFFFFF;
			(e->image->img_s + cur)[2] ^= 0x00FFFFFF;
		}
	}
}


int			get_special_color(int color, double m, double h)
{
	(void)h;
	(void)m;

	//	color = grey;
	//	color ^= 0x00FFFFFF;
	return (color);
}

int			get_color(t_color c)
{
	float	invgamma;
	float	exposure;

	invgamma = 0.45;
	exposure = -0.66f;
	//	if (c.light == 6)
	//	{
	//		return ((int)RGB((1.0f - expf(c.r * exposure)) * 255,
	//					(1.0f - expf(c.g * exposure)) * 255,
	//					(1.0f - expf(c.b * exposure)) * 255));
	//	}
	//	else if (c.light == 6)
	//	{
	return ((int)RGB((powf(c.r, invgamma)) * 255,
				(powf(c.g, invgamma)) * 255, (powf(c.b, invgamma)) * 255));
	//	}
	//	return ((int)RGB(c.r * 255, c.g * 255, c.b * 255));
}

t_color		color_def(t_color c)
{
	double	all_light;
	double	excess_light;

	all_light = c.r + c.g + c.b;
	excess_light = all_light - 3;
	if (excess_light > 0)
	{
		c.r = c.r + excess_light * (c.r / all_light);
		c.g = c.g + excess_light * (c.g / all_light);
		c.b = c.b + excess_light * (c.b / all_light);
	}
	c.r = c.r < 0 ? 0 : c.r;
	c.r = c.r > 1 ? 1 : c.r;
	c.g = c.g < 0 ? 0 : c.g;
	c.g = c.g > 1 ? 1 : c.g;
	c.b = c.b < 0 ? 0 : c.b;
	c.b = c.b > 1 ? 1 : c.b;
	c.light = c.light > 1 ? 1 : c.light;
	c.light = c.light < 0 ? 0 : c.light;
	return (new_color(c.r, c.g, c.b, c.light));
}
