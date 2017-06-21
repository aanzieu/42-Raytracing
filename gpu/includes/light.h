/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 15:36:01 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 18:13:21 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

#include "vectors.h"
#include "colors.h"

# define AMBIENT_LIGHT WHITE

typedef struct			s_light
{
	t_vec3d				pos;
	t_color				color;
	double				intensity_coef;
	struct s_light		*next;
}						t_light;

/*******************************************************************************
**                     FCTS_OBJ                                               **
*******************************************************************************/

t_light					*new_light(t_light *nw);
void					add_light(t_light **alst, t_light *nw);
void					load_lights(t_light **lights, t_light *lights_tmp,
						int *lights_len);

#endif

