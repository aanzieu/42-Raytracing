# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/16 11:32:29 by aanzieu           #+#    #+#              #
#    Updated: 2017/06/23 09:44:56 by aanzieu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

MAKE = make 
MAKE_FLAGS = --no-print-directory

INCLUDE = -I includes -I libft
INCLUDECUDA = -I srcs/cuda/cudaheader

SRC_DIR = srcs
SRC_CUDA_DIR = srcs/cuda/cudasrc

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SDL_FLAGS = `sdl-config --cflags --libs`

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

RM = rm -f
RF = rm -rf

###################################################
##--- LIST of Sources                         ---##
###################################################

SRC_CUDA =		$(SRC_CUDA_DIR)/gpu_rtv1.cu \
				$(SRC_CUDA_DIR)/ray_tracer.cu \
				\
				$(SRC_CUDA_DIR)/libmath/vectors/vectors.cu \
				$(SRC_CUDA_DIR)/libmath/vectors/vectors2.cu \
				$(SRC_CUDA_DIR)/libmath/vectors/translation.cu \
				$(SRC_CUDA_DIR)/libmath/vectors/rotation.cu \
				\
				$(SRC_CUDA_DIR)/libmath/conversion/angles.cu \
				\
				$(SRC_CUDA_DIR)/libmath/equation/equation_resolve.cu \
				$(SRC_CUDA_DIR)/objects/sphere.cu \
				$(SRC_CUDA_DIR)/objects/plane.cu \
				$(SRC_CUDA_DIR)/objects/cylinder.cu \
				$(SRC_CUDA_DIR)/objects/paraboloid.cu \
				$(SRC_CUDA_DIR)/objects/cone.cu \
				\
				$(SRC_CUDA_DIR)/shading/shading.cu \
				\
				$(SRC_CUDA_DIR)/camera/camera.cu \
				\
				$(SRC_CUDA_DIR)/colors/colors.cu \


SRC =			$(SRC_DIR)/main.c \
				$(SRC_DIR)/free_memory.c \
				$(SRC_DIR)/render.c \
				$(SRC_DIR)/display_functions.c \
				\
				$(SRC_DIR)/threads/malloc_objects_cpy.c \
				\
				$(SRC_DIR)/effects/effects_options.c \
				$(SRC_DIR)/effects/effect_bayer.c \
				$(SRC_DIR)/effects/effect_black_and_white.c \
				$(SRC_DIR)/effects/effect_cartoon.c \
				$(SRC_DIR)/effects/effect_eight_bits.c \
				$(SRC_DIR)/effects/effect_negative.c \
				$(SRC_DIR)/effects/effect_sepia.c \
				$(SRC_DIR)/effects/effect_pastel.c \
				\
				$(SRC_DIR)/loader/load_cones.c \
				$(SRC_DIR)/loader/load_paraboloids.c \
				$(SRC_DIR)/loader/load_spheres.c \
				$(SRC_DIR)/loader/load_cylinders.c \
				$(SRC_DIR)/loader/load_planes.c \
				$(SRC_DIR)/loader/load_lights.c \
				\
				$(SRC_DIR)/events/event_handler.c \
				$(SRC_DIR)/events/key_press_handler.c \
				$(SRC_DIR)/events/key_release_handler.c \
				$(SRC_DIR)/events/mouse_handler.c \
				\
				$(SRC_DIR)/parser/parse_add.c \
				$(SRC_DIR)/parser/parse_add_bonus.c \
				$(SRC_DIR)/parser/parse_camera.c \
				$(SRC_DIR)/parser/parse_cones.c \
				$(SRC_DIR)/parser/parse_cylinders.c \
				$(SRC_DIR)/parser/parse_infos.c \
				$(SRC_DIR)/parser/parse_infos_2.c \
				$(SRC_DIR)/parser/parse_lights.c \
				$(SRC_DIR)/parser/parse_paraboloids.c \
				$(SRC_DIR)/parser/parse_planes.c \
				$(SRC_DIR)/parser/parse_spheres.c \
				$(SRC_DIR)/parser/parser.c \
				\
				$(SRC_DIR)/get_next_line/get_next_line.c \
				\
				$(SRC_DIR)/malloc/malloc_objects.c \
				$(SRC_DIR)/malloc/malloc_objects_bonus.c \

###################################################
##--- Use Patsubst to find .o from .c         ---##
###################################################

OBJ		= $(patsubst srcs/%.c, obj/%.o, $(SRC))
.SILENT:
OBJ_CUDA = $(patsubst srcs/%.cu, objcuda/%.o, $(SRC_CUDA))
.SILENT:

###################################################
##--- Compilation Running                     ---##
###################################################

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_CUDA)
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Sources--------"
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Cuda Sources--------"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Libft Library--------"
	if [ ! -d bin ]; then mkdir -p bin; fi
	@nvcc -o bin/$(NAME) $(OBJ) $(OBJ_CUDA) $(LIBFT) -Xlinker -framework,SDL2 \
	-gencode arch=compute_30,code=compute_30 \
    -gencode arch=compute_35,code=compute_35
	printf '\033[1;7m'
	printf '\033[33m[✔] %s\n\033[0m' "--DONE--------"

###################################################
##--- Create repertories for objects .c to .c ---##
###################################################

obj/%.o: srcs/%.c
	if [ ! -d obj ]; then mkdir -p obj; fi
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CC_FLAGS) -c $(INCLUDE) $(INCLUDECUDA) $< -o $@
	printf '\033[0m[✔] %s\n\033[0m' "$<"

objcuda/%.o: srcs/%.cu
	if [ ! -d objcuda ]; then mkdir -p objcuda; fi
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	nvcc -c -dc -Wno-deprecated-gpu-targets $(INCLUDECUDA) $(INCLUDE) $< -o $@ 
	printf '\033[0m[✔] %s\n\033[0m' "$<"

###################################################
##--- Clean only objects .o                      ##
###################################################

clean:
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Library--------"
	@$(MAKE) $(MAKE_FLAGS) fclean -C $(LIBFT_DIR)
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Output Files--------"
	@$(RM) $(OBJ) $(OBJ_CUDA)

###################################################
##--- Clean ALl                                  ##
###################################################

fclean: clean
	printf '\033[1;7m'
	printf '\033[31m[✔] %s\n\033[0m' "--Cleaning Executable and All Object--------"
	@$(RM) $(NAME)
	@$(RF) obj objcuda bin

re: fclean all

run: $(NAME)
	./bin/rtv1 ./testfiles/basic.xml

runforever:
	nodemon -e c,h --watch . --exec make run > /tmp/lala

.PHONY: clean fclean re all run runforever
