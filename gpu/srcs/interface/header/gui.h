#ifndef GUI_H
# define GUI_H

#include "../../../includes/rt.h"

#define UNUSED(a) (void)a


#define MAX_VERTEX_MEMORY 1024 * 1024
#define MAX_ELEMENT_MEMORY 512 * 1024

#ifdef __APPLE__
#define NK_SHADER_VERSION "#version 150\n"
#else
#define NK_SHADER_VERSION "#version 300 es\n"
#endif

#define WINDOW_WIDTH 1540
#define WINDOW_HEIGHT 867

struct nk_glfw_vertex {
	float position[2];
	float uv[2];
	nk_byte col[4];
};

struct device {
	struct nk_buffer cmds;
	struct nk_draw_null_texture null;
	GLuint vbo, vao, ebo;
	GLuint prog;
	GLuint vert_shdr;
	GLuint frag_shdr;
	GLint attrib_pos;
	GLint attrib_uv;
	GLint attrib_col;
	GLint uniform_tex;
	GLint uniform_proj;
	GLuint font_tex;
};


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
int
ui_widget_value_infos_int(struct nk_context *ctx, struct media *media, int *value, char *title);
int
ui_widget_value_infos_cam(struct nk_context *ctx, struct media *media, double *value, char *title);
int
ui_widget_value_slider_int(struct nk_context *ctx, struct media *media, int *value, char *title);
int
ui_widget_value_slider_float(struct nk_context *ctx, struct media *media, double *value, char *title);


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
void			remove_torus(t_torus **s, t_intersection *i);
void			remove_mobius(t_mobius **s, t_intersection *i);
void			remove_disk(t_disk **s, t_intersection *i);
void			remove_cube(t_cube **s, t_intersection *i);
void			remove_h_cube(t_h_cube **s, t_intersection *i);
void			remove_hyperboloid(t_hyperboloid **s, t_intersection *i);
void			remove_paraboloid(t_paraboloid **s, t_intersection *i);
void			remove_triangle(t_triangle **s, t_intersection *i);
int				mousepress_middle(struct nk_context *ctx, t_world *world, struct nk_vec2 pos);
int				mousepress_left(struct nk_context *ctx, t_world *world, struct nk_vec2 pos);

/* ===============================================================
 *
 *                          WINDOW POP UP
 *
 * ===============================================================*/

void	objects_param(struct nk_context *ctx, struct media *media, t_world *world);
void	scene_parameters(struct nk_context *ctx, struct media *media, t_world *world);
void	scene_topbar(struct nk_context *ctx, struct media *media, t_world *world);
void 	camera_control_bar(struct nk_context *ctx, struct media *media, t_world *world);
void	render_scene(struct nk_context *ctx, struct media *media, int *a_h, t_world *world);

int 	file_browser_run(struct file_browser *browser, struct nk_context *ctx);
void file_browser_init(struct file_browser *browser, struct media *media);
void file_browser_free(struct file_browser *browser);
struct nk_image* media_icon_for_file(struct media *media, const char *file);
char* file_load(const char* path, size_t* siz);
void file_browser_reload_directory_content(struct file_browser *browser, const char *path);
/* ===============================================================
 *
 *                          DEVICE INIT
 *
 * ===============================================================*/

void	device_shutdown(struct device *dev);
void	device_upload_atlas(struct device *dev, const void *image, int width, int height);
void 	device_init(struct device *dev);
void	set_up_global_state(struct device *dev, GLfloat ortho[4][4]);

/* ===============================================================
 *
 *                          OPENGL INIT
 *
 * ===============================================================*/

void	defaut_opengl_state();
void 	init_glfw_start(GLFWwindow **win, struct nk_context *ctx, t_screen *screen);
void 	error_callback(int e, const char *d);
void 	scroll_input(GLFWwindow *win, double _, double yoff);
void 	text_input(GLFWwindow *win, unsigned int codepoint);
void 	die(const char *fmt, ...);

struct nk_image icon_load(const char *filename);
void	loading_media(struct media *media, struct nk_font_atlas *atlas, struct nk_context *ctx, struct device *device);
void	device_draw(struct device *dev, struct nk_context *ctx, t_screen *screen, enum nk_anti_aliasing AA);
void	allocate_vertex_buffer(struct device *dev, enum nk_anti_aliasing AA, struct nk_context *ctx);
int		key_press(struct nk_context *ctx, t_world *world);

void	sphere_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_sphere(t_world *world, int i);
void	cone_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_cone(t_world *world, int i);
void	cylinder_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_cylinder(t_world *world, int i);
void	plane_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_plane(t_world *world, int i);
void	plane_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_torus(t_world *world, int i);
void	torus_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_mobius(t_world *world, int i);
void	mobius_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_disk(t_world *world, int i);
void	disk_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_cube(t_world *world, int i);
void	cube_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_h_cube(t_world *world, int i);
void	h_cube_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_paraboloid(t_world *world, int i);
void	paraboloid_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_hyperboloid(t_world *world, int i);
void	hyperboloid_informations(t_world *world, struct nk_context *ctx, struct media *media);
void	refresh_triangle(t_world *world, int i);
void	triangle_informations(t_world *world, struct nk_context *ctx, struct media *media);


void	draw_color_picker(struct nk_context *ctx, t_color *o, t_world *world);
void	draw_chess_color(struct nk_context *ctx, t_world *world, t_color *c);
void	draw_choose_color(struct nk_context *ctx, t_world *world, t_color *c);
void	header_info(struct nk_context *ctx, struct nk_image img, char *n);

void	select_scene(struct nk_context *ctx, struct media *media, t_world *world, int img_active[3]);
void	press_launch(struct nk_context *ctx, t_world *world, int img_active[3]);

#endif
