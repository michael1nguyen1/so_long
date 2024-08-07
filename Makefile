# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 15:46:54 by linhnguy          #+#    #+#              #
#    Updated: 2024/06/27 13:03:39 by linhnguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
LIBMLX = MLX42
HEADERS	= -I $(LIBMLX)/include -I ./include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
LIBFT = libft.a
LIBFTDIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_CFLAGS = -fsanitize=address -g3
SRCS =	./src/so_long.c ./src/images.c ./src/check_map.c ./src/check_map_utils.c	\
		 ./src/check_map_utils2.c ./src/game_movement.c ./src/end_game.c			\
		 ./src/error_handling.c ./src/image_utils.c ./src/str_utils.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: libmlx $(NAME)

$(NAME):$(OBJS)
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) $(LIBFTDIR)/$(LIBFT) -o $(NAME)
	@echo "Program Made"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4;

debug: re
	$(CC) $(OBJS) $(LIBS) $(HEADERS) $(DEBUG_CFLAGS) $(LIBFTDIR)/$(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)"

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFTDIR) clean
	@rm -rf MLX42/build
	@echo "Cleaned object files"

fclean: clean
	$(RM) $(NAME)
	rm -rf $(LIBMLX)/build/libmlx42.a
	@make -C $(LIBFTDIR) fclean
	@echo "Fully Cleaned"

re: fclean all

.PHONY: all, clean, fclean, re, libmlx, debug
