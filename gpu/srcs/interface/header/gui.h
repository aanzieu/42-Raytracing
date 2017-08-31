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
 *                         DELETE OBJECTS
 *
 * ===============================================================*/

//int			remove_object(t_world *world, t_intersection *i);
void			remove_sphere(t_sphere **s, t_intersection *i);
void			remove_cone(t_cone **s, t_intersection *i);
void			remove_cylinder(t_cylinder **s, t_intersection *i);
void			remove_plane(t_plane **s, t_intersection *i);
int			mousepress_right(struct nk_context *ctx, t_world *world, struct nk_vec2 pos);

/* ===============================================================
 *
 *                          WINDOW POP UP
 *
 * ===============================================================*/

void	basic_demo(struct nk_context *ctx, struct media *media);
void	grid_demo(struct nk_context *ctx, struct media *media);
void	scene_parameters(struct nk_context *ctx, struct media *media, t_world *world);
void	render_demo(struct nk_context *ctx, struct media *media, int *a_h, t_world *world);



#endif
