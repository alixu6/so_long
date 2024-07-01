/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
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
# ifndef PIXEL
#  define PIXEL 32
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
# define PLAYER "./textures/player.xpm"
# define PLAYER1 "./textures/player1.xpm"
# define PLAYER2 "./textures/player2.xpm"
# define PLAYER3 "./textures/player3.xpm"
# define PLAYER4 "./textures/player4.xpm"
# define PLAYER5 "./textures/player5.xpm"
# define PLAYER6 "./textures/player6.xpm"
# define ENEMY "./textures/enemy.xpm"
# define ENEMY1 "./textures/enemy1.xpm"
# define ENEMY2 "./textures/enemy2.xpm"
# define ENEMY3 "./textures/enemy3.xpm"
# define ENEMY4 "./textures/enemy4.xpm"
# define ENEMY5 "./textures/enemy5.xpm"
# define ENEMY6 "./textures/enemy6.xpm"
# define EXIT_IMG1 "./textures/exit_closed.xpm"
# define EXIT_IMG2 "./textures/exit_open.xpm"

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
	void	*exit;
	void	*exit_open;
	void	*player[7];
	void	*enemy[7];
	int		count;
	int		w;
	int		h;
	int		player_frame;
	int		enemy_frame;
	int		enemy_counter;
	int		move;
}	t_game;

char	*get_next_line(int fd);

void	ft_free_map(char **map);
void	ft_map_size(const char *filename, t_point *size);
void	ft_map_lines(char **map, int fd, int size_y);
char	**ft_read_map(const char *filename, t_point *size);
t_point	ft_find_player_pos(char **map, t_point size);

void	ft_init_enemy(t_game *game);
void	ft_init_player(t_game * game);
void	ft_init_struct(t_game *game, char **area, t_point size);
void	ft_cannot_read_map(void);

int		ft_count_player(t_map *params);
int		ft_count_exit(t_map *params);
int		ft_rectangular(t_map *params);
int		ft_row_walls(t_map *params);
int		ft_column_walls(t_map *params);
int		ft_valid_char(char c);
int		ft_check_char(t_map *params);
void	ft_flood(t_map *params, t_point pos);
int		ft_check_path(t_map *params);
int		ft_check_map(t_map *params);

void	ft_enemy_img(t_game *game);
void	ft_player_img(t_game *game);
void	ft_convert_to_img(t_game *game);
void	ft_create_window(t_game *game);
void	ft_game_loop(t_game *game);

void	ft_end_game(t_game *game, t_point new_pos);
void	ft_game_moves(t_game *game, t_point new_pos);
int		ft_keys(int keysym, t_game *game);

void	ft_destroy_images(t_game *game);
int		ft_destroy(t_game *game);

void	ft_render_space(t_game *game, int x, int y);
void	ft_render_item(t_game *game, int x, int y);
void	ft_render_player(t_game *game, int x, int y);

void	ft_render_exit(t_game *game, int x, int y);
void	ft_render_map(t_game *game, int x, int y);
void	ft_render_loop(t_game *game);

void	ft_enemy_case(t_game *game, t_point new_pos);
int		ft_enemy_loop(t_game *game);
void	ft_render_enemy(t_game *game, int x, int y);

#endif
