/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_demo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:03:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/08 18:14:11 by PZC              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

/* ===============================================================
 *
 *                          GRID_DEMO
 *
 * ===============================================================*/

int	find_informations_object(t_world *world, struct nk_context *ctx, struct media *media)
{
	if(world->ob_save == 's')
		sphere_informations(world, ctx, media);
	else if(world->ob_save == 'x')
		cone_informations(world, ctx, media);
	else if(world->ob_save == 'y')
		cylinder_informations(world, ctx, media);
	else if(world->ob_save == 'p')
		plane_informations(world, ctx, media);
	else if(world->ob_save == 'b')
		paraboloid_informations(world, ctx, media);
	else if(world->ob_save == 'h')
		hyperboloid_informations(world, ctx, media);
	else if(world->ob_save == 't')
		triangle_informations(world, ctx, media);
	else if(world->ob_save == 'd')
		disk_informations(world, ctx, media);
	else if(world->ob_save == 'm')
		mobius_informations(world, ctx, media);
	else if(world->ob_save == 'o')
		torus_informations(world, ctx, media);
	else if(world->ob_save == 'c')
		cube_informations(world, ctx, media);

	else
		return(0);
	return(1);
}
void	grid_demo(struct nk_context *ctx, struct media *media, t_world *world)
{
	// static char text[3][64];
	// static int text_len[3];
	static const char *items[] = {"none","mapping","mapping2","mapping3"};
	static int selected_item = 0;
	// static struct	nk_color color = {255, 123, 0, 255};
	static int check = 1;
	static int check2 = 1;

	int i;
	nk_style_set_font(ctx, &media->font_20->handle);
	if (nk_begin(ctx, "Objects", nk_rect(world->screen.width - 275, 52, 275, 550),
				NK_WINDOW_TITLE|NK_WINDOW_BORDER))
	{
		ui_header(ctx, media, "---- Informations ----");
		find_informations_object(world, ctx, media);
		ui_header(ctx, media, "---- Add Mapping ----");
		nk_layout_row_dynamic(ctx, 25, 2);
		nk_style_set_font(ctx, &media->font_18->handle);
		nk_label(ctx, "Reflection", NK_TEXT_LEFT);
		if((nk_checkbox_label(ctx, "", &check)) && !check)
			printf("test check %d\n", check);
		nk_label(ctx, "Refraction", NK_TEXT_LEFT);
		if((nk_checkbox_label(ctx, "", &check2)) && !check2)
			printf("test check %d\n", check2);
		nk_label(ctx, "Mapping", NK_TEXT_LEFT);
		if (nk_combo_begin_label(ctx, items[selected_item], nk_vec2(nk_widget_width(ctx), 200))) {
			nk_layout_row_dynamic(ctx, 25, 1);
			for (i = 0; i < 3; ++i)
				if (nk_combo_item_label(ctx, items[i], NK_TEXT_LEFT))
					selected_item = i;
			nk_combo_end(ctx);
		}
	}
	nk_end(ctx);
}
