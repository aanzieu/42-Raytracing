# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/04 09:15:59 by aanzieu           #+#    #+#              #
#    Updated: 2017/05/26 10:46:05 by aanzieu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmath.a

SRC = ft_point_and_vector.c \
	   ft_vector_operation.c \
	   ft_vector_properties.c \
	   ft_vector_utils.c \
	   ft_point_utils.c \
	   ft_vector_transformation.c \
	   ft_vector_translation.c \
	   ft_equation_resolve.c \

OBJ = $(SRC:.c=.o)

.SILENT:

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	printf '\033[4m'
	printf '\033[32m[✔] %s\n\033[0m' "Libmath Done"

%.o : %.c
	gcc -Wall -Wextra -Werror -I. -c $<
	printf '\033[0m[✔] %s\n\033[0m' "$<"
	
clean:
	/bin/rm -rf *.o
	printf '\033[31m[✔] %s\n\033[0m' "Clean Libmath"

fclean: clean
	/bin/rm -f $(NAME)
	printf '\033[31m[✔] %s\n\033[0m' "Fclean Libmath"

re: fclean all

all: $(NAME)

.PHONY: clean fclean re all
