/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_demo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 21:29:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

/* ===============================================================
 *
 *                          RENDER DEMO
 *
 * ===============================================================*/

void ui_widget_render(struct nk_context *ctx, struct media *media, float height)
{
	static const float ratio[] = {(float)WIN_WIDTH};
	nk_style_set_font(ctx, &media->font_22->handle);
	nk_layout_row(ctx, NK_STATIC, height, 1, ratio);
}

void load_video_buffer(int *a_h, unsigned char *video_buffer)
{
	int i;
	t_color tmp;    

	for (i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
	{
		tmp = int_to_rgb(a_h[i]);
		video_buffer[4 * i + 0] = tmp.r;
		video_buffer[4 * i + 1] = tmp.g;
		video_buffer[4 * i + 2] = tmp.b;        
		video_buffer[4 * i + 3] = 255;
	}
}

struct nk_image screen_load(int *a_h, unsigned char *video_buffer)
{
	int x,y;//,n;
	GLuint tex;

	x = WIN_WIDTH;
	y = WIN_HEIGHT;

	// if (!data) die("[SDL]: failed to load image: %s", filename);
	load_video_buffer(a_h, video_buffer);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, video_buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	// stbi_image_free(data);
	return nk_image_id((int)tex);
}

void	render_demo(struct nk_context *ctx, struct media *media, int *a_h, unsigned char *video_buffer)
{
	struct nk_image screen;

	screen = screen_load(a_h, video_buffer);
	//int i = 0;
	nk_style_set_font(ctx, &media->font_20->handle);
	nk_begin(ctx, "RT World", nk_rect(0, 0, WIN_WIDTH + 27, WIN_HEIGHT + 60),
			NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_TITLE);

	/*------------------------------------------------
	 *                  SELECTED IMAGE
	 *------------------------------------------------*/
	// ui_header(ctx, media, "Selected Image");
	ui_widget_render(ctx, media, WIN_HEIGHT);
	nk_image(ctx, screen);

	nk_style_set_font(ctx, &media->font_14->handle);
	nk_end(ctx);
}
