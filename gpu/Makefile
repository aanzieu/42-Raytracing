NAME = rtv1

MAKE = make 
MAKE_FLAGS = --no-print-directory

SRC_DIR = srcs
SRC_CUDA_DIR = srcs/cuda/cudasrc

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SDL_FLAGS = `sdl-config --cflags --libs`

CC = gcc
CC_FLAGS = -Wall -Werror -Wextra

SRC_CUDA =	$(SRC_CUDA_DIR)/gpu_rtv1.cu \
			$(SRC_CUDA_DIR)/ray_tracer.cu \
			\
			$(SRC_CUDA_DIR)/libmath/vectors/vectors.cu \
			$(SRC_CUDA_DIR)/libmath/vectors/vectors2.cu \
			$(SRC_CUDA_DIR)/libmath/vectors/translation.cu \
			$(SRC_CUDA_DIR)/libmath/vectors/rotation.cu \
			\
			$(SRC_CUDA_DIR)/objects/sphere.cu \
			$(SRC_CUDA_DIR)/objects/plane.cu \
			$(SRC_CUDA_DIR)/objects/cylinder.cu \
			$(SRC_CUDA_DIR)/objects/cone.cu \
			\
			$(SRC_CUDA_DIR)/shading/shading.cu \
			\
			$(SRC_CUDA_DIR)/libmath/conversion/angles.cu \
			\
			$(SRC_CUDA_DIR)/camera/camera.cu \
			\
			$(SRC_CUDA_DIR)/colors/colors.cu \

SRC =	$(SRC_DIR)/main.c \
		\
		$(SRC_DIR)/events/event_handler.c \
		$(SRC_DIR)/events/key_press_handler.c \
		$(SRC_DIR)/events/key_release_handler.c \
		$(SRC_DIR)/events/mouse_handler.c \
		\
		$(SRC_DIR)/free_memory.c \
		$(SRC_DIR)/render.c \
		\
		$(SRC_DIR)/parser/parser.c \
		$(SRC_DIR)/parser/parse_camera.c \
		$(SRC_DIR)/parser/parse_cones.c \
		$(SRC_DIR)/parser/parse_cylinders.c \
		$(SRC_DIR)/parser/parse_lights.c \
		$(SRC_DIR)/parser/parse_planes.c \
		$(SRC_DIR)/parser/parse_spheres.c \
		$(SRC_DIR)/parser/parse_add.c \
		$(SRC_DIR)/parser/parse_infos.c \
		$(SRC_DIR)/parser/parse_infos_2.c \
		\
		$(SRC_DIR)/get_next_line/get_next_line.c \
		$(SRC_DIR)/malloc/malloc_objects.c \
		$(SRC_DIR)/display_functions.c \

SOURCES := $(shell find srcs -type f -name '*.c')
OBJ		= $(patsubst srcs/%.c, obj/%.o, $(SOURCES))
.SILENT:

SOURCESCUDA := $(shell find srcs -type f -name '*.cu')
OBJ_CUDA = $(patsubst srcs/%.cu, objcuda/%.o, $(SOURCESCUDA))
.SILENT:


#OBJ_CUDA = 	gpu_rtv1.o \
			ray_tracer.o \
			sphere.o \
			angles.o \
			camera.o \
			rotation.o \
			cylinder.o cone.o \
			plane.o \
			vectors2.o \
			vectors.o \
			colors.o \
			shading.o \
>>>>>>> Stashed changes

#RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_CUDA)
	printf '\033[4m'
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling sources--------"
	printf '\033[4m'
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Cuda sources--------"
	@$(MAKE) $(MAKE_FLAGS) -C $(LIBFT_DIR)
	printf '\033[4m'
	printf '\033[32m[✔] %s\n\033[0m' "--Compiling Libft library--------"
#	@echo "--Compiling cuda-----------"
#	@nvcc -c $(SRC_CUDA) -dc -Wno-deprecated-gpu-targets
	@mkdir -p bin
#	@echo "--Creating executable------"
	@nvcc -o bin/$(NAME) $(OBJ) $(OBJ_CUDA) $(LIBFT) -Xlinker -framework,SDL2 \
	-gencode arch=compute_30,code=compute_30 \
    -gencode arch=compute_35,code=compute_35
	@echo "--Done---------------------"

obj/%.o: srcs/%.c
	@mkdir -p obj
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CC_FLAGS) -c $< -o $@
	printf '\033[0m[✔] %s\n\033[0m' "$<"

objcuda/%.o: srcs/%.cu
	@mkdir -p obj_cuda
	if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	nvcc -c -dc -Wno-deprecated-gpu-targets $< -o $@ 
	printf '\033[0m[✔] %s\n\033[0m' "$<"

clean:
	@echo "--Cleaning libraries-------"
	@$(MAKE) $(MAKE_FLAGS) fclean -C $(LIBFT_DIR)
	@echo "--Cleaning output files----"
	@$(RM) $(OBJ)

fclean: clean
	@echo "--Cleaning executale------"
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./bin/rtv1 ./testfiles/basic.xml

runforever:
	nodemon -e c,h --watch . --exec make run > /tmp/lala
