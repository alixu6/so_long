/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 09:50:42 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 19:29:16 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"
#include <stdlib.h>

/*void	ft_push_map(t_map **map, int x, int y)
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
}*/

/*t_point	ft_get_map_size(const char *map_file)
{
	int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return (t_point){0, 0};
    }

    char *line;
    t_point size = {0, 0};
    int rows = 0;
    int cols = 0;

    while ((line = get_next_line(fd)) != NULL) {
        if (cols == 0)
            cols = ft_strlen(line) - 1; // Assuming the line ends with '\n'
        rows++;
        free(line);
    }
    close(fd);

    size.y = rows;
    ft_printf("size.y is %d\n", rows);
    size.x = cols;
    ft_printf("size.y is %d\n", cols);

    return size;
}*/

t_point	ft_find_player_pos(char **map, t_point size)
{
	t_point	player_pos;
	int	y;
	int	x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (map[y][x] == 'P')
			{
				player_pos.x = x;
				player_pos.y = y;
				return (player_pos);
			}
			x++;
		}
		y++;
	}
	player_pos.x = -1;
	player_pos.y = -1;
	return (player_pos);
}
