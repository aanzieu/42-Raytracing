/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 17:47:53 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/19 17:51:14 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <effects.h>
#include <colors.h>

void	pixel_to_image(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8 *pixel;

	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

/*
** Not fonctionnel
**	else if(world->keys.pad_8 == 1)
**		exposure_color(world->a_h);
*/

void	effect_application(t_world *world)
{
	int		averages[10][4];

	if (world->keys.pad_0 == 1)
		sepia_effect(world->a_h, (t_color){0, 0, 0});
	else if (world->keys.pad_0 == 2)
		bayer_color(world->a_h, 2);
	else if (world->keys.pad_0 == 3)
		eight_bit_effect(world->a_h);
	else if (world->keys.pad_0 == 4)
		pastel_effect(world->a_h, world->viewplane.y_res,
								world->viewplane.x_res, averages);
	else if (world->keys.pad_0 == 5)
		black_and_white_effect(world->a_h, (t_color){0, 0, 0});
	else if (world->keys.pad_0 == 6)
		shell_shading_effect(world->a_h);
	else if (world->keys.pad_0 == 7)
		negative_color(world->a_h);
	else if (world->keys.pad_0 == 8)
		anaglyph(world);
}
