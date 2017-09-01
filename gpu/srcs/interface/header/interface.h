#ifndef INTERFACE_H
# define INTERFACE_H

#include "../../../includes/rt.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"

// #define WINDOW_WIDTH 1200
// #define WINDOW_HEIGHT 800





#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

/* ===============================================================
 *
 *                          DEVICE
 *
 * ===============================================================*/



/* ===============================================================
 *
 *                          SURFACE RT BLOC
 *                          *
 * ===============================================================*/

void	gui_calls(struct file_browser *browser, struct nk_context *ctx, struct media *media, t_world *world);
// void 	error_callback(int e, const char *d);
// void scroll_input(GLFWwindow *win, double _, double yoff);
// void text_input(GLFWwindow *win, unsigned int codepoint);
// void die(const char *fmt, ...);

#endif
