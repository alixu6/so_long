/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:05 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 19:28:15 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

char **ft_read_map(const char *filename, t_point *size) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return NULL;
    }

    char *line;
    char **map = NULL;
	int rows = 0;
    int cols = 0;

    while ((line = get_next_line(fd)) != NULL) {

        if (cols == 0)
            cols = ft_strlen(line); // Set the column count for the first line
	
        map = realloc(map, sizeof(char *) * (rows + 1));
        map[rows] = line; // Store the line in the map array
        rows++;
    }
    close(fd);
    size->y = rows;
    size->x = cols;
return (map);
}

/*char **ft_read_map(const char *filename, t_point *size) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return NULL;
    }

    char *line;
    char **map = NULL;
    int rows = 0;
    int max_cols = 0; // Track maximum line length excluding newline

    while ((line = get_next_line(fd)) != NULL) {
        int cols = 0;

        // Calculate actual length of the line (excluding newline)
        while (line[cols] != '\0' && line[cols] != '\n') {
            cols++;
        }

        // Update max_cols if necessary
        if (cols > max_cols) {
            max_cols = cols;
        }

        // Store the line in the map array
        map = realloc(map, sizeof(char *) * (rows + 1));
        map[rows] = line;
        rows++;
    }
    close(fd);

    // Assign size excluding newlines and null terminators
    size->y = rows;
    size->x = max_cols;

    return map;
}*/

char	**ft_make_map(char **area, t_point size)
{
	char	**map;
	int	i;
	int	j;

	map = (char **)malloc(sizeof(char *) * size.y);
	if (!map)
		return (NULL);
	i = 0;
	while (i < size.y)
	{
		map[i] = (char *)malloc(sizeof(char) * (size.x + 1));
		if (!map[i])
			return (NULL);
		j = 0;
		while (j < size.x)
		{
			map[i][j] = area[i][j];
			j++;
		}
		map[i][size.x] = '\0';
		i++;
	}
	return (map);
}

void	ft_flood(t_map *params, t_point pos)
{
	char	original;
	if (pos.x < 0 || pos.x >= params->size.x)
		return ;
	if (pos.y < 0 || pos.y >= params->size.y)
		return ;
	ft_printf("entering flood\n");
	if (params->map[pos.y][pos.x] == '1' || params->map[pos.y][pos.x] == 'X')
		return ;
	original = params->map[pos.y][pos.x];
	if (original == 'C')
		params->nb++;
	else if (original == 'E')
	{
		if (params->nb == params->goal)
			params->valid = 1;
		return ;
	}
	params->map[pos.y][pos.x] = 'X';
	ft_flood(params, (t_point){pos.x + 1, pos.y});
	ft_flood(params, (t_point){pos.x - 1, pos.y});
	ft_flood(params, (t_point){pos.x, pos.y + 1});
	ft_flood(params, (t_point){pos.x, pos.y - 1});
	params->map[pos.y][pos.x] = original;
}

int	ft_check_path(t_map *params)
{
	int	i;
	int	j;

	i = 0;
	while (i < params->size.y)
	{
		ft_printf("entering the loop in check_path\n");
		j = 0;
		while (j < params->size.x)
		{
			if (params->map[i][j] == 'C')
				params->goal++;
			j++;
		}
		i++;
	}
	ft_printf("params->goal is %d\n", params->goal);
	if (params->goal < 1)
		return (0);
	ft_flood(params, params->player);
	ft_printf("params->valid is %d\n", params->valid);
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
		return (1);
	}
	return (1);
}
