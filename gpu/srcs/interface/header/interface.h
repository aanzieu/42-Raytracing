#ifndef INTERFACE_H
# define INTERFACE_H

#include "../../../includes/rt.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

/* ===============================================================
 *
 *                          DEVICE
 *
 * ===============================================================*/

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

/* ===============================================================
 *
 *                          SURFACE RT BLOC
 *                          *
 * ===============================================================*/

void	gui_calls(struct nk_context *ctx, struct media *media, t_world *world);

#endif
