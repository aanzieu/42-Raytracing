/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_obj_parameters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:03:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/26 16:27:44 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

static void	find_informations_object2(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	if (world->ob_save == 'd')
		disk_informations(world, ctx, media);
	else if (world->ob_save == 'm')
		mobius_informations(world, ctx, media);
	else if (world->ob_save == 'o')
		torus_informations(world, ctx, media);
	else if (world->ob_save == 'c')
		cube_informations(world, ctx, media);
	else if (world->ob_save == 'u')
		h_cube_informations(world, ctx, media);
	else if (world->ob_save == 'l')
		light_informations(world, ctx, media);
}

static void	find_informations_object(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	if (world->ob_save == 's')
		sphere_informations(world, ctx, media);
	else if (world->ob_save == 'x')
		cone_informations(world, ctx, media);
	else if (world->ob_save == 'y')
		cylinder_informations(world, ctx, media);
	else if (world->ob_save == 'p')
		plane_informations(world, ctx, media);
	else if (world->ob_save == 'b')
		paraboloid_informations(world, ctx, media);
	else if (world->ob_save == 'h')
		hyperboloid_informations(world, ctx, media);
	else if (world->ob_save == 't')
		triangle_informations(world, ctx, media);
	find_informations_object2(world, ctx, media);
}

void		objects_param(struct nk_context *ctx, struct media *media,\
						t_world *world)
{
	nk_style_set_font(ctx, &media->font_20->handle);
	if (nk_begin(ctx, "Object parameters",\
		nk_rect(world->screen.width - 250, 52, 250, world->screen.height - 52),\
		NK_WINDOW_TITLE | NK_WINDOW_BORDER))
	{
		ui_header(ctx, media, "---- Selected Object");
		find_informations_object(world, ctx, media);
	}
	nk_style_set_font(ctx, &media->font_20->handle);
	nk_end(ctx);
}
