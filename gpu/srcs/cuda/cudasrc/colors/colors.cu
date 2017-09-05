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
	#include "../../cudaheader/gpu_rt.h"
}

__host__ __device__ t_color new_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}

__host__ __device__ t_color	color_scalar(t_color c1, double coef)
{
	return ((t_color){c1.r * coef, c1.g * coef, c1.b * coef});
}

__host__ __device__ t_color	color_multiply(t_color c1, t_color c2)
{
	return ((t_color){c1.r * c2.r, c1.g * c2.g, c1.b * c2.b});
}

__host__ __device__ t_color	color_add(t_color c1, t_color c2)
{
	return ((t_color){c1.r + c2.r, c1.g + c2.g, c1.b + c2.b});
}

__host__ __device__ int		get_color(t_color color)
{
	double	all_light;
	double	excess_light;

	all_light = color.r + color.g + color.b;
	excess_light = all_light - 3;
	if (excess_light > 0)
	{
		color.r = color.r + excess_light * (color.r / all_light);
		color.g = color.g + excess_light * (color.g / all_light);
		color.b = color.b + excess_light * (color.b / all_light);
	}
	color.r = color.r < 0 ? 0 : color.r;
	color.r = color.r > 1 ? 1 : color.r;
	color.g = color.g < 0 ? 0 : color.g;
	color.g = color.g > 1 ? 1 : color.g;
	color.b = color.b < 0 ? 0 : color.b;
	color.b = color.b > 1 ? 1 : color.b;
	return ((int)(color.b * 255) + (int)(color.g * 255) * 256 +
									(int)(color.r * 255) * 256 * 256);
}
