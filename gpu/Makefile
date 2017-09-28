# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/16 11:32:29 by aanzieu           #+#    #+#              #
#    Updated: 2017/09/27 17:21:09 by xpouzenc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

MAKE = make
MAKE_FLAGS = --no-print-directory

INCLUDE = -I includes -I libft
INCLUDECUDA = -I srcs/cuda/cudaheader
INCLUDEXML =  -I /Users/$(USER)/.brew/opt/libxml2/include/libxml2
INCLUDENK = -I frameworks/nuklear/include

SRC_DIR = srcs
SRC_CUDA_DIR = srcs/cuda/cudasrc
SRC_NUKLEAR = frameworks/nuklear

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SDL_FLAGS = `sdl-config --cflags --libs`
XML_FLAGS = `xml2-config --cflags --exec-prefix=/usr --libs`

GLFW3 = /Users/$(USER)/.brew/opt/glfw/lib/libglfw.3.2.dylib
#GLFW3 = frameworks/glfw/lib/libglfw.3.2.dylib
GLEW = frameworks/glew/lib/libGLEW.a

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

RM = rm -f
RF = rm -rf

###################################################
##--- LIST of Sources                         ---##
###################################################

SRC_CUDA =		$(SRC_CUDA_DIR)/gpu_rtv1.cu \
				$(SRC_CUDA_DIR)/ray_tracer_cpu.cu \
				$(SRC_CUDA_DIR)/ray_tracer_gpu.cu \
				$(SRC_CUDA_DIR)/ray_tracer_utils.cu \
				\
				$(SRC_CUDA_DIR)/libmath/vectors/vectors.cu \
				$(SRC_CUDA_DIR)/libmath/vectors/vectors2.cu \
				$(SRC_CUDA_DIR)/libmath/vectors/translation.cu \
				$(SRC_CUDA_DIR)/libmath/vectors/rotation.cu \
				\
				$(SRC_CUDA_DIR)/libmath/conversion/angles.cu \
				$(SRC_CUDA_DIR)/libmath/equation/equation_resolve.cu \
				$(SRC_CUDA_DIR)/libmath/equation/solve_quartic.cu \
				$(SRC_CUDA_DIR)/libmath/equation/solve_quadratic.cu \
				$(SRC_CUDA_DIR)/libmath/equation/n_degree_resolve.cu \
				$(SRC_CUDA_DIR)/libmath/equation/equation_utils.cu \
				\
				$(SRC_CUDA_DIR)/objects/sphere.cu \
				$(SRC_CUDA_DIR)/objects/plane.cu \
				$(SRC_CUDA_DIR)/objects/cylinder.cu \
				$(SRC_CUDA_DIR)/objects/paraboloid.cu \
				$(SRC_CUDA_DIR)/objects/hyperboloid.cu \
				$(SRC_CUDA_DIR)/objects/cone.cu \
				$(SRC_CUDA_DIR)/objects/disk.cu \
				$(SRC_CUDA_DIR)/objects/mobius.cu \
				$(SRC_CUDA_DIR)/objects/torus.cu \
				$(SRC_CUDA_DIR)/objects/triangle.cu \
				$(SRC_CUDA_DIR)/objects/cube.cu \
				$(SRC_CUDA_DIR)/objects/hollow_cube.cu \
				\
				$(SRC_CUDA_DIR)/shading/shading.cu \
				\
				$(SRC_CUDA_DIR)/material/material_cpu.cu \
				$(SRC_CUDA_DIR)/material/material_gpu.cu \
				$(SRC_CUDA_DIR)/material/perlin_noise.cu \
				$(SRC_CUDA_DIR)/material/perlin_presets.cu \
				\
				$(SRC_CUDA_DIR)/camera/camera.cu \
				\
				$(SRC_CUDA_DIR)/colors/colors.cu \
				$(SRC_CUDA_DIR)/colors/colors2.cu

SRC_NUK =		$(SRC_NUKLEAR)/device_init.c \
				$(SRC_NUKLEAR)/device_init_next.c \
				$(SRC_NUKLEAR)/load_media.c \
				$(SRC_NUKLEAR)/extended.c \

