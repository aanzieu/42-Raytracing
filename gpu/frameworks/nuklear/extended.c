/* nuklear - v1.05 - public domain */
#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "interface.h"
#include "gui.h"
#include "cluster.h"

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

	t_cluster	cluster;

	cluster_initialize(world, &cluster);
	printf("test init cluster\n");
		// ft_bzero(cluster.world->a_h, cluster.world->size_main);

	/* GUI */
	struct device device;
	struct nk_context ctx;
	struct nk_font_atlas atlas;
	struct file_browser browser;
	struct media media;
	int i = 0;

	init_glfw_start(&win, &ctx, &(cluster).world->screen);
	/* GUI */
	device_init(&device);
	loading_media(&media, &atlas, &ctx, &device);
	file_browser_init(&browser, &media);
	while (!glfwWindowShouldClose(win))
	{
		/* High DPI displays */
		glfwSetWindowAspectRatio(win, 16, 9);
		glfwSetWindowSizeLimits(win, 1024, 768, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwGetWindowSize(win, &(cluster).world->screen.width, &(cluster).world->screen.height);
		glfwGetFramebufferSize(win, &(cluster).world->screen.display_width, &(cluster).world->screen.display_height);
		world->screen.scale.x = (float)cluster.world->screen.display_width/(float)cluster.world->screen.width;
		world->screen.scale.y = (float)cluster.world->screen.display_height/(float)cluster.world->screen.height;

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
		nk_input_key(&ctx, NK_KEY_X, glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS);
		if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
				glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		{
			nk_input_key(&ctx, NK_KEY_COPY, glfwGetKey(win, GLFW_KEY_C) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_PASTE, glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_CUT, glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS);
			nk_input_key(&ctx, NK_KEY_SHIFT, 1);
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
		if (cluster.world->video_buffer != NULL && cluster.world->redraw == 1)
		{
			ft_bzero(cluster.world->video_buffer, WIN_WIDTH * WIN_HEIGHT * 4 * sizeof(unsigned char));
			ft_printf("Redraw Scène next time %d \n", i++);
			refresh_viewplane(cluster.world);
			if (cluster.world->mode_cluster == 1)
			{
				ft_putstr("Waiting for connection...\n");
				render_clustering(world, &cluster);
				ft_putstr("End of connexion, get started again\n");
			}
			else
				rt(cluster.world);
			if (cluster.world->keys.pad_0)
				effect_application(cluster.world);
			cluster.world->redraw = 0;
			cluster.world->reload_buffer = 1;
		}
		gui_calls(&browser, &ctx, &media, cluster.world);

		/* Draw */
		glViewport(0, 0, cluster.world->screen.display_width, cluster.world->screen.display_height);
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		device_draw(&device, &ctx, &(cluster.world->screen), NK_ANTI_ALIASING_ON);
		glfwSwapBuffers(win);

	}
	glDeleteTextures(1,(const GLuint*)&media.plane.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.sphere.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.cone.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.cylinder.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.disk.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.paraboloid.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.hyperboloid.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.mobius.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.cube.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.h_cube.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.torus.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.triangle.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.light.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.cam.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.rec.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.rec_on.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.a_rot_left.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.a_rot_right.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.a_right.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.a_left.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.a_up.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.a_down.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.unchecked.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.checked.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.rocket.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.dir.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.del.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.convert.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.zoom_in.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.zoom_out.handle.id);
	glDeleteTextures(1,(const GLuint*)&media.icons.default_file.handle.id);

	file_browser_free(&browser);
	nk_font_atlas_clear(&atlas);
	nk_free(&ctx);
	device_shutdown(&device);
	glfwTerminate();
	return 0;
}
