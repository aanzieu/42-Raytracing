/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 11:25:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/23 08:23:02 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../../includes/effects.h"

static int	limit_color(int col)
{
	if (col <= 0)
		return (0);
	else if (col > 0 && col <= 50)
		return (25);
	else if (col > 50 && col <= 100)
		return (75);
	else if (col > 100 && col <= 200)
		return (150);
	else if (col > 200 && col < 250)
		return (225);
	else if (col >= 255)
		return (255);
	return (col);
}

void		int_to_int(int	*src, int *dst, int width, int height)
{
	int	i;
	int	j;
//	int	*tmp;
	size_t size;

	size = sizeof(int) * width * height;
	ft_bzero(dst, size);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			dst[i * width + j] = src[i * width + j];
			j++;
		}
		i++;
	}
}

/* Convert  marroon on r,g,b and */
void		sepia_effect(int *pix)
{
	int		i;
	int		j;
	int		tmp;
	int		cur;
	t_color	tmpx;
	t_color	color;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cur = i * WIN_WIDTH + j;
			color.b = pix[cur] >> 16;
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.r = (pix[cur] & 0x0000FF);
//			grey = ((double)color.r  + (double)color.g + (double)color.b) / 3 ;
//			color.r = grey * 1.27 > 255 ?  255 : grey * 1.27;
//			color.b = grey * 0.729 > 255 ? 255 : grey * 0.729;
//			color.g = grey > 255 ? 255 :grey;
			tmp = (((double)color.r * 0.393  + (double)color.g * 0.769 + (double)color.b) * 0.189) * 1.8;
			tmpx.r = tmp > 255 ? 255 : tmp;
			tmp = (((double)color.r *0.349  + (double)color.g * 0.686 + (double)color.b) * 0.168) * 1.8;
			tmpx.g = tmp > 255 ? 255 : tmp;
			tmp =(((double)color.r * 0.272  + (double)color.g * 0.534 + (double)color.b) * 0.131) * 1.8;
			tmpx.b = tmp > 255 ? 255 : tmp;
			color.r = tmpx.r;
			color.g = tmpx.g;
			color.b = tmpx.b;
			pix[cur] = color.r * 256 * 256 + color.g * 256 + color.b;
			++j;
		}++i;
	}
}

/* add r,g,b and divide by 3 */
void		black_and_white_effect(int *pix)
{
	int		i;
	int		j;
	int		grey;
	int		cur;
	t_color	color;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cur = i * WIN_WIDTH + j;
			color.b = pix[cur] >> 16;
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.r = (pix[cur] & 0x0000FF);
			grey = ((double)color.r + (double)color.g + (double)color.b) / 3;
			color.r = grey;
			color.g = grey;
			color.b = grey;
			pix[cur] = RGB(color.r, color.g, color.b);
			j++;
		}
		i++;
	}
}

void		shell_shading_effect(int *pix)
{
	int		i;
	int		j;
	int		cur;
	t_color	color;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cur = i * WIN_WIDTH + j;
			color.r = pix[cur] >> 16;
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.b = (pix[cur] & 0x0000FF);
			pix[cur] = RGB(limit_color(color.r), limit_color(color.g), limit_color(color.b));
			j++;
		}
		i++;
	}
}

/* *bits colors*/
static void		pixellize_screen(int *pix, int width, int height, int intensity)
{
	int		x;

	int		y;
	int		i;
	int		j;
	int		color;

	x = -intensity;
	while ((x += intensity) < width)
	{
		y = -intensity;
		while ((y += intensity) < height)
		{
			color = pix[width * y + x];
			i = -1;
			while (++i < intensity)
			{
			j = -1;
			while (++j < intensity)
				pix[width * (y + i) + x + j] = color;
			}
		}
	}
}

void		eight_bit_effect(int *pix)
{
	int		i;
	int		j;
	int		value;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			value = pix[i * WIN_WIDTH + j];
			value /= (1 << 4);
			pix[i * WIN_WIDTH + j] = value * (1 << 4);
			++j;
		}
	++i;
	}
	pixellize_screen(pix, WIN_WIDTH, WIN_HEIGHT, WIN_HEIGHT / 128);
}

static void			reinit_avg(int averages[][4], t_pastel pastel)
{
  int				i;
  int				j;

  i = pastel.level;
  while (i--)
  {
	j = 4;
	while (j--)
	{
		averages[i][j] = 0;
	}
  }
}

