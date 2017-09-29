#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_FONT

#include <assert.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <unistd.h>
#include "stb_image.h"
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

void    die(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputs("\n", stderr);
    exit(EXIT_FAILURE);
}

void    error_callback(int e, const char *d)
{
    ft_printf("Error %d: %s\n", e, d);
}

char* file_load(const char* path, size_t* siz)
{
    char *buf;
    FILE *fd = fopen(path, "rb");
    if (!fd) die("Failed to open file: %s\n", path);
    fseek(fd, 0, SEEK_END);
    *siz = (size_t)ftell(fd);
    fseek(fd, 0, SEEK_SET);
    buf = (char*)calloc(*siz, 1);
    fread(buf, *siz, 1, fd);
    fclose(fd);
    return buf;
}

struct nk_image icon_load(const char *filename)
{
	int x,y,n;
	GLuint tex;
	unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
	if (!data) die("[SDL]: failed to load image: %s", filename);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return nk_image_id((int)tex);
}

void load_icon_object(struct media *media)
{
 	media->light = icon_load("frameworks/nuklear/icon/light.png");
	media->plane = icon_load("frameworks/nuklear/icon/plan.png");
	media->sphere = icon_load("frameworks/nuklear/icon/sphere.png");
	media->cone = icon_load("frameworks/nuklear/icon/cone.png");
	media->cylinder = icon_load("frameworks/nuklear/icon/cylinder.png");
	media->disk = icon_load("frameworks/nuklear/icon/disk.png");
	media->paraboloid = icon_load("frameworks/nuklear/icon/paraboloid.png");
	media->hyperboloid = icon_load("frameworks/nuklear/icon/hyperboloid.png");
	media->mobius = icon_load("frameworks/nuklear/icon/moebius.png");
	media->cube = icon_load("frameworks/nuklear/icon/cube.png");
	media->h_cube = icon_load("frameworks/nuklear/icon/h_cube.png");
	media->torus = icon_load("frameworks/nuklear/icon/torus.png");
	media->triangle = icon_load("frameworks/nuklear/icon/triangle.png");
	media->cam = icon_load("frameworks/nuklear/icon/cam.png");
    media->rec = icon_load("frameworks/nuklear/icon/camera.png");
	media->rec_on = icon_load("frameworks/nuklear/icon/camera_on.png");
    media->a_rot_left = icon_load("frameworks/nuklear/icon/rot_left.png");
    media->a_rot_right = icon_load("frameworks/nuklear/icon/rot_right.png");
    media->a_right = icon_load("frameworks/nuklear/icon/right.png");
    media->a_left = icon_load("frameworks/nuklear/icon/left.png");
    media->a_up = icon_load("frameworks/nuklear/icon/up.png");
    media->a_down = icon_load("frameworks/nuklear/icon/down.png");
	media->unchecked = icon_load("frameworks/nuklear/icon/unchecked.png");
	media->checked = icon_load("frameworks/nuklear/icon/checked.png");
	media->rocket = icon_load("frameworks/nuklear/icon/rt.png");
    media->del = icon_load("frameworks/nuklear/icon/delete.png");
    media->dir = icon_load("frameworks/nuklear/icon/directory.png");
    media->convert = icon_load("frameworks/nuklear/icon/export.png");
    media->icons.default_file = icon_load("frameworks/nuklear/icon/default.png");
    media->zoom_in = icon_load("frameworks/nuklear/icon/zoom_in.png");
    media->zoom_out = icon_load("frameworks/nuklear/icon/zoom_out.png");
}


void	loading_media(struct media *media, struct nk_font_atlas *atlas, struct nk_context *ctx, struct device *device)
{
	const void *image; int w, h;
	struct nk_font_config cfg = nk_font_config(0);

	cfg.oversample_h = 3; cfg.oversample_v = 2;
	/* Loading one font with different heights is only required if you want higher
	 * quality text otherwise you can just set the font height directly
	 * e.g.: ctx->style.font.height = 20. */
	nk_font_atlas_init_default(atlas);
	nk_font_atlas_begin(atlas);
	media->font_14 = nk_font_atlas_add_from_file(atlas, "frameworks/nuklear/extra_font/Roboto-Regular.ttf", 14.0f, &cfg);
	media->font_18 = nk_font_atlas_add_from_file(atlas, "frameworks/nuklear/extra_font/Roboto-Regular.ttf", 18.0f, &cfg);
	media->font_20 = nk_font_atlas_add_from_file(atlas, "frameworks/nuklear/extra_font/Roboto-Regular.ttf", 20.0f, &cfg);
	media->font_22 = nk_font_atlas_add_from_file(atlas, "frameworks/nuklear/extra_font/Roboto-Regular.ttf", 22.0f, &cfg);
	image = nk_font_atlas_bake(atlas, &w, &h, NK_FONT_ATLAS_RGBA32);
	device_upload_atlas(device, image, w, h);
	nk_font_atlas_end(atlas, nk_handle_id((int)device->font_tex), &device->null);
	nk_init_default(ctx, &media->font_14->handle);


	/* icons */
	glEnable(GL_TEXTURE_2D);
	load_icon_object(media);

	// media->menu[0] = icon_load("frameworks/nuklear/icon/plan.png");
	// media->menu[1] = icon_load("frameworks/nuklear/icon/sphere.png");
	// media->menu[2] = icon_load("frameworks/nuklear/icon/cone.png");
	// media->menu[3] = icon_load("frameworks/nuklear/icon/cylinder.png");
	// media->menu[4] = icon_load("frameworks/nuklear/icon/disk.png");
	// media->menu[5] = icon_load("frameworks/nuklear/icon/volume.png");

    // media_init(media);

    media->images[0] = icon_load("testfiles/0.png");
    media->images[1] = icon_load("testfiles/1.png");
    media->images[2] = icon_load("testfiles/2.png");
    media->images[3] = icon_load("testfiles/3.png");
    media->images[4] = icon_load("testfiles/4.png");
    media->images[5] = icon_load("testfiles/5.png");
  	media->images[6] = icon_load("testfiles/6.png");
  	media->images[7] = icon_load("testfiles/7.png");
  	media->images[8] = icon_load("testfiles/8.png");
}