SRC =			$(SRC_DIR)/main.c \
				$(SRC_DIR)/launch_cpu_gpu.c \
				$(SRC_DIR)/launch_configuration.c \
				$(SRC_DIR)/data_setup.c \
				$(SRC_DIR)/main_master.c \
				$(SRC_DIR)/main_client.c \
				$(SRC_DIR)/free_memory.c \
				$(SRC_DIR)/render.c \
				$(SRC_DIR)/display_functions.c \
				\
				$(SRC_DIR)/threads/malloc_objects_cpy.c \
				$(SRC_DIR)/threads/malloc_objects_cpy2.c \
				$(SRC_DIR)/threads/malloc_objects_cpy3.c \
				\
				$(SRC_DIR)/interface/interface.c \
				$(SRC_DIR)/interface/gui_utils.c \
				$(SRC_DIR)/interface/gui_utils2.c \
				$(SRC_DIR)/interface/gui_utils3.c \
				$(SRC_DIR)/interface/gui_obj_parameters.c \
				$(SRC_DIR)/interface/gui_scene_parameters.c \
				$(SRC_DIR)/interface/gui_scene_parameters2.c \
				$(SRC_DIR)/interface/gui_effect_button.c \
				$(SRC_DIR)/interface/gui_render_scene.c \
				$(SRC_DIR)/interface/gui_topbar.c \
				$(SRC_DIR)/interface/gui_topbar2.c \
				$(SRC_DIR)/interface/gui_topbar_add_obj.c \
				$(SRC_DIR)/interface/gui_cam_controller.c \
				$(SRC_DIR)/interface/launch_scenes.c \
				$(SRC_DIR)/interface/mouse_event/mouse_press_left.c \
				$(SRC_DIR)/interface/mouse_event/mouse_press_middle.c \
				$(SRC_DIR)/interface/mouse_event/mouse_press_right.c \
				$(SRC_DIR)/interface/object_informations/obj_info_spheres.c \
				$(SRC_DIR)/interface/object_informations/obj_move.c \
				$(SRC_DIR)/interface/object_informations/obj_info_planes.c \
				$(SRC_DIR)/interface/object_informations/obj_info_cones.c \
				$(SRC_DIR)/interface/object_informations/obj_info_disks.c \
				$(SRC_DIR)/interface/object_informations/obj_info_cubes.c \
				$(SRC_DIR)/interface/object_informations/obj_info_h_cubes.c \
				$(SRC_DIR)/interface/object_informations/obj_info_triangles.c \
				$(SRC_DIR)/interface/object_informations/obj_info_cylinders.c \
				$(SRC_DIR)/interface/object_informations/obj_info_paraboloids.c \
				$(SRC_DIR)/interface/object_informations/obj_info_hyperboloids.c \
				$(SRC_DIR)/interface/object_informations/obj_info_torus.c \
				$(SRC_DIR)/interface/object_informations/obj_info_mobius.c \
				$(SRC_DIR)/interface/object_informations/obj_info_lights.c \
				$(SRC_DIR)/interface/object_informations/obj_info_utils.c \
				$(SRC_DIR)/interface/object_informations/obj_info_utils2.c \
				$(SRC_DIR)/interface/object_informations/obj_info_utils3.c \
				$(SRC_DIR)/interface/object_informations/object_refresh.c \
				$(SRC_DIR)/interface/object_informations/object_refresh2.c \
				$(SRC_DIR)/interface/object_informations/object_refresh3.c \
				$(SRC_DIR)/interface/remove_objects/remove_objects.c \
				$(SRC_DIR)/interface/remove_objects/remove_objects2.c \
				$(SRC_DIR)/interface/remove_objects/remove_objects3.c \
				$(SRC_DIR)/interface/key_press.c \
				$(SRC_DIR)/interface/free_objects/free_world.c \
				$(SRC_DIR)/interface/free_objects/free_objects.c \
				$(SRC_DIR)/interface/free_objects/free_objects_next.c \
				$(SRC_DIR)/interface/free_objects/free_objects_next2.c \
				\
				$(SRC_DIR)/effects/effects_options.c \
				$(SRC_DIR)/effects/effect_bayer.c \
				$(SRC_DIR)/effects/effect_black_and_white.c \
				$(SRC_DIR)/effects/effect_cartoon.c \
				$(SRC_DIR)/effects/effect_eight_bits.c \
				$(SRC_DIR)/effects/effect_negative.c \
				$(SRC_DIR)/effects/effect_sepia.c \
				$(SRC_DIR)/effects/effect_pastel.c \
				$(SRC_DIR)/effects/effect_anaglyph.c \
				\
				$(SRC_DIR)/loader/load_cones.c \
				$(SRC_DIR)/loader/load_torus.c \
				$(SRC_DIR)/loader/load_triangles.c \
				$(SRC_DIR)/loader/load_cubes.c \
				$(SRC_DIR)/loader/load_h_cubes.c \
				$(SRC_DIR)/loader/load_paraboloids.c \
				$(SRC_DIR)/loader/load_hyperboloids.c \
				$(SRC_DIR)/loader/load_spheres.c \
				$(SRC_DIR)/loader/load_mobius.c \
				$(SRC_DIR)/loader/load_cylinders.c \
				$(SRC_DIR)/loader/load_planes.c \
				$(SRC_DIR)/loader/load_disks.c \
				$(SRC_DIR)/loader/load_lights.c \
				\
				$(SRC_DIR)/events/event_handler.c \
				$(SRC_DIR)/events/key_press_handler.c \
				$(SRC_DIR)/events/key_release_handler.c \
				$(SRC_DIR)/events/mouse_handler.c \
				$(SRC_DIR)/events/screenshot_event.c \
				\
				$(SRC_DIR)/xml_parser/parser.c \
				$(SRC_DIR)/xml_parser/parse_camera.c \
				$(SRC_DIR)/xml_parser/parse_light.c \
				$(SRC_DIR)/xml_parser/parse_plane.c \
				$(SRC_DIR)/xml_parser/parse_sphere.c \
				$(SRC_DIR)/xml_parser/parse_mobius.c \
				$(SRC_DIR)/xml_parser/parse_cylinder.c \
				$(SRC_DIR)/xml_parser/parse_disk.c \
				$(SRC_DIR)/xml_parser/parse_cone.c \
				$(SRC_DIR)/xml_parser/parse_paraboloid.c \
				$(SRC_DIR)/xml_parser/parse_hyperboloid.c \
				$(SRC_DIR)/xml_parser/parse_torus.c \
				$(SRC_DIR)/xml_parser/parse_triangle.c \
				$(SRC_DIR)/xml_parser/parse_cube.c \
				$(SRC_DIR)/xml_parser/parse_h_cube.c \
				$(SRC_DIR)/xml_parser/parse_init_pos.c \
				$(SRC_DIR)/xml_parser/parse_init_color.c \
				$(SRC_DIR)/xml_parser/parse_material.c \
				$(SRC_DIR)/xml_parser/parser_utils.c \
				$(SRC_DIR)/xml_parser/error_msg.c \
				\
				$(SRC_DIR)/xml_saver/ft_itoa_double.c \
				$(SRC_DIR)/xml_saver/xml_saver.c \
				$(SRC_DIR)/xml_saver/xml_saver_func.c \
				$(SRC_DIR)/xml_saver/xml_save_objects.c \
				$(SRC_DIR)/xml_saver/xml_save_objects_2.c \
				$(SRC_DIR)/xml_saver/xml_save_objects_3.c \
				\
				$(SRC_DIR)/get_next_line/get_next_line.c \
				\
				$(SRC_DIR)/malloc/malloc_objects.c \
				$(SRC_DIR)/malloc/malloc_objects1.c \
				$(SRC_DIR)/malloc/malloc_objects_bonus.c \
				$(SRC_DIR)/malloc/malloc_objects_bonus2.c \
				\
				$(SRC_DIR)/threads/free_object_thread.c \
				$(SRC_DIR)/threads/free_object_thread2.c \
				$(SRC_DIR)/threads/free_object_thread3.c \
				\
				$(SRC_DIR)/server/master.c \
				$(SRC_DIR)/server/master_send_infos.c \
				$(SRC_DIR)/server/master_buff_infos.c \
				$(SRC_DIR)/server/master_buff_infos_next.c \
				$(SRC_DIR)/server/master_dup_data.c \
				$(SRC_DIR)/server/master_utils.c \
				$(SRC_DIR)/server/client.c \
				$(SRC_DIR)/server/data_grow.c \
				$(SRC_DIR)/server/client_recev_infos.c \
				$(SRC_DIR)/server/client_recev_infos_next.c \
				$(SRC_DIR)/server/client_utils.c \

