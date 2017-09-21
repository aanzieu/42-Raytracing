/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_scenes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 13:54:11 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/12 14:10:08 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../../includes/light.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include "parse.h"

static void	launch_scene_select(t_world *world, int i)
{
	char *nb;
	char *start;
	char *path;

	clear_world(world);
	nb = ft_itoa(i);
	start = ft_strjoin("testfiles/", nb);
	ft_strdel(&nb);
	path = ft_strjoin(start, ".xml");
	ft_strdel(&start);
	parse_rtv1(world, path);
	ft_strdel(&path);
	load_data(world);
	rt(world);
	world->img_scene = i;
	world->redraw = 3;
}

void		press_launch(struct nk_context *ctx, t_world *world,\
						int img_active[3])
{
	if (nk_button_label(ctx, "Launch"))
	{
		if (img_active[2] == 1)
			launch_scene_select(world, 1);
		else if (img_active[2] == 2)
			launch_scene_select(world, 2);
		else if (img_active[2] == 3)
			launch_scene_select(world, 3);
		else if (img_active[2] == 4)
			launch_scene_select(world, 4);
		img_active[0] = 0;
		img_active[1] = 0;
		nk_popup_close(ctx);
	}
}
