/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:20:10 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/03 17:40:26 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		allocate_vertex_buffer(struct device *dev, enum nk_anti_aliasing aa,
			struct nk_context *ctx)
{
	static const struct nk_draw_vertex_layout_element	vertex_layout[] = {
	{NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(struct nk_glfw_vertex,
	position)}, {NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(struct
	nk_glfw_vertex, uv)}, {NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8,
	NK_OFFSETOF(struct nk_glfw_vertex, col)}, {NK_VERTEX_LAYOUT_END}};
	struct nk_convert_config							config;

	glBindVertexArray(dev->vao);
	glBindBuffer(GL_ARRAY_BUFFER, dev->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dev->ebo);
	glBufferData(GL_ARRAY_BUFFER, MAX_VERTEX_MEMORY, NULL, GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_ELEMENT_MEMORY, NULL,
			GL_STREAM_DRAW);
	NK_MEMSET(&config, 0, sizeof(config));
	config.vertex_layout = vertex_layout;
	config.vertex_size = sizeof(struct nk_glfw_vertex);
	config.vertex_alignment = NK_ALIGNOF(struct nk_glfw_vertex);
	config.null = dev->null;
	config.circle_segment_count = 22;
	config.curve_segment_count = 22;
	config.arc_segment_count = 22;
	config.global_alpha = 1.0f;
	config.shape_AA = aa;
	config.line_AA = aa;
	allocate_vertex_buffer_next(ctx, dev, config);
}

void		draw_render(t_cluster *cluster)
{
	static int i;

	if (cluster->world->video_buffer != NULL && cluster->world->redraw == 1)
	{
		cluster->world->on = 1;
		ft_bzero(cluster->world->video_buffer, WIN_WIDTH * WIN_HEIGHT
				* 4 * sizeof(unsigned char));
		ft_printf("Redraw Scène next time %d \n", i++);
		refresh_viewplane(cluster->world);
		if (cluster->world->mode_cluster == 1)
		{
			ft_putstr("Waiting for connection...\n");
			if (cluster->client_list != NULL)
				render_clustering(cluster);
			ft_putstr("End of connexion, get started again\n");
		}
		else
			rt(cluster->world);
		if (cluster->world->keys.pad_0)
			effect_application(cluster->world);
		cluster->world->redraw = 0;
		cluster->world->reload_buffer = 1;
	}
}

void		glfw_init_ratio(GLFWwindow *win, t_cluster cluster, t_world *world)
{
	glfwSetWindowAspectRatio(win, 16, 9);
	glfwSetWindowSizeLimits(win, 1024, 768, GLFW_DONT_CARE, GLFW_DONT_CARE);
	glfwGetWindowSize(win, &(cluster).world->screen.width,
			&(cluster).world->screen.height);
	glfwGetFramebufferSize(win, &(cluster).world->screen.display_width,
			&(cluster).world->screen.display_height);
	world->screen.scale.x = (float)cluster.world->screen.display_width /
		(float)cluster.world->screen.width;
	world->screen.scale.y = (float)cluster.world->screen.display_height /
		(float)cluster.world->screen.height;
}

void		glfw_viewport(t_cluster cluster, struct device *device,
			struct nk_context *ctx, GLFWwindow *win)
{
	glViewport(0, 0, cluster.world->screen.display_width,
			cluster.world->screen.display_height);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	device_draw(device, ctx, &(cluster.world->screen),
			NK_ANTI_ALIASING_ON);
	glfwSwapBuffers(win);
}

void		interface_launch(t_world *world)
{
	static GLFWwindow		*win;
	t_cluster				cluster;
	struct device			device;
	struct nk_context		ctx;
	struct media			media;

	cluster_initialize(world, &cluster);
	init_glfw_start(&win, &ctx, &(cluster).world->screen);
	device_init(&device);
	loading_media(&media, &ctx, &device);
	while (!glfwWindowShouldClose(win))
	{
		glfw_init_ratio(win, cluster, world);
		nk_input_begin(&ctx);
		glfwPollEvents();
		allocate_keys(&ctx, win);
		if (render_condition(&ctx, world) == 0)
			break ;
		draw_render(&cluster);
		gui_calls(&ctx, &media, cluster.world);
		glfw_viewport(cluster, &device, &ctx, win);
	}
	delete_object(ctx, media);
	device_shutdown(&device);
	glfwTerminate();
}
