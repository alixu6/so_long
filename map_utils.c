/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:50:42 by axu               #+#    #+#             */
/*   Updated: 2024/06/25 18:18:14 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"
#include <stdlib.h>

/*void	ft_push_map(t_map **map, int x, int y)
{
	t_map	*new_point;

	new_point = (t_map *)malloc(sizeof(t_map));
	new_point->x = x;
	new_point->y = y;
	new_point->next = *map;
	*map = new_point;
}

int	ft_pop_map(t_map **map, int *x, int *y)
{
	t_map	*temp;
	
	if (*map == NULL)
		return (0);
	temp = *map;
	*x = temp->x;
	*y = temp->y;
	*map = (*map)->next;
	free(temp);
	return (1);
}*/

void	ft_map_size(const char *filename, t_point *size)
{
	int	fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	size->y = 0;
	size->x = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (size->x == 0)
			size->x = ft_strlen(line);
		size->y++;
		free(line);
	}
	close(fd);
}	

t_point	ft_find_player_pos(char **map, t_point size)
{
	t_point	player_pos;
	int	y;
	int	x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (map[y][x] == 'P')
			{
				player_pos.x = x;
				player_pos.y = y;
				return (player_pos);
			}
			x++;
		}
		y++;
	}
	player_pos.x = -1;
	player_pos.y = -1;
	return (player_pos);
}

void	ft_create_window(t_game	*game)
{
	game->w = game->render.size.x * CELL_SIZE;
	game->h = game->render.size.y * CELL_SIZE;
	ft_printf("game render size x is %d\n", game->render.size.x);
	ft_printf("game w is %d\n", game->w);
	ft_printf("game render size y is %d\n", game->render.size.y);
	ft_printf("game h is %d\n", game->h);
	game->win = mlx_new_window(game->mlx, game->w, game->h, "GAME");
        if (!game->win)
	{
		free(game->mlx);
		return ;
	}
	ft_render_map(game);
}


