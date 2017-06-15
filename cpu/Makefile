# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakefileOKDEF                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/07 08:31:30 by aanzieu           #+#    #+#              #
#    Updated: 2017/06/13 14:28:38 by aanzieu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rtv1

FLGS	= -Wall -Wextra -Werror

SRC		= srcs/rtv1.c \
		  srcs/rtv1_draw.c \
		  srcs/rtv1_ray.c \
		  srcs/rtv1_intersection.c \
		  \
		  srcs/utils/rtv1_cpy.c \
		  srcs/utils/rtv1_del.c \
		  srcs/utils/rtv1_image.c \
		  \
		  srcs/hooks/rtv1_hook.c \
		  srcs/hooks/rtv1_keyboard.c \
		  srcs/hooks/rtv1_mouse.c \
		  srcs/hooks/rtv1_mouse_delete.c \
		  \
		  srcs/colors/rtv1_choose_colors.c \
		  srcs/colors/rtv1_calcul_colors.c \
		  \
		  srcs/camera/rtv1_camera.c \
		  \
		  srcs/memory/rtv1_free_thread.c \
		  srcs/memory/rtv1_free_thread_next.c \
		  srcs/memory/rtv1_malloc.c \
		  srcs/memory/rtv1_malloc_scene.c \
		  srcs/memory/rtv1_malloc_object.c \
		  srcs/memory/rtv1_malloc_cpy.c \
		  srcs/memory/rtv1_malloc_cpy_bonus.c \
		  \
		  srcs/parse/rtv1_parse.c \
		  srcs/parse/rtv1_parse_add.c \
		  srcs/parse/rtv1_parse_infos.c \
		  srcs/parse/rtv1_parse_plans.c \
		  srcs/parse/rtv1_parse_lights.c \
		  srcs/parse/rtv1_parse_spheres.c \
		  srcs/parse/rtv1_parse_cones.c \
		  srcs/parse/rtv1_parse_cylinders.c \
		  srcs/parse/rtv1_parse_paraboloid.c \
		  srcs/parse/rtv1_parse_elipsoid.c \
		  \
		  srcs/objects/rtv1_sphere.c \
		  srcs/objects/rtv1_plan.c \
		  srcs/objects/rtv1_cone.c \
		  srcs/objects/rtv1_cylinder.c \
		  srcs/objects/rtv1_paraboloid.c \
		  srcs/objects/rtv1_epsiloid.c \
		  srcs/objects/rtv1_light.c \

OBJ		= $(patsubst src/%.c,obj/%.o,$(SRC))
.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	make -C srcs/libft/ 
	make -C srcs/libmath/ 
	make -C minilibx_macos/ 
	gcc $(FLGS) -o $(NAME) $(SRC) -I ./minilibx_macos/ -lmlx -framework OpenCL -framework OpenGL -framework AppKit -L ./minilibx_macos/ -L ./srcs/libft/ -lft -L ./srcs/libmath/ -lmath -lpthread
	printf '\033[32m[✔] %s\n\033[0m' "RTV1 RDY"

obj/%.o: %.c
	mkdir -p obj
	gcc -Wall -Wextra -Werror -c $< -o $@
	echo '\033[0m[✔] %s\n\033[0m' "$<"

clean:
	/bin/rm -rf obj/
	make -C srcs/libft/ clean
	make -C srcs/libmath/ clean
	make -C minilibx_macos/ clean
	printf '\033[31m[✔] %s\n\033[0m' "Clean RTV1"

fclean: clean
	/bin/rm -f $(NAME)
	make -C srcs/libft/ fclean
	make -C srcs/libmath/ fclean
	printf '\033[31m[✔] %s\n\033[0m' "Fclean RTV1"

re: fclean all

all: $(NAME)
.PHONY: clean fclean re all test
