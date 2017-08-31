/* nuklear - v1.05 - public domain */
#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "header/interface.h"
#include "header/gui.h"


void	allocate_vertex_buffer(struct device *dev, enum nk_anti_aliasing AA, struct nk_context *ctx)
{

	void *vertices, *elements;
	struct nk_convert_config config;
	static const struct nk_draw_vertex_layout_element vertex_layout[] = {
		{NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(struct nk_glfw_vertex, position)},
		{NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(struct nk_glfw_vertex, uv)},
		{NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, NK_OFFSETOF(struct nk_glfw_vertex, col)},
		{NK_VERTEX_LAYOUT_END}
	};
	/* allocate vertex and element buffer */
	glBindVertexArray(dev->vao);
	glBindBuffer(GL_ARRAY_BUFFER, dev->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dev->ebo);
	glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_MEMORY, NULL, GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_ELEMENT_MEMORY, NULL, GL_STREAM_DRAW);
	vertices = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	elements = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	
	/* fill convert configuration */
	NK_MEMSET(&config, 0, sizeof(config));
	config.vertex_layout = vertex_layout;
	config.vertex_size = sizeof(struct nk_glfw_vertex);
	config.vertex_alignment = NK_ALIGNOF(struct nk_glfw_vertex);
	config.null = dev->null;
	config.circle_segment_count = 22;
	config.curve_segment_count = 22;
	config.arc_segment_count = 22;
	config.global_alpha = 1.0f;
	config.shape_AA = AA;
	config.line_AA = AA;

	/* setup buffers to load vertices and elements */
	struct nk_buffer vbuf, ebuf;
	nk_buffer_init_fixed(&vbuf, vertices, MAX_VERTEX_MEMORY);
	nk_buffer_init_fixed(&ebuf, elements, MAX_ELEMENT_MEMORY);
	nk_convert(ctx, &dev->cmds, &vbuf, &ebuf, &config);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

int interface_launch(t_world *world, char *argv)
{
	/* Platform */
	(void)argv;
	static GLFWwindow *win;
	t_screen	screen;
	/* GUI */
	struct device device;
	struct nk_font_atlas atlas;
	struct media media;
	struct nk_context ctx;

	init_glfw_start(&win, &ctx, &screen);
	/* GUI */
	device_init(&device);
	loading_media(&media, &atlas, &ctx, &device);
	// run_interface();
	while (!glfwWindowShouldClose(win))
	{
		/* High DPI displays */
		glfwGetWindowSize(win, &screen.width, &screen.height);
		glfwGetFramebufferSize(win, &screen.display_width, &screen.display_height);
		screen.scale.x = (float)screen.display_width/(float)screen.width;
		screen.scale.y = (float)screen.display_height/(float)screen.height;

		/* Input */

		double x, y;
		nk_input_begin(&ctx);
		glfwPollEvents();
		nk_input_key(&ctx, NK_KEY_DEL, glfwGetKey(win, GLFW_KEY_DELETE) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_ENTER, glfwGetKey(win, GLFW_KEY_ENTER) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_TAB, glfwGetKey(win, GLFW_KEY_TAB) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_BACKSPACE, glfwGetKey(win, GLFW_KEY_BACKSPACE) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_LEFT, glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_RIGHT, glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_UP, glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_DOWN, glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS);
		nk_input_key(&ctx, NK_KEY_K, glfwGetKey(win, GLFW_KEY_K) == GLFW_PRESS);		
		nk_input_key(&ctx, NK_KEY_L, glfwGetKey(win, GLFW_KEY_L) == GLFW_PRESS);
		if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
				glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		{
			nk_input_key(&ctx, NK_KEY_COPY, glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_PASTE, glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_SHIFT, 1);
			printf("keypush test\n");
		}
		else
		{
			nk_input_key(&ctx, NK_KEY_COPY, 0);
			nk_input_key(&ctx, NK_KEY_PASTE, 0);
			nk_input_key(&ctx, NK_KEY_CUT, 0);
			nk_input_key(&ctx, NK_KEY_SHIFT, 0);
		}
		glfwGetCursorPos(win, &x, &y);
		nk_input_motion(&ctx, (int)x, (int)y);
		nk_input_button(&ctx, NK_BUTTON_LEFT, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
		nk_input_button(&ctx, NK_BUTTON_MIDDLE, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);
		nk_input_button(&ctx, NK_BUTTON_RIGHT, (int)x, (int)y, glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
		nk_input_end(&ctx);

		/* GUI */
		if (world->video_buffer != NULL)
			ft_bzero(world->video_buffer, WIN_WIDTH * WIN_HEIGHT * 4 * sizeof(unsigned char));
		gui_calls(&ctx, &media, world);

		/* Draw */
		glViewport(0, 0, screen.display_width, screen.display_height);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);        
		glClear(GL_COLOR_BUFFER_BIT);
		device_draw(&device, &ctx, &screen, NK_ANTI_ALIASING_ON);
		glfwSwapBuffers(win);
	}

	glDeleteTextures(1,(const GLuint*)&media.unchecked.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.checked.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.rocket.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.cloud.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.pen.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.play.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.pause.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.stop.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.next.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.prev.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.tools.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.dir.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.del.handle.id);

	nk_font_atlas_clear(&atlas);
	nk_free(&ctx);
	device_shutdown(&device);
	glfwTerminate();
	return 0;
}
