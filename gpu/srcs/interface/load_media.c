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
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <unistd.h>

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

static char*
str_duplicate(const char *src)
{
    char *ret;
    size_t len = strlen(src);
    if (!len) return 0;
    ret = (char*)malloc(len+1);
    if (!ret) return 0;
    memcpy(ret, src, len);
    ret[len] = '\0';
    return ret;
}

static void
dir_free_list(char **list, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i)
        free(list[i]);
    free(list);
}

static char**
dir_list(const char *dir, int return_subdirs, size_t *count)
{
    size_t n = 0;
    char buffer[MAX_PATH_LEN];
    char **results = NULL;
    const DIR *none = NULL;
    size_t capacity = 32;
    size_t size;
    DIR *z;

    assert(dir);
    assert(count);
    strncpy(buffer, dir, MAX_PATH_LEN);
    n = strlen(buffer);

    if (n > 0 && (buffer[n-1] != '/'))
        buffer[n++] = '/';

    size = 0;

    z = opendir(dir);
    if (z != none) {
        int nonempty = 1;
        struct dirent *data = readdir(z);
        nonempty = (data != NULL);
        if (!nonempty) return NULL;

        do {
            DIR *y;
            char *p;
            int is_subdir;
            if (data->d_name[0] == '.')
                continue;

            strncpy(buffer + n, data->d_name, MAX_PATH_LEN-n);
            y = opendir(buffer);
            is_subdir = (y != NULL);
            if (y != NULL) closedir(y);

            if ((return_subdirs && is_subdir) || (!is_subdir && !return_subdirs)){
                if (!size) {
                    results = (char**)calloc(sizeof(char*), capacity);
                } else if (size >= capacity) {
                    void *old = results;
                    capacity = capacity * 2;
                    results = (char**)realloc(results, capacity * sizeof(char*));
                    assert(results);
                    if (!results) free(old);
                }
                p = str_duplicate(data->d_name);
                results[size++] = p;
            }
        } while ((data = readdir(z)) != NULL);
    }

    if (z) closedir(z);
    *count = size;
    return results;
}


static struct file_group
FILE_GROUP(enum file_groups group, const char *name, struct nk_image *icon)
{
    struct file_group fg;
    fg.group = group;
    fg.name = name;
    fg.icon = icon;
    return fg;
}

static struct file
FILE_DEF(enum file_types type, const char *suffix, enum file_groups group)
{
    struct file fd;
    fd.type = type;
    fd.suffix = suffix;
    fd.group = group;
    return fd;
}

struct nk_image* media_icon_for_file(struct media *media, const char *file)
{
    int i = 0;
    const char *s = file;
    char suffix[4];
    int found = 0;
    memset(suffix, 0, sizeof(suffix));

    /* extract suffix .xxx from file */
    while (*s++ != '\0') {
        if (found && i < 3)
            suffix[i++] = *s;

        if (*s == '.') {
            if (found){
                found = 0;
                break;
            }
            found = 1;
        }
    }

    /* check for all file definition of all groups for fitting suffix*/
    for (i = 0; i < FILE_MAX && found; ++i) {
        struct file *d = &media->files[i];
        {
            const char *f = d->suffix;
            s = suffix;
            while (f && *f && *s && *s == *f) {
                s++; f++;
            }

            /* found correct file definition so */
            if (f && *s == '\0' && *f == '\0')
                return media->group[d->group].icon;
        }
    }
    return &media->icons.default_file;
}


