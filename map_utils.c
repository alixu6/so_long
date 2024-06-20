/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:50:42 by axu               #+#    #+#             */
/*   Updated: 2024/06/20 13:05:19 by axu              ###   ########.fr       */
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


void	ft_push_map(t_map **map, int x, int y)
{
	t_map	*new_point;

	new_point = (t_map *)malloc(sizeof(t_map));
	new_point->x = x;
	new_point->y = y;
	new_point->next = *map;
	*map = new_point;
}

int	ft_pop_map(t_map **map, int *x, int *y)
{
	t_map	*temp;
	
	if (*map == NULL)
		return (0);
	temp = *map;
	*x = temp->x;
	*y = temp->y;
	*map = (*map)->next;
	free(temp);
	return (1);
}


