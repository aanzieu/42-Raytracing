# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilau <svilau@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/03 15:43:25 by svilau            #+#    #+#              #
#    Updated: 2016/09/30 10:48:13 by svilau           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ./ft_memset.c ./ft_bzero.c ./ft_memcpy.c ./ft_memccpy.c ./ft_memmove.c ./ft_memchr.c ./ft_memcmp.c ./ft_strlen.c ./ft_strdup.c ./ft_strcpy.c ./ft_strncpy.c ./ft_strcat.c ./ft_strncat.c ./ft_strlcat.c ./ft_strchr.c ./ft_strrchr.c ./ft_strstr.c ./ft_strnstr.c ./ft_strcmp.c ./ft_strncmp.c ./ft_atoi.c ./ft_isalpha.c ./ft_isdigit.c ./ft_isalnum.c ./ft_isascii.c ./ft_isprint.c ./ft_toupper.c ./ft_tolower.c ./ft_memalloc.c ./ft_memdel.c ./ft_strnew.c ./ft_strdel.c ./ft_strclr.c ./ft_striter.c ./ft_striteri.c ./ft_strmap.c ./ft_strmapi.c ./ft_strequ.c ./ft_strnequ.c ./ft_strsub.c ./ft_strjoin.c ./ft_strtrim.c ./ft_strsplit.c ./ft_itoa.c ./ft_putchar.c ./ft_putstr.c ./ft_putendl.c ./ft_putnbr.c ./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c ./ft_strtolower.c ./ft_cleanup_str.c ./ft_lstnew.c ./ft_lst_add_back.c ./ft_atoi_double.c ./ft_count_word.c ./ft_swap_str.c ./ft_swap_double.c ft_printf/check_conv.c ft_printf/handler_hexa.c ft_printf/handler_int.c ft_printf/handler_char_str.c ft_printf/handler_long.c ft_printf/handler_octal.c ft_printf/handler_w_str.c ft_printf/handler_wchar.c ft_printf/init_env.c ft_printf/ft_printf.c ft_printf/parse_buffer.c ft_printf/put_precision_padding.c ft_printf/parse_handler.c ft_printf/misc.c

O_FILES = ./ft_memset.o ./ft_bzero.o ./ft_memcpy.o ./ft_memccpy.o ./ft_memmove.o ./ft_memchr.o ./ft_memcmp.o ./ft_strlen.o ./ft_strdup.o ./ft_strcpy.o ./ft_strncpy.o ./ft_strcat.o ./ft_strncat.o ./ft_strlcat.o ./ft_strchr.o ./ft_strrchr.o ./ft_strstr.o ./ft_strnstr.o ./ft_strcmp.o ./ft_strncmp.o ./ft_atoi.o ./ft_isalpha.o ./ft_isdigit.o ./ft_isalnum.o ./ft_isascii.o ./ft_isprint.o ./ft_toupper.o ./ft_tolower.o ./ft_memalloc.o ./ft_memdel.o ./ft_strnew.o ./ft_strdel.o ./ft_strclr.o ./ft_striter.o ./ft_striteri.o ./ft_strmap.o ./ft_strmapi.o ./ft_strequ.o ./ft_strnequ.o ./ft_strsub.o ./ft_strjoin.o ./ft_strtrim.o ./ft_strsplit.o ./ft_itoa.o ./ft_putchar.o ./ft_putstr.o ./ft_putendl.o ./ft_putnbr.o ./ft_putchar_fd.o ./ft_putstr_fd.o ./ft_putendl_fd.o ./ft_putnbr_fd.o ./ft_strtolower.o ./ft_cleanup_str.o ./ft_lstnew.o ./ft_lst_add_back.o ./ft_atoi_double.o ./ft_count_word.o ./ft_swap_str.o ./ft_swap_double.o check_conv.o handler_hexa.o handler_int.o handler_char_str.o handler_long.o handler_octal.o handler_w_str.o handler_wchar.o init_env.o ft_printf.o parse_buffer.o put_precision_padding.o parse_handler.o misc.o

HEADERS = ./libft.h ./ft_printf.h

COMPILE = gcc

ARCHIVE = ar rc

FLAGS = -Wall -Werror -Wextra

O_FLAG = -c

OBJS_PRINTF = $(SRCS_PRINTF:.c=.o)

all: $(NAME)

$(NAME):

	@ $(COMPILE) $(FLAGS) -I./ $(O_FLAG) $(SRC) ##$(SRCS_PRINTF)

	@$(ARCHIVE) $(NAME) $(O_FILES) $(HEADERS)

clean:
	@ /bin/rm -f $(O_FILES) $(OBJS_PRINTF)

fclean: clean
	@ /bin/rm -f $(NAME)

re: fclean all