static void
media_init(struct media *media)
{
    /* file groups */
    struct icons *icons = &media->icons;
    media->group[FILE_GROUP_DEFAULT] = FILE_GROUP(FILE_GROUP_DEFAULT,"default",&icons->default_file);
    media->group[FILE_GROUP_TEXT] = FILE_GROUP(FILE_GROUP_TEXT, "textual", &icons->text_file);
    media->group[FILE_GROUP_MUSIC] = FILE_GROUP(FILE_GROUP_MUSIC, "music", &icons->music_file);
    media->group[FILE_GROUP_FONT] = FILE_GROUP(FILE_GROUP_FONT, "font", &icons->font_file);
    media->group[FILE_GROUP_IMAGE] = FILE_GROUP(FILE_GROUP_IMAGE, "image", &icons->img_file);
    media->group[FILE_GROUP_MOVIE] = FILE_GROUP(FILE_GROUP_MOVIE, "movie", &icons->movie_file);

    /* files */
    media->files[FILE_DEFAULT] = FILE_DEF(FILE_DEFAULT, NULL, FILE_GROUP_DEFAULT);
    media->files[FILE_TEXT] = FILE_DEF(FILE_TEXT, "txt", FILE_GROUP_TEXT);
    media->files[FILE_C_SOURCE] = FILE_DEF(FILE_C_SOURCE, "c", FILE_GROUP_TEXT);
    media->files[FILE_CPP_SOURCE] = FILE_DEF(FILE_CPP_SOURCE, "cpp", FILE_GROUP_TEXT);
    media->files[FILE_HEADER] = FILE_DEF(FILE_HEADER, "h", FILE_GROUP_TEXT);
    media->files[FILE_CPP_HEADER] = FILE_DEF(FILE_HEADER, "hpp", FILE_GROUP_TEXT);
    media->files[FILE_MP3] = FILE_DEF(FILE_MP3, "mp3", FILE_GROUP_MUSIC);
    media->files[FILE_WAV] = FILE_DEF(FILE_WAV, "wav", FILE_GROUP_MUSIC);
    media->files[FILE_OGG] = FILE_DEF(FILE_OGG, "ogg", FILE_GROUP_MUSIC);
    media->files[FILE_TTF] = FILE_DEF(FILE_TTF, "ttf", FILE_GROUP_FONT);
    media->files[FILE_BMP] = FILE_DEF(FILE_BMP, "bmp", FILE_GROUP_IMAGE);
    media->files[FILE_PNG] = FILE_DEF(FILE_PNG, "png", FILE_GROUP_IMAGE);
    media->files[FILE_JPEG] = FILE_DEF(FILE_JPEG, "jpg", FILE_GROUP_IMAGE);
    media->files[FILE_PCX] = FILE_DEF(FILE_PCX, "pcx", FILE_GROUP_IMAGE);
    media->files[FILE_TGA] = FILE_DEF(FILE_TGA, "tga", FILE_GROUP_IMAGE);
    media->files[FILE_GIF] = FILE_DEF(FILE_GIF, "gif", FILE_GROUP_IMAGE);
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
	media->paraboloid = icon_load("srcs/interface/icon/paraboloid.png");
	media->hyperboloid = icon_load("srcs/interface/icon/hyperboloid.png");
	media->moebius = icon_load("srcs/interface/icon/moebius.png");
	media->cube = icon_load("srcs/interface/icon/cube.png");
	media->torus = icon_load("srcs/interface/icon/torus.png");
	media->triangle = icon_load("srcs/interface/icon/triangle.png");

	media->rec = icon_load("srcs/interface/icon/camera.png");
	media->rec_on = icon_load("srcs/interface/icon/camera_on.png");

    media->play = icon_load("srcs/interface/icon/rot_left.png");
    media->pause = icon_load("srcs/interface/icon/rot_right.png");
    media->next =  icon_load("srcs/interface/icon/right.png");
    media->prev =  icon_load("srcs/interface/icon/left.png");
    media->up =  icon_load("srcs/interface/icon/up.png");
    media->down =  icon_load("srcs/interface/icon/down.png");

	media->unchecked = icon_load("srcs/interface/icon/unchecked.png");
	media->checked = icon_load("srcs/interface/icon/checked.png");
	media->rocket = icon_load("srcs/interface/icon/rt.png");
	media->cloud = icon_load("srcs/interface/icon/cloud.png");
	media->pen = icon_load("srcs/interface/icon/pen.png");
	media->stop = icon_load("srcs/interface/icon/stop.png");
	media->tools = icon_load("srcs/interface/icon/tools.png");
	media->dir = icon_load("srcs/interface/icon/directory.png");
	media->copy = icon_load("srcs/interface/icon/copy.png");
	media->convert = icon_load("srcs/interface/icon/export.png");
	media->del = icon_load("srcs/interface/icon/delete.png");
	media->edit = icon_load("srcs/interface/icon/edit.png");
	media->menu[0] = icon_load("srcs/interface/icon/plan.png");
	media->menu[1] = icon_load("srcs/interface/icon/sphere.png");
	media->menu[2] = icon_load("srcs/interface/icon/cone.png");
	media->menu[3] = icon_load("srcs/interface/icon/cylinder.png");
	media->menu[4] = icon_load("srcs/interface/icon/disk.png");
	media->menu[5] = icon_load("srcs/interface/icon/volume.png");

	media->icons.home = icon_load("srcs/interface/icon/home.png");
    media->icons.directory = icon_load("srcs/interface/icon/directory.png");
    media->icons.computer = icon_load("srcs/interface/icon/computer.png");
    media->icons.desktop = icon_load("srcs/interface/icon/desktop.png");
    media->icons.default_file = icon_load("srcs/interface/icon/default.png");
    media->icons.text_file = icon_load("srcs/interface/icon/text.png");
    media->icons.music_file = icon_load("srcs/interface/icon/music.png");
    media->icons.font_file =  icon_load("srcs/interface/icon/font.png");
    media->icons.img_file = icon_load("srcs/interface/icon/img.png");
    media->icons.movie_file = icon_load("srcs/interface/icon/movie.png");
    media_init(media);

    media->images[0] = icon_load("testfiles/1.png");
    media->images[1] = icon_load("testfiles/2.png");
    media->images[2] = icon_load("testfiles/3.png");

	// int i;
	// for (i = 0; i < 1; ++i)
	// {
	// 	char buffer[256];
	// 	sprintf(buffer, "srcs/interface/images/image%d.png", (i+1));
	// 	media->images[i] = icon_load(buffer);
	// }

}

