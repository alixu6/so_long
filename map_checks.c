/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:17:07 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 19:13:34 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"
#include "so_long_bonus.h"

int	ft_count_player(t_map *params)
{
	int	count_p;
	int	i;
	int	j;

	count_p = 0;
	i = 0;
	while (i < params->size.y)
	{
		j = 0;
		while (j < params->size.x)
		{
			if (params->map[i][j] == 'P')
				count_p++;
			j++;
		}
		i++;
	}
	if (count_p == 1)
		return (1);
	else
		return (0);
}

int	ft_count_exit(t_map *params)
{
	int	count_e;
	int	i;
	int	j;

	count_e = 0;
	i = 0;
	while (i < params->size.y)
	{
		j = 0;
		while (j < params->size.x)
		{
			if (params->map[i][j] == 'E')
				count_e++;
			j++;
		}
		i++;
	}
	if (count_e == 1)
		return (1);
	else
		return (0);
}

int	ft_rectangular(t_map *params)
{
	int	i;
	int	j;
	int	row_length;

	i = 0;
	row_length = params->size.x;
	while (i < params->size.y)
	{
		j = 0;
		while (params->map[i][j] != '\0')
			j++;
		if (j != row_length)
			return (0);
		i++;
	}
	return (1);
}

int	ft_row_walls(t_map *params)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < params->size.x - 1)
	{
		if (params->map[i][j] != '1')
			return (0);
		j++;
	}
	i = params->size.y - 1;
	j = 0;
	while (j < params->size.x - 1)
	{
		if (params->map[i][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

int	ft_column_walls(t_map *params)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < params->size.y)
	{
		if (params->map[i][j] != '1')
			return (0);
		i++;
	}
	i = 0;
	j = params->size.x - 2;
	while (i < params->size.y)
	{
		if (params->map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}
