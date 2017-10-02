/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_loading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:53:31 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/02 16:49:28 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../../includes/rt.h"
#include "nuklear.h"
#include "gui.h"

void			die(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputs("\n", stderr);
	exit(EXIT_FAILURE);
}

void			error_callback(int e, const char *d)
{
	ft_printf("Error %d: %s\n", e, d);
}

char			*file_load(const char *path, size_t *siz)
{
	char *buf;
	FILE *fd;

	fd = fopen(path, "rb");
	if (!fd)
		die("Failed to open file: %s\n", path);
	fseek(fd, 0, SEEK_END);
	*siz = (size_t)ftell(fd);
	fseek(fd, 0, SEEK_SET);
	buf = (char*)calloc(*siz, 1);
	fread(buf, *siz, 1, fd);
	fclose(fd);
	return (buf);
}

void			delete_object_next(struct media media)
{
	glDeleteTextures(1, (const GLuint*)&media.plane.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.sphere.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.cone.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.cylinder.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.disk.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.paraboloid.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.hyperboloid.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.mobius.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.cube.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.h_cube.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.torus.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.triangle.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.light.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.cam.handle.id);
}

void			delete_object(struct nk_context ctx, struct media media)
{
	glDeleteTextures(1, (const GLuint*)&media.rec.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.rec_on.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.a_rot_left.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.a_rot_right.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.a_right.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.a_left.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.a_up.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.a_down.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.unchecked.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.checked.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.rocket.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.dir.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.del.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.convert.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.zoom_in.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.zoom_out.handle.id);
	glDeleteTextures(1, (const GLuint*)&media.icons.default_file.handle.id);
	delete_object_next(media);
	nk_free(&ctx);
}