void file_browser_reload_directory_content(struct file_browser *browser, const char *path)
{
    strncpy(browser->directory, path, MAX_PATH_LEN);
    dir_free_list(browser->files, browser->file_count);
    dir_free_list(browser->directories, browser->dir_count);
    browser->files = dir_list(path, 0, &browser->file_count);
    browser->directories = dir_list(path, 1, &browser->dir_count);
}

void file_browser_init(struct file_browser *browser, struct media *media)
{
    ft_memset(browser, 0, sizeof(*browser));
    browser->media = media;
    {
        /* load files and sub-directory list */
       char *home = getenv("HOME");
#ifdef _WIN32
        if (!home) home = getenv("USERPROFILE");
#else
        if (!home) home = getpwuid(getuid())->pw_dir;
        {
            size_t l;
            ft_strncpy(browser->home, home, MAX_PATH_LEN);
            l = ft_strlen(browser->home);
            ft_strcpy(browser->home + l, "/");
            strcpy(browser->directory, browser->home);
        }
#endif
        {
            size_t l;
            ft_strcpy(browser->desktop, browser->home);
            l = ft_strlen(browser->desktop);
            ft_strcpy(browser->desktop + l, "desktop/");
        }
        browser->files = dir_list(browser->directory, 0, &browser->file_count);
        browser->directories = dir_list(browser->directory, 1, &browser->dir_count);
    }
}


void file_browser_free(struct file_browser *browser)
{
    if (browser->files)
        dir_free_list(browser->files, browser->file_count);
    if (browser->directories)
        dir_free_list(browser->directories, browser->dir_count);
    browser->files = NULL;
    browser->directories = NULL;
    memset(browser, 0, sizeof(*browser));
}
