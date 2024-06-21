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

int	ft_count_player(char **map, t_point size)
{
	int	count_p;
	int	i;
	int	j;

	count_p = 0;
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (map[i][j] == 'P')
				count_p++;
			j++;
		}
		i++;
	}
	ft_printf("size.y is %d i is %d count_p is %d size.x is %d\n", size.y, i, count_p, size.x);
	if (count_p == 1)
		return (1);
	else
		return (0);
}

int	ft_count_exit(char **map, t_point size)
{
	int	count_e;
	int	i;
	int	j;

	count_e = 0;
	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (map[i][j] == 'E')
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

int	ft_rectangular(char **map, t_point size)
{
	int	i;
	int	j;
	int	row_length;

	if (size.y <= 0)
		return (0);
	i = 0;
	row_length = size.x;
	while (i < size.y)
	{
		j = 0;
		while (map[i][j] != '\0')
			j++;
		if (j != row_length)
		{
			ft_printf("column = %d\n", j);
			ft_printf("row_length is %d\n", row_length);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_row_walls(char **map, t_point size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("size.x is %d\n", size.x);
	while (j < size.x - 1)
	{
		if (map[i][j] != '1')
		{
			ft_printf("size.x is %d\n", size.x);
			ft_printf("First row not surrounding by walls at column %d\n", j);
			return (0);
		}
		j++;
	}
	i = size.y - 1;
	j = 0;
	while (j < size.x - 1)
	{
		if (map[i][j] != '1')
		{
			ft_printf("Last row not surrounding by walls at column %d\n", j);
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_column_walls(char **map, t_point size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_printf("size.y is %d\n", size.y);
	while (i < size.y)
	{
		ft_printf("size.y is %d\n", size.y);
		if (map[i][j] != '1')
		{
			ft_printf("First column not surrounding by walls at row %d\n", i);
			return (0);
		}
		i++;
	}
	i = 0;
	j = size.x - 2;
	ft_printf("Checking second-to-last column: index %d\n", j);
	while (i < size.y)
	{
		ft_printf("Checking second-to-last column: row %d, value %c\n", i, map[i][j]);
		if (map[i][j] != '1')
		{
			ft_printf("Second-to-last column not surrounding by walls at row %d\n", i);
			return (0);
		}
		i++;
		ft_printf("Incremented i to: %d\n", i);
	}
	ft_printf("Exited loop with i: %d\n", i);
	return (1);
}
