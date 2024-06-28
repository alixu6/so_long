# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 13:24:10 by axu               #+#    #+#              #
#    Updated: 2024/06/28 10:29:31 by axu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SOURCES = so_long.c get_next_line.c map_utils.c  map_checks.c map_moves.c \
	  mlx_utils.c moves.c render.c destroy.c \

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I$(MINILIBX_PATH) -I$(LIBFT_PATH)

MINILIBX_PATH = ./minilibx-linux
MINILIBX = $(MINILIBX_PATH)/libmlx.a

LIBFT_PATH = ./ft_printf
LIBFT = $(LIBFT_PATH)/libftprintf.a

MINILIBX_FLAGS = -L$(MINILIBX_PATH) -lmlx_Linux -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBFT) $(MINILIBX) $(MINILIBX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_PATH)

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MINILIBX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(MINILIBX_PATH) clean

re: fclean all
