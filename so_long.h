/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:51:18 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 11:22:15 by axu              ###   ########.fr       */
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

typedef struct	s_map
{
	int	x;
	int	y;
	struct	s_map *next;
}	t_map;

typedef struct	s_check_map
{
	char	**map;
	t_map	size;
	t_map	player;
	int	*nb;
	int	goal;
	int	*valid;
}	t_check_map;

int	ft_count_player(char **map, t_map size);
int	ft_count_exit(char **map, t_map size);
int	ft_rectangular(char **map, t_map size);
int	ft_row_walls(char **map, t_map size);
int	ft_column_walls(char **map, t_map size);
char	**ft_make_map(char **area, t_map size);
void	ft_flood(char **map, t_map size, t_map player, int *nb, int goal, int *valid);
int	ft_check_path(char **map, t_map size, t_map player);
int	ft_check_map(char **map, t_map size);

#endif
