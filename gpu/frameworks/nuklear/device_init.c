#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_FONT
#include "rt.h"
#include "nuklear.h"
#include "gui.h"
#include <assert.h>

static void	buffer_setup_end(struct device *dev)
{
	GLsizei vs = sizeof(struct nk_glfw_vertex);
	size_t vp = offsetof(struct nk_glfw_vertex, position);
	size_t vt = offsetof(struct nk_glfw_vertex, uv);
	size_t vc = offsetof(struct nk_glfw_vertex, col);
	glGenBuffers(1, &dev->vbo);
	glGenBuffers(1, &dev->ebo);
	glGenVertexArrays(1, &dev->vao);
	glBindVertexArray(dev->vao);
	glBindBuffer(GL_ARRAY_BUFFER, dev->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dev->ebo);
	glEnableVertexAttribArray((GLuint)dev->attrib_pos);
	glEnableVertexAttribArray((GLuint)dev->attrib_uv);
	glEnableVertexAttribArray((GLuint)dev->attrib_col);
	glVertexAttribPointer((GLuint)dev->attrib_pos, 2, GL_FLOAT, GL_FALSE, vs, (void*)vp);
	glVertexAttribPointer((GLuint)dev->attrib_uv, 2, GL_FLOAT, GL_FALSE, vs, (void*)vt);
	glVertexAttribPointer((GLuint)dev->attrib_col, 4, GL_UNSIGNED_BYTE, GL_TRUE, vs, (void*)vc);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

static void	buffer_default_gl(struct device *dev)
{
	GLint status;

	glCompileShader(dev->vert_shdr);
	glCompileShader(dev->frag_shdr);
	glGetShaderiv(dev->vert_shdr, GL_COMPILE_STATUS, &status);
	assert(status == GL_TRUE);
	glGetShaderiv(dev->frag_shdr, GL_COMPILE_STATUS, &status);
	assert(status == GL_TRUE);
	glAttachShader(dev->prog, dev->vert_shdr);
	glAttachShader(dev->prog, dev->frag_shdr);
	glLinkProgram(dev->prog);
	glGetProgramiv(dev->prog, GL_LINK_STATUS, &status);
	assert(status == GL_TRUE);
	dev->uniform_tex = glGetUniformLocation(dev->prog, "Texture");
	dev->uniform_proj = glGetUniformLocation(dev->prog, "ProjMtx");
	dev->attrib_pos = glGetAttribLocation(dev->prog, "Position");
	dev->attrib_uv = glGetAttribLocation(dev->prog, "TexCoord");
	dev->attrib_col = glGetAttribLocation(dev->prog, "Color");
}

void		device_init(struct device *dev)
{
	static const GLchar	*vertex_shader =
		NK_SHADER_VERSION
		"uniform mat4 ProjMtx;\n""in vec2 Position;\n""in vec2 TexCoord;\n"
		"in vec4 Color;\n""out vec2 Frag_UV;\n""out vec4 Frag_Color;\n"
		"void main() {\n""   Frag_UV = TexCoord;\n""   Frag_Color = Color;\n"
		"   gl_Position = ProjMtx * vec4(Position.xy, 0, 1);\n""}\n";
	static const GLchar	*fragment_shader =
		NK_SHADER_VERSION
		"precision mediump float;\n""uniform sampler2D Texture;\n"
		"in vec2 Frag_UV;\n""in vec4 Frag_Color;\n""out vec4 Out_Color;\n""void main(){\n"
		"   Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n""}\n";
	nk_buffer_init_default(&dev->cmds);
	dev->prog = glCreateProgram();
	dev->vert_shdr = glCreateShader(GL_VERTEX_SHADER);
	dev->frag_shdr = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(dev->vert_shdr, 1, &vertex_shader, 0);
	glShaderSource(dev->frag_shdr, 1, &fragment_shader, 0);
	buffer_default_gl(dev);
	buffer_setup_end(dev);
}

void		device_upload_atlas(struct device *dev, const void *image, int width, int height)
{
	glGenTextures(1, &dev->font_tex);
	glBindTexture(GL_TEXTURE_2D, dev->font_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, image);
}

void		device_shutdown(struct device *dev)
{
	glDetachShader(dev->prog, dev->vert_shdr);
	glDetachShader(dev->prog, dev->frag_shdr);
	glDeleteShader(dev->vert_shdr);
	glDeleteShader(dev->frag_shdr);
	glDeleteProgram(dev->prog);
	glDeleteTextures(1, &dev->font_tex);
	glDeleteBuffers(1, &dev->vbo);
	glDeleteBuffers(1, &dev->ebo);
	nk_buffer_free(&dev->cmds);
}
