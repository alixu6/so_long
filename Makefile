
NAME = so_long

SOURCES = map_utils.c

OBJECTS = $(SOURCES:.C=.O)

CC = cc

CFLAGS = -Wall -Werror -Wextra

MINILIBX_PATH = ./minilibx-linux

MINILIBX = $(MINILIBX_PATH)/libmlx.a

LIBFT_PATH = ./ft_printf

LIBFT = $(LIBFT_PATH)/libftprintf.a

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(MINILIBX)

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
	$(NAME) -C $(LIBFT_PATH) fclean
	$(NAME) -C $(MINILIBX_PATH) fclean

re: fclean all
