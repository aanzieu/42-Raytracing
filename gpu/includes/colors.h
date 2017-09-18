/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:50:53 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 16:07:11 by xpouzenc         ###   ########.fr       */
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
double	color_to_coef(unsigned int color);

#endif
