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

SOURCES = ./sources/so_long.c get_next_line.c ./sources/map_utils.c  ./sources/map_checks.c ./sources/map_path.c \
	  ./sources/mlx_utils.c ./sources/moves.c ./sources/render.c ./sources/destroy.c \

BONUS_SOURCES = ./bonus/so_long_bonus.c get_next_line.c ./bonus/map_utils_bonus.c  ./bonus/map_checks_bonus.c ./bonus/map_path_bonus.c \
	  ./bonus/mlx_utils_bonus.c ./bonus/moves_bonus.c ./bonus/render_bonus.c ./bonus/enemy_bonus.c ./bonus/destroy_bonus.c \

OBJECTS = $(SOURCES:.c=.o)

BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I$(MINILIBX_PATH) -I$(LIBFT_PATH)

MINILIBX_PATH = ./minilibx-linux
MINILIBX = $(MINILIBX_PATH)/libmlx.a

LIBFT_PATH = ./ft_printf
LIBFT = $(LIBFT_PATH)/libftprintf.a

MINILIBX_FLAGS = -L$(MINILIBX_PATH) -lmlx -L/usr/lib/X11 -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBFT) $(MINILIBX) $(MINILIBX_FLAGS)

bonus: $(LIBFT) $(MINILIBX) $(BONUS_OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJECTS) $(LIBFT) $(MINILIBX) $(MINILIBX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(MINILIBX):
	$(MAKE) -C $(MINILIBX_PATH)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MINILIBX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(MINILIBX_PATH) clean

re: fclean all
