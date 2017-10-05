/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:50:53 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/19 14:59:35 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define RGB(r,g,b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_cl
{
	int				r;
	int				g;
	int				b;
}					t_cl;

double				color_to_coef(unsigned int color);

#endif
