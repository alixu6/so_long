/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:27:53 by axu               #+#    #+#             */
/*   Updated: 2024/06/20 10:06:17 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

typedef struct	s_map
{
	int	x;
	int	y;
}	t_map;


char	**ft_make_map(char **area, t_map size)
{
	char	**map;
	int	i;
	int	j;

	map = (char **)malloc(sizeof(char *) * size.y);
	i = 0;
	while (i < size.y)
	{
		map[i] = (char *)malloc(sizeof(char) * (size.x + 1));
		j = 0;
		while (j < size.x)
		{
			map[i][j] = area[i][j];
			j++;
		}
		i++;
	}
	map[i][size.x] = '\0';
	return (map);
}

void	ft_check_chars(char **map, t_map size, t_map player, char to_check)
{
	if (player.x > 0 && map[player.y - 1][player.x] == 'C')

			

void	ft_check_map(char **map, t_map size, t_point player)
{
	ft_check_chars(map, size, player, map[player.y][player.x]);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		exit(EXIT_FAILURE);
	if (argc == 2)

	if (!ft_rectangular)
		error;
	if (!ft_walls)
		error;
	if (!ft_path)
		error;
	if (exit == 1 && c > 0 && P == 1)
		ft_is_valid;


