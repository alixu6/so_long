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

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_map_size(const char *filename, t_point *size)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nEmpty map\n");
		exit(0);
	}
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

void	ft_map_lines(char **map, int fd, int size_y)
{
	char	*line;
	int		row;

	row = 0;
	line = get_next_line(fd);
	while (line != NULL && row < size_y)
	{
		map[row] = line;
		line = get_next_line(fd);
		row++;
	}
	map[row] = NULL;
	close(fd);
	if (line)
		free(line);
}

char	**ft_read_map(const char *filename, t_point *size)
{
	int		fd;
	char	**map;

	ft_map_size(filename, size);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (size->y + 1));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	ft_map_lines(map, fd, size->y);
	return (map);
}

t_point	ft_find_player_pos(char **map, t_point size)
{
	t_point	player_pos;
	int		y;
	int		x;

	player_pos.x = 0;
	player_pos.y = 0;
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
	return (player_pos);
}
