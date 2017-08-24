/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 20:47:59 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 21:28:57 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

void    gui_calls(struct nk_context *ctx, struct media *media, t_world *world)
{
	// printf("test\n");
//	basic_demo(ctx, media);
	button_demo(ctx, media, world);
	if (world->a_h != NULL)
	   render_demo(ctx, media, world->a_h, world->video_buffer);
	//     grid_demo(&ctx, &media);
}
