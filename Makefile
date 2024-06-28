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
	  mlx_utils.c destroy.c render.c \

OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

MINILIBX_PATH = ./minilibx-linux

MINILIBX = $(MINILIBX_PATH)/libmlx.a $(MINILIBX_PATH)/libmlx_Linux.a

LIBFT_PATH = ./ft_printf

LIBFT = $(LIBFT_PATH)/libftprintf.a

INCLUDES = -I$(MINILIBX_PATH)

MINILIBX_FLAGS = -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBFT) $(MINILIBX) $(MINILIBX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_PATH)

clean:
	rm -f $(OBJECTS)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MINILIBX_PATH) clean

fclean: clean
	rm -f $(NAME)
	@$(NAME) -C $(LIBFT_PATH) fclean
	@$(NAME) -C $(MINILIBX_PATH) fclean

re: fclean all
