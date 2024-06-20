/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:05 by axu               #+#    #+#             */
/*   Updated: 2024/06/20 13:50:56 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*#include "so_long.h"*/

#include <stdlib.h>

typedef struct  s_map
{
        int     x;
        int     y;
        struct  s_map *next;
}       t_map;

typedef struct  s_check_map
{
        char    **map;
        t_map   size;
        t_map   player;
        int     *nb;
        int     goal;
        int     *valid;
}       t_check_map;


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

int	ft_valid_move(char **map, t_map size, int x, int y)
{
	char	c;

	c = map[y][x];
	if (x < 0 || x >= size.x || y < 0 || y >= size.y)
		return (0);
	if (c == '0' || c == 'C' || c == 'E')
		return (1);
	else
		return (0);
}

void	ft_flood(char **map, t_map size, t_map player, int *nb, int goal, int *valid)
{
	if (player.x < 0 || player.x >= size.x)
		return ;
	if (player.y < 0 || player.y >= size.y)
		return ;
	if (map[player.y][player.x] == '1' || map[player.y][player.x] == 'X')
		return ;
	if (map[player.y][player.x] == 'C')
		(*nb)++;
	else if (map[player.y][player.x] == 'E')
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
}

#include <stdio.h>

int	ft_check_map(char **map, t_map size, t_map player)
{
	int	nb;
	int	goal;
	int	valid;
	int	i;
	int	j;

	nb = 0;
	goal = 0;
	valid = 0;
	i = 0;
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
	ft_flood(map, size, player, &nb, goal, &valid);
	return (valid ? 1 : 0);
}

int main() {
    char *area[] = {
        "P00C",
        "0C11",
        "000E",
        "C111"
    };

    t_map size = {4, 4, NULL};
    t_map player = {0, 0, NULL};

    char **map = ft_make_map(area, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");


    int is_valid_path = ft_check_map(map, size, player);
    if (is_valid_path) {
        printf("Path is valid and all coins collected!\n");
    } else {
        printf("Path is invalid or not all coins collected.\n");
    }

    // Free allocated memory
    int i = 0;
    while (i < size.y) {
        free(map[i]);
        i++;
    }
    free(map);

    return 0;
}
