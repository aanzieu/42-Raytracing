/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:36:01 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/20 12:10:18 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vectors.h"
# include "colors.h"

# define AMBIENT_LIGHT WHITE

typedef struct			s_ambient
{
	t_color				color;
	double				intensity;
	double				coef;
}						t_ambient;

typedef struct			s_light
{
	int					id;
	t_vec3d				pos;
	t_vec3d				dir;
	t_vec3d				dir_v;
	t_color				color;
	double				intensity_coef;
	struct s_light		*next;
}						t_light;

/*
********************************************************************************
**                     FCTS_OBJ                                               **
********************************************************************************
*/

t_light					*new_light(t_light *nw, int id);
void					add_light(t_light **alst, t_light *nw);
void					load_lights(t_light **lights, t_light *lights_tmp,
						int *lights_len);
void					free_light(t_light **l_tmp, t_light **l, int *len);

#endif
