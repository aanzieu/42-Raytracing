/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 11:28:30 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 15:01:43 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H

# include "colors.h"
# include "rt.h"

typedef	struct	s_pastel
{
	int			radius;
	int			level;
}				t_pastel;

typedef	struct	s_pos
{
	int			x;
	int			y;
	int			i;
	int			j;
	int			w;
	int			h;
}				t_pos;

void			shell_shading_effect(int *pix);
void			exposure_color(int *pix);
void			filter_color(int *pix);
void			negative_color(int *pix);
void			bayer_color(int *pix, int bayervalue);
void			solarized_effect(int *pix);
void			pastel_effect(int *pix, int height,
				int width, int averages[10][4]);
void			black_and_white_effect(int *pix, t_color color);
void			sepia_effect(int *pix, t_color color);
void			eight_bit_effect(int *pix);
void			anaglyph(t_world *world);

#endif