static void			each_in_radius(t_pastel pastel, t_pos pix, int *from, int averages[][4])
{
	int				lvl;
	int				i;
	int				j;
	t_color			color;
	int				cur;
	reinit_avg(averages, pastel);

	j = -(pastel.radius) - 1;
	while (++j < pastel.radius)
	{
		i = -(pastel.radius - 1);
		while (++i < pastel.radius)
		{
			if ((i + pix.x) >= 0 && (i + pix.x) < pix.width && (j + pix.y) >= 0 && (j + pix.y) < pix.height)
			{
				cur = (j + pix.y) * pix.width + (i + pix.x);//* WIN_WIDTH + j;
				color.r = (from[cur] & 0x0000FF);
				color.g = (from[cur] & 0x00FF00) >> 8;
				color.b = from[cur] >> 16;
				lvl = (((double)color.r + (double)color.g + (double)color.b) / 3) * (double)pastel.level / 256.0;

//				lvl = (((double)(from[(j + pix->y) * pix[1].x + i + pix->x]) / 3.0)) * (double)pastel.level / 256.0;
				averages[lvl][3]++;
				averages[lvl][0] += color.r;//color.r;//from[(j + pix->y) * pix[1].x + i + pix->x].argb[0];
				averages[lvl][1] += color.g;//from[(j + pix->y) * pix[1].x + i + pix->x].argb[1];
				averages[lvl][2] += color.b;//from[(j + pix->y) * pix[1].x + i + pix->x].argb[2];
			}
		}
	}
}


static void			filler(t_pastel pastel, t_pos pix, int *to, int averages[][4])
{
	double			max;
	double			max_index;
	int				i;
	t_color			color;
	int				cur;

	i = pastel.level;
	max = 1;
	max_index = 0;
	while (i--)
	{
		if (max < averages[i][3])
		{
			max = averages[i][3];
			max_index = i;
		}
	}
	cur = (pix.y * pix.width + pix.x);//* WIN_WIDTH + j;
	color.r = averages[(int)max_index][0] / max;
	color.g = averages[(int)max_index][1] / max;
	color.b = averages[(int)max_index][2] / max;
	to[cur] = (RGB(color.r, color.g, color.b));
}

void		pastel_effect(int *pix, int height, int width)
{
	t_pastel	pastel;
	int		averages[pastel.level][4];
	int		x;
	int		y;
	t_pos	pos;
	int		*sum;

	pastel.level = 10;
	pastel.radius = 10;
	if (pastel.radius >= height * width)
		return ;
	sum = malloc(height * width * sizeof(int));
	ft_bzero(sum, height * width * sizeof(int));
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			pos.x = x;
			pos.y = y;
			pos.width = width;
			pos.height = height;
			each_in_radius(pastel, pos, pix, averages);
			filler(pastel, pos, sum, averages);
		}
	}
	int_to_int(sum, pix, width, height);
	free(sum);
}

void		solarized_effect(int *pix)
{
	int		i;
	int		j;
	int		cur;
	t_color	color;
	t_color tmp;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			cur = i * WIN_WIDTH + j;
			color.r = (pix[cur] & 0x0000FF);
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.b = pix[cur] >> 16;
			tmp.r = color.r < 152 ? 255 - color.r : color.r;
			tmp.g = color.g < 116 ? 255 - color.g : color.g;
			tmp.b = color.b < 124 ? 255 - color.b : color.b;
			pix[cur] = RGB(tmp.r, tmp.g, tmp.b);
			j++;
		}
		i++;
	}
}

void		bayer_color(int *pix)
{
	int		x;
	int		y;
	int		cur;
	int		bayervalue = 2;
	t_color color;
	
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			color.r = (pix[cur] & 0x0000FF);
			color.g = (pix[cur] & 0x00FF00) >> 8;
			color.b = pix[cur] >> 16;
			if((y / bayervalue) & 1)
				color.b = 0;
			else
				color.r = 0;
			if((x / bayervalue) & 1)
				color.g = 0;
			pix[cur] = RGB(color.r, color.g, color.b);
		}
	}
}

void		negative_color(int *pix)//, char *pix)
{
	int		x;
	int		y;
	int		r;
	int		g;
	int		b;
	int		cur;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			r = (pix[cur] & 0x0000FF);
			g = (pix[cur] & 0x00FF00) >> 8;
			b = pix[cur] >> 16;
			r ^= 0x00FFFFFF;
			g ^= 0x00FFFFFF;
			b ^= 0x00FFFFFF;
			pix[cur] = RGB(r, g, b);
		}
	}
}

void		filter_color(int *pix)
{
	int		x;
	int		y;
	float	invgamma;
	int		cur;
	t_color		c;

	invgamma = 0.68;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			c.r = (pix[cur] & 0x0000FF);
			c.g = (pix[cur] & 0x00FF00) >> 8;
			c.b = pix[cur] >> 16;
			pix[cur] = (int)RGB((powf(c.r, invgamma)), (powf(c.g, invgamma)), (powf(c.b, invgamma)));
		}
	}
}

void		exposure_color(int *pix)
{
	int		x;
	int		y;
	float	exposure;
	int		cur;
	t_color		c;

	exposure = -0.66f;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			cur = ((y * WIN_WIDTH) + x);
			c.r = (pix[cur] & 0x0000FF);
			c.g = (pix[cur] & 0x00FF00) >> 8;
			c.b = pix[cur] >> 16;
			pix[cur] = RGB((1.0f - expf(c.r * exposure)),
						(1.0f - expf(c.g * exposure)),
						(1.0f - expf(c.b * exposure)));
		}
	}
}
