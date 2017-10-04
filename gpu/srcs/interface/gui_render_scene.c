/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_render_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 14:46:46 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/29 14:58:25 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"

static void		get_position(struct nk_context *ctx, t_world *w,\
								struct nk_vec2 *pos)
{
	*pos = nk_window_get_position(ctx);
	w->pos_render.x = pos->x;
	w->pos_render.y = pos->y;
}

void			put_pixel(unsigned char *video_buffer, int x, int y, int color)
{
	t_color	tmp;

	tmp = int_to_rgb(color);
	video_buffer[4 * y * WIN_WIDTH + (0 + x * 4)] = tmp.r;
	video_buffer[4 * y * WIN_WIDTH + (1 + x * 4)] = tmp.g;
	video_buffer[4 * y * WIN_WIDTH + (2 + x * 4)] = tmp.b;
	video_buffer[4 * y * WIN_WIDTH + (3 + x * 4)] = 255;
}

void			load_video_buffer(int *a_h, unsigned char *video_buffer,\
								int x_res, int render_factor)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		x = 0;
		while (j < WIN_WIDTH)
		{
			put_pixel(video_buffer, j, i, a_h[y * x_res + x]);
			j++;
			if (j % render_factor == 0)
				x++;
		}
		i++;
		if (i % render_factor == 0)
			y++;
	}
}

struct nk_image	screen_load(int *a_h, unsigned char *video_buffer,\
							int x_res, int render_factor)
{
	int		x;
	int		y;
	GLuint	tex;

	x = WIN_WIDTH;
	y = WIN_HEIGHT;
	load_video_buffer(a_h, video_buffer, x_res, render_factor);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,\
	GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,\
	GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA,\
	GL_UNSIGNED_BYTE, video_buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	return (nk_image_id((int)tex));
}

void			render_scene(struct nk_context *ctx, struct media *media,\
							t_world *w)
{
	static struct nk_image	screen;
	struct nk_vec2			pos;

	nk_style_set_font(ctx, &media->font_18->handle);
	if (nk_begin(ctx, w->title, nk_rect((w->screen.width - (WIN_WIDTH + 15))\
		/ 2, (w->screen.height - (WIN_HEIGHT + 48)) / 2, WIN_WIDTH + 15,\
		WIN_HEIGHT + 48), NK_WINDOW_MOVABLE | NK_WINDOW_NO_SCROLLBAR |\
		NK_WINDOW_TITLE | NK_WINDOW_BACKGROUND | NK_WINDOW_CLOSABLE))
	{
		if ((w->reload_buffer == 1 && w->redraw == 0) || w->redraw == 3)
		{
			screen = screen_load(w->a_h, w->video_buffer, w->viewplane.x_res,\
								w->render_factor);
			w->reload_buffer = 0;
		}
		get_position(ctx, w, &pos);
		nk_layout_row_static(ctx, WIN_HEIGHT, WIN_WIDTH, 1);
		nk_image(ctx, screen);
		if (mousepress_middle(ctx, w, pos) || mousepress_left(ctx, w, pos)\
			|| key_press(ctx, w)) 
		{
			w->on = 0;
			w->redraw = 1;
		}
	}
	clear(ctx, w);
	nk_end(ctx);
}
