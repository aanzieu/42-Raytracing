#ifndef GUI_H
# define GUI_H

#include "../../../includes/rt.h"
#define MAX(a,b) ((a) < (b) ? (b) : (a))

void	ui_widget(struct nk_context *ctx, struct media *media, float height);
void	ui_header(struct nk_context *ctx, struct media *media, const char *title);
void	ui_widget_centered(struct nk_context *ctx, struct media *media, float height);
int		ui_piemenu(struct nk_context *ctx, struct nk_vec2 pos, float radius,
		struct nk_image *icons, int item_count);


/* ===============================================================
 *
 *                          WINDOW POP UP
 *
 * ===============================================================*/

void	basic_demo(struct nk_context *ctx, struct media *media);
void	grid_demo(struct nk_context *ctx, struct media *media);
void	button_demo(struct nk_context *ctx, struct media *media, t_world *world);
void	render_demo(struct nk_context *ctx, struct media *media, int *a_h, unsigned char *video_buffer);

#endif
