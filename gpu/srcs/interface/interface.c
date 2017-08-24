/* nuklear - v1.05 - public domain */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: PZC <PZC@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/08/21 11:47:33 by svilau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
// #include "interface.h"
// #define NK_IMPLEMENTATION
#include <rt.h>
#include "nuklear.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stdarg.h>
// #include <string.h>
// #include <math.h>
// #include <assert.h>
// #include <math.h>
// #include <time.h>
// #include <limits.h>
// #include <unistd.h>
// #include <dirent.h>
// #include <rt.h>
// #include <colors.h>

// #include </Users/svilau/brew/Cellar/glew/2.1.0/include/GL/glew.h>
// #include </Users/svilau/brew/Cellar/glfw/3.2.1/include/GLFW/glfw3.h>

// #define NK_INCLUDE_FIXED_TYPES
// #define NK_INCLUDE_STANDARD_IO
// #define NK_INCLUDE_DEFAULT_ALLOCATOR
// #define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
// #define NK_INCLUDE_FONT_BAKING
// #define NK_INCLUDE_DEFAULT_FONT
// #define NK_IMPLEMENTATION
// #include "nuklear.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

// /* macros */
// #define WINDOW_WIDTH 1200
// #define WINDOW_HEIGHT 800

// #define MAX_VERTEX_MEMORY 512 * 1024
// #define MAX_ELEMENT_MEMORY 128 * 1024

// #define UNUSED(a) (void)a
// #define MIN(a,b) ((a) < (b) ? (a) : (b))
// #define MAX(a,b) ((a) < (b) ? (b) : (a))
// #define LEN(a) (sizeof(a)/sizeof(a)[0])

// #ifdef __APPLE__
//   #define NK_SHADER_VERSION "#version 150\n"
// #else
//   #define NK_SHADER_VERSION "#version 300 es\n"
// #endif

struct media;

void    gui_calls(struct nk_context *ctx, struct media *media, t_world *world)
{
    printf("TEST\n");
    return;
    // printf("test\n");
    // basic_demo(&ctx, &media);
    //     button_demo(ctx, media, world);
    //     if (world->a_h != NULL)
    //         render_demo(ctx, media, world->a_h, world->video_buffer);
    //     grid_demo(&ctx, &media);
}