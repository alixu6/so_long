/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:05 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 14:05:26 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

char	**ft_make_map(char **area, t_map size)
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

/*int	ft_valid_move(char **map, t_map size, int x, int y)
{
	char	c;

	c = map[y][x];
	if (x < 0 || x >= size.x || y < 0 || y >= size.y)
		return (0);
	if (c == '0' || c == 'C' || c == 'E')
		return (1);
	else
		return (0);
}*/

void	ft_flood(char **map, t_map size, t_map player, int *nb, int goal, int *valid)
{
	char	original;
	if (player.x < 0 || player.x >= size.x)
		return ;
	if (player.y < 0 || player.y >= size.y)
		return ;
	if (map[player.y][player.x] == '1' || map[player.y][player.x] == 'X')
		return ;
	original = map[player.y][player.x];
	if (original == 'C')
		(*nb)++;
	else if (original == 'E')
	{
		if (*nb == goal)
			*valid = 1;
		return ;
	}
	map[player.y][player.x] = 'X';
	ft_flood(map, size, (t_map){player.x + 1, player.y, NULL}, nb, goal, valid);
	ft_flood(map, size, (t_map){player.x - 1, player.y, NULL}, nb, goal, valid);
	ft_flood(map, size, (t_map){player.x, player.y + 1, NULL}, nb, goal, valid);
	ft_flood(map, size, (t_map){player.x, player.y - 1, NULL}, nb, goal, valid);
	map[player.y][player.x] = 'x';
}

int	ft_check_path(char **map, t_map size, t_map player)
{
	int	nb;
	int	goal;
	int	valid;
	int	i;
	int	j;

	i = 0;
	nb = 0;
	goal = 0;
	valid = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (map[i][j] == 'C')
				goal++;
			j++;
		}
		i++;
	}
	if (goal < 1)
		return (0);
	ft_flood(map, size, player, &nb, goal, &valid);
	return (valid ? 1 : 0);
}

int	ft_check_map(char **map, t_map size)
{
	if (!ft_count_player(map, size))
	{
		printf("wrong number of players\n");
		return (0);
	}
	if (!ft_count_exit(map, size))
	{
		printf("wrong number of exits\n");
		return (0);
	}
	if (!ft_rectangular(map, size))
	{
		printf("map is not rectangular\n");
		return (0);
	}
	if (!ft_row_walls(map, size) || !ft_column_walls(map, size))
	{
		printf("map not surrounding by walls\n");
		return (0);
	}
	return (1);
}

int main() {

    char *area[] = {
        "1111111",
        "1C000P1",
        "100E01",
        "1111111"
    };

    t_map size = {7, 4, NULL};
    t_map player = {5, 1, NULL};

    char **map = ft_make_map(area, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

	
	if (ft_check_map(map, size))
	{
		int is_valid_path = ft_check_path(map, size, player);
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
