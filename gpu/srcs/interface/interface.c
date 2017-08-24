/* nuklear - v1.05 - public domain */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/08/21 11:47:33 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#include "../../includes/rt.h"
#include "header/nuklear.h"

void    gui_calls(struct nk_context *ctx, struct media *media, t_world *world)
{
	(void)ctx;
	(void)media;
	(void)world;
	printf("TEST\n");
	return;
	// printf("test\n");
	// basic_demo(&ctx, &media);
	//     button_demo(ctx, media, world);
	//     if (world->a_h != NULL)
	//         render_demo(ctx, media, world->a_h, world->video_buffer);
	//     grid_demo(&ctx, &media);
}
