/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:05 by axu               #+#    #+#             */
/*   Updated: 2024/06/25 17:10:26 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

char	**ft_read_map(const char *filename, t_point *size)
{
	int		fd;
	char	*line;
	char	**map;
	int		row;

	ft_map_size(filename, size);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (size->y + 1));
	if (!map)
		return (NULL);
	row = 0;
	line = get_next_line(fd);
	while (line != NULL && row < size->y)
	{
		map[row] = line;
		line = get_next_line(fd);
		row++;
	}
	map[row] = NULL;
	close(fd);
	if (line)
		free(line);
	return (map);
}

void	ft_flood(t_map *params, t_point pos)
{
	char	original;

	if (pos.x < 0 || pos.x >= params->size.x)
		return ;
	if (pos.y < 0 || pos.y >= params->size.y)
		return ;
	original = params->map[pos.y][pos.x];
	if (original == '1' || original == 'X')
		return ;
	if (original == 'C')
		params->nb++;
	else if (original == 'E')
	{
		if (params->nb == params->goal)
			params->valid = 1;
		return ;
	}
	params->map[pos.y][pos.x] = 'X';
	ft_flood(params, (t_point){pos.x - 1, pos.y});
	ft_flood(params, (t_point){pos.x + 1, pos.y});
	ft_flood(params, (t_point){pos.x, pos.y - 1});
	ft_flood(params, (t_point){pos.x, pos.y + 1});
}

int	ft_check_path(t_map *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->size.y)
	{
		j = 0;
		while (j < params->size.x)
		{
			if (params->map[i][j] == 'C')
				params->goal++;
			j++;
		}
		i++;
	}
	if (params->goal < 1)
		return (0);
	ft_flood(params, params->player);
	return (params->valid);
}

int	ft_check_map(t_map *params)
{
	if (!ft_count_player(params->map, params->size))
	{
		printf("wrong number of players\n");
		return (0);
	}
	if (!ft_count_exit(params->map, params->size))
	{
		printf("wrong number of exits\n");
		return (0);
	}
	if (!ft_rectangular(params->map, params->size))
	{
		printf("map is not rectangular\n");
		return (0);
	}
	if (!ft_row_walls(params->map, params->size))
	{
		printf("map not surrounding by walls 1\n");
		return (0);
	}
	if (!ft_column_walls(params->map, params->size))
	{
		printf("map not surrouding by walls 2\n");
		return (0);
	}
	return (1);
}
