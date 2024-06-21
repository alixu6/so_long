/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:51:18 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 14:49:59 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include "ft_printf/libftprintf.h"

# include <stdio.h>

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*wdw_ptr;
	void	*textures[5];
	/*t_map	*map;*/
}	t_data;

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

int	ft_count_player(char **map, t_point size);
int	ft_count_exit(char **map, t_point size);
int	ft_rectangular(char **map, t_point size);
int	ft_row_walls(char **map, t_point size);
int	ft_column_walls(char **map, t_point size);
void	ft_init_struct(t_map *params, char **area, t_point size, t_point player);
char	**ft_make_map(char **area, t_point size);
void	ft_flood(t_map *params, t_point pos);
int	ft_check_path(t_map *params);
int	ft_check_map(t_map *params);

#endif