###################################################
##--- Use Patsubst to find .o from .c         ---##
###################################################

OBJ		 = $(patsubst srcs/%.c, obj/%.o, $(SRC))
.SILENT:
OBJ_NUK	 = $(patsubst frameworks/%.c, objnuklear/%.o, $(SRC_NUK))
.SILENT:
OBJ_CUDA = $(patsubst srcs/%.cu, objcuda/%.o, $(SRC_CUDA))
.SILENT:

###################################################
##--- Compilation Running                     ---##
###################################################

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_CUDA) $(OBJ_NUK)
	printf '\033[K\033[32m[✔] %s\n\033[0m' "--Compiling Sources--------"
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Cuda Sources--------"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Libft Library--------"
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Interface--------"
	if [ ! -d bin ]; then mkdir -p bin; fi
	@nvcc -g -o bin/$(NAME) $(OBJ) $(OBJ_CUDA) $(OBJ_NUK) $(LIBFT) $(XML_FLAGS) -Xlinker -framework,SDL2 -Xlinker -framework,OpenGL -Xlinker -framework,Cocoa -Xlinker -framework,IOKit -Xlinker -framework,CoreVideo -Xlinker $(GLEW) -Xlinker $(GLFW3)
	printf '\033[1;7m'
	printf '\033[33m[✔] %s\n\033[0m' "--DONE--------"

