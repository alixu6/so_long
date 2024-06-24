/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:51:18 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 17:43:31 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
/*# include <X11/keysim.h>*/
# include "minilibx-linux/mlx.h"
# include "ft_printf/libftprintf.h"

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct	s_map
{
	char	**map;
	t_point	size;
	t_point	player;
	int	nb;
	int	goal;
	int	valid;
}	t_map;

typedef struct	s_game
{
	void	*mlx_ptr;
	void	*wdw_ptr;
	char	**map;
	int	map_cols;
	int	map_rows;
	void	*img_wall;
	void	*img_empty;
	void	*img_collectible;
	int	img_width;
	int	img_height;
}	t_game;

/*t_point	ft_get_map_size(const char *map_file);*/

int	ft_count_player(char **map, t_point size);
int	ft_count_exit(char **map, t_point size);
int	ft_rectangular(char **map, t_point size);
int	ft_row_walls(char **map, t_point size);
int	ft_column_walls(char **map, t_point size);

char	*get_next_line(int fd);

char	**ft_read_map(const char *filename, t_point *size);

t_point	ft_find_player_pos(char **map, t_point size);

/*char	**ft_make_map(char **area, t_point size);*/
void	ft_flood(t_map *params, t_point pos);
int	ft_check_path(t_map *params);
int	ft_check_map(t_map *params);

void	ft_init_struct(t_map *params, char **area, t_point size);

int     on_destroy(t_game *game);
int on_keypress(int keysym, t_game *game);
void render_map(t_game *game);


#endif
