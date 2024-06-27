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

void	ft_map_size(const char *filename, t_point *size)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	size->y = 0;
	size->x = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (size->x == 0)
			size->x = ft_strlen(line);
		size->y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_point	ft_find_player_pos(char **map, t_point size)
{
	t_point	player_pos;
	int		y;
	int		x;

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