###################################################
##--- Create repertories for objects .c to .c ---##
###################################################

obj/%.o: srcs/%.c
	if [ ! -d obj ]; then mkdir -p obj; fi
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CC_FLAGS) -c $(INCLUDE) $(INCLUDECUDA) $(INCLUDEXML) $(INCLUDENK) $< -o $@
	printf '\033[K\033[0m[✔] %s\n\033[0m\033[1A' "$<"

objnuklear/%.o: frameworks/%.c
	if [ ! -d objnuklear ]; then mkdir -p objnuklear; fi
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CC_FLAGS) -c $(INCLUDE) $(INCLUDECUDA) $(INCLUDEXML) $(INCLUDENK) $< -o $@
	printf '\033[K\033[0m[✔] %s\n\033[0m\033[1A' "$<"

objcuda/%.o: srcs/%.cu
	if [ ! -d objcuda ]; then mkdir -p objcuda; fi
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	#printf '\033[31m[✔] %s\n\033[0m' "--Set up Env Clang 7.3.0--------"
	nvcc -g -c -dc -Wno-deprecated-gpu-targets $(INCLUDECUDA) $(INCLUDE) $(INCLUDEXML) $(INCLUDENK) $< -o $@
	printf '\033[K\033[0m[✔] %s\n\033[0m\033[1A' "$<"

###################################################
##--- Clean only objects .o                      ##
###################################################

clean:
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Library--------"
	@$(MAKE) $(MAKE_FLAGS) fclean -C $(LIBFT_DIR)
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Output Files--------"
	@$(RM) $(OBJ) $(OBJ_CUDA) $(OBJ_NUK)

###################################################
##--- Clean ALl                                  ##
###################################################

fclean: clean
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Executable and All Object--------"
	@$(RM) $(NAME)
	@$(RF) obj objcuda objnuklear bin screenshots

re: fclean all

clearall : fclean
	rm -rf LibraryTmp