#ifndef GUI_H
# define GUI_H

#include "../../../includes/rt.h"
#define MAX(a,b) ((a) < (b) ? (b) : (a))

void	ui_widget(struct nk_context *ctx, struct media *media, float height);
void	ui_header(struct nk_context *ctx, struct media *media, const char *title);
void	ui_widget_centered(struct nk_context *ctx, struct media *media, float height);
int		ui_piemenu(struct nk_context *ctx, struct nk_vec2 pos, float radius,
		struct nk_image *icons, int item_count);
void	ui_widget_small_button(struct nk_context *ctx, struct media *media, float height);
void
ui_widget_special_mode(struct nk_context *ctx, struct media *media, float height);
int
ui_widget_value_infos(struct nk_context *ctx, struct media *media, double *value, char *title);
/* ===============================================================
 *
 *                          WINDOW POP UP
 *
 * ===============================================================*/

void	basic_demo(struct nk_context *ctx, struct media *media);
void	grid_demo(struct nk_context *ctx, struct media *media);
void	scene_parameters(struct nk_context *ctx, struct media *media, t_world *world);
void	render_demo(struct nk_context *ctx, struct media *media, int *a_h, unsigned char *video_buffer);

#endif
