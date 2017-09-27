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
    printf("Error %d: %s\n", e, d);
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

	media->menu[0] = icon_load("frameworks/nuklear/icon/plan.png");
	media->menu[1] = icon_load("frameworks/nuklear/icon/sphere.png");
	media->menu[2] = icon_load("frameworks/nuklear/icon/cone.png");
	media->menu[3] = icon_load("frameworks/nuklear/icon/cylinder.png");
	media->menu[4] = icon_load("frameworks/nuklear/icon/disk.png");
	media->menu[5] = icon_load("frameworks/nuklear/icon/volume.png");

    media_init(media);

    media->images[0] = icon_load("testfiles/0.png");
    media->images[1] = icon_load("testfiles/1.png");
    media->images[2] = icon_load("testfiles/2.png");
    media->images[3] = icon_load("testfiles/3.png");
    media->images[4] = icon_load("testfiles/4.png");
    media->images[5] = icon_load("testfiles/5.png");

	// int i;
	// for (i = 0; i < 1; ++i)
	// {
	// 	char buffer[256];
	// 	sprintf(buffer, "frameworks/nuklear/images/image%d.png", (i+1));
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
