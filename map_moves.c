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
	if (!ft_count_player(params))
	{
		ft_printf("Error\nWrong number of players\n");
		return (0);
	}
	if (!ft_count_exit(params))
	{
		ft_printf("Error\nWrong number of exits\n");
		return (0);
	}
	if (!ft_rectangular(params))
	{
		ft_printf("Error\nMap is not rectangular\n");
		return (0);
	}
	if (!ft_row_walls(params)
		|| !ft_column_walls(params))
	{
		ft_printf("Error\nMap not surrounding by walls\n");
		return (0);
	}
	return (1);
}
