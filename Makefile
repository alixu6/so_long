# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 13:24:10 by axu               #+#    #+#              #
#    Updated: 2024/06/21 17:19:52 by axu              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SOURCES = so_long.c map_checks.c map_moves.c map_utils.c get_next_line.c 

OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

MINILIBX_PATH = ./minilibx-linux

MINILIBX = $(MINILIBX_PATH)/libmlx.a

LIBFT_PATH = ./ft_printf

LIBFT = $(LIBFT_PATH)/libftprintf.a

INCLUDES = -I$(MINILIBX_PATH)

MINILIBX_FLAGS = -lm -lX11 -lXext

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
