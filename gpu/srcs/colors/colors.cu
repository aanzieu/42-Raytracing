/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.cu                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/15 10:38:50 by svilau            #+#    #+#             */
/*   Updated: 2017/06/15 14:09:12 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern "C" {
	#include "../../includes/rtv1.h"
}

__host__ __device__ void	color_scalar(t_color *color, double coeficient)
{
	color->r *= coeficient;
	color->g *= coeficient;
	color->b *= coeficient;	
}

__host__ __device__ void	color_multiply(t_color *color1, t_color color2)
{
	color1->r *= color2.r;
	color1->g *= color2.g;
	color1->b *= color2.b;	
}

__host__ __device__ void	color_add(t_color *color1, t_color color2)
{
	color1->r += color2.r;
	color1->g += color2.g;
	color1->b += color2.b;	
}

__host__ __device__ int		get_color(double r, double g, double b)
{
	return ((int)(b * 255) + (int)(g * 255) * 256 + (int)(r * 255) * 256 * 256);
}