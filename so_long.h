/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:51:18 by axu               #+#    #+#             */
/*   Updated: 2024/06/27 19:46:33 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef CELL_SIZE
#  define CELL_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"
# include "ft_printf/libftprintf.h"

# define OUT_IMG "./textures/wall1.xpm"
# define WALL_IMG "./textures/wall.xpm"
# define SPACE_IMG "./textures/space.xpm"
# define ITEM_IMG "./textures/item.xpm"
# define PLAYER_IMG "./textures/player.xpm"
# define PLAYER_IMG1 "./textures/player1.xpm"
# define PLAYER_IMG2 "./textures/player2.xpm"
# define PLAYER_IMG3 "./textures/player3.xpm"
# define PLAYER_IMG4 "./textures/player4.xpm"
# define PLAYER_IMG5 "./textures/player5.xpm"
# define PLAYER_IMG6 "./textures/player6.xpm"
# define EXIT_START_IMG "./textures/exit_closed.xpm"
# define EXIT_END_IMG "./textures/exit_open.xpm"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**map;
	t_point	size;
	t_point	player;
	int		nb;
	int		goal;
	int		valid;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	render;
	void	*out;
	void	*wall;
	void	*space;
	void	*item;
	void	*player[7];
	void	*exit;
	void	*exit_open;
	int		count;
	int		w;
	int		h;
	int		player_frame;
	int		move;
}	t_game;

int		ft_count_player(char **map, t_point size);
int		ft_count_exit(char **map, t_point size);
int		ft_rectangular(char **map, t_point size);
int		ft_row_walls(char **map, t_point size);
int		ft_column_walls(char **map, t_point size);

char	*get_next_line(int fd);

void	ft_map_size(const char *filename, t_point *size);
char	**ft_read_map(const char *filename, t_point *size);

t_point	ft_find_player_pos(char **map, t_point size);

void	ft_create_window(t_game *game);

void	ft_flood(t_map *params, t_point pos);
int		ft_check_path(t_map *params);
int		ft_check_map(t_map *params);

void	ft_init_struct(t_game *game, char **area, t_point size);

void	ft_convert_to_img(t_game *game);

int     on_destroy(t_game *game);
int		on_keypress(int keysym, t_game *game);

void	ft_render_outline(t_game *game, int x, int y);
void	ft_render_wall(t_game *game, int x, int y);
void	ft_render_space(t_game *game, int x, int y);
void	ft_render_item(t_game *game, int x, int y);
void	ft_render_player(t_game *game, int x, int y);
void	ft_render_exit(t_game *game, int x, int y);

void	ft_render_map(t_game *game);

void	ft_player_frame(t_game *game, int x, int y);

void	print_map(char **map, int size_x, int size_y);

#endif
