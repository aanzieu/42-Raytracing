#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_FONT

#include "header/stb_image.h"
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"
#include <assert.h>

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
	media->font_14 = nk_font_atlas_add_from_file(atlas, "srcs/interface/extra_font/Roboto-Regular.ttf", 14.0f, &cfg);
	media->font_18 = nk_font_atlas_add_from_file(atlas, "srcs/interface/extra_font/Roboto-Regular.ttf", 18.0f, &cfg);
	media->font_20 = nk_font_atlas_add_from_file(atlas, "srcs/interface/extra_font/Roboto-Regular.ttf", 20.0f, &cfg);
	media->font_22 = nk_font_atlas_add_from_file(atlas, "srcs/interface/extra_font/Roboto-Regular.ttf", 22.0f, &cfg);
	image = nk_font_atlas_bake(atlas, &w, &h, NK_FONT_ATLAS_RGBA32);
	device_upload_atlas(device, image, w, h);
	nk_font_atlas_end(atlas, nk_handle_id((int)device->font_tex), &device->null);
	nk_init_default(ctx, &media->font_14->handle);

	/* icons */
	glEnable(GL_TEXTURE_2D);
	media->plane = icon_load("srcs/interface/icon/plan.png");
	media->sphere = icon_load("srcs/interface/icon/sphere.png");
	media->cone = icon_load("srcs/interface/icon/cone.png");
	media->cylinder = icon_load("srcs/interface/icon/cylinder.png");
	media->disk = icon_load("srcs/interface/icon/disk.png");
	
	media->unchecked = icon_load("srcs/interface/icon/unchecked.png");
	media->checked = icon_load("srcs/interface/icon/checked.png");
	// media.rocket = icon_load("srcs/interface/icon/rocket.png");
	// media.cloud = icon_load("srcs/interface/icon/cloud.png");
	// media.pen = icon_load("srcs/interface/icon/pen.png");
	// media.play = icon_load("srcs/interface/icon/play.png");
	// media.pause = icon_load("srcs/interface/icon/pause.png");
	// media.stop = icon_load("srcs/interface/icon/stop.png");
	// media.next =  icon_load("srcs/interface/icon/next.png");
	// media.prev =  icon_load("srcs/interface/icon/prev.png");
	// media.tools = icon_load("srcs/interface/icon/tools.png");
	// media.dir = icon_load("srcs/interface/icon/directory.png");
	// media.copy = icon_load("srcs/interface/icon/copy.png");
	// media.convert = icon_load("srcs/interface/icon/export.png");
	// media.del = icon_load("srcs/interface/icon/delete.png");
	// media.edit = icon_load("srcs/interface/icon/edit.png");
	// media.menu[0] = icon_load("srcs/interface/icon/home.png");
	// media.menu[1] = icon_load("srcs/interface/icon/phone.png");
	// media.menu[2] = icon_load("srcs/interface/icon/plane.png");
	// media.menu[3] = icon_load("srcs/interface/icon/wifi.png");
	// media.menu[4] = icon_load("srcs/interface/icon/settings.png");
	// media.menu[5] = icon_load("srcs/interface/icon/volume.png");

	int i;
	for (i = 0; i < 9; ++i)
	{
		char buffer[256];
		sprintf(buffer, "srcs/interface/images/image%d.png", (i+1));
		media->images[i] = icon_load(buffer);
	}

}