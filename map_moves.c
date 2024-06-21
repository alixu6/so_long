/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:05 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 14:52:21 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_init_struct(t_map *params, char **area, t_point size, t_point player)
{
	params->map = area;
	params->size = size;
	params->player = player;
	params->nb = 0;
	params->goal = 0;
	params->valid = 0;
}

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
	params->map[pos.y][pos.x] = 'x';
}

int	ft_check_path(t_map *params)
{
	int	i;
	int	j;

	i = 0;
	params->goal = 0;
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
		printf("map not surrounding by walls\n");
		return (0);
	}
	if (!ft_column_walls(params->map, params->size))
	{
		printf("map not surrouding by walls\n");
		return (0);
	}
	return (1);
}

int main() {

	t_map	params;

    char *area[] = {
        "1111111",
        "1C000P1",
        "100E01",
        "1111111"
    };

    t_point size = {7, 4};
    t_point player = {5, 1};

    char **map = ft_make_map(area, size);
    ft_init_struct(&params, map, size, player);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	
	if (ft_check_map(&params))
	{
		int is_valid_path = ft_check_path(&params);
		if (is_valid_path) {
        		printf("Path is valid and all coins collected!\n");
    		} else {
        		printf("Path is invalid or not all coins collected.\n");
   		 }
	}
	else
		printf("Error\n");


    // Free allocated memory
    int i = 0;
    while (i < size.y) {
        free(map[i]);
        i++;
    }
    free(map);

    return 0;
}
