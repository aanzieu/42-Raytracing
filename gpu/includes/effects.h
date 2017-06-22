/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 11:28:30 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/22 17:48:11 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H

typedef	struct	s_pastel
{
	int	radius;
	int	level;
}				t_pastel;

typedef	struct	s_pos
{
	int		x;
	int		y;
	int		width;
	int		height;
}				t_pos;

void		shell_shading_effect(int *pix);
void		exposure_color(int *pix);
void		filter_color(int *pix);
void		negative_color(int *pix);
void		bayer_color(int *pix);
void		solarized_effect(int *pix);
void		pastel_effect(int *pix, int height, int width);
void		black_and_white_effect(int *pix);
void		sepia_effect(int *pix);
void		eight_bit_effect(int *pix);
#endif
