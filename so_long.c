/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:27:53 by axu               #+#    #+#             */
/*   Updated: 2024/06/25 18:18:58 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_init_struct(t_game *game, char **area, t_point size)
{
	t_point player_pos;

	game->render.map = area;
	game->render.size = size;
	player_pos = ft_find_player_pos(area, size);
        if (player_pos.x == -1 && player_pos.y == -1)
                return ;
	game->render.player = player_pos;
	game->render.nb = 0;
	game->render.goal = 0;
	game->render.valid = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->out = NULL;
	game->wall = NULL;
	game->space = NULL;
	game->item = NULL;
	/*game->player = 0;*/
	game->exit_open = NULL;
	game->exit = NULL;
	game->count = 0;
	game->w = 0;
	game->h = 0;
	game->player_frame = 0;
	game->move = 0;
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void print_map(char **map, int size_x, int size_y)
{
    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            printf("%c ", map[y][x]); // Print each character of the map
        }
        printf("\n"); // New line after each row
    }
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nExpected input: ./so_long <map_file>\n");
		return (0);
	}
	game.render.map = ft_read_map(argv[1], &game.render.size);
	if (!game.render.map)
	{
		ft_printf("Error\nCannot read map\n");
		return (0);
	}
	/*print_map(game.render.map, game.render.size.x, game.render.size.y);*/
	ft_init_struct(&game, game.render.map, game.render.size);
	if (!ft_check_map(&game.render) || !ft_check_path(&game.render))
	{
		printf("Error\nInvalid map\n");
		ft_free_map(game.render.map);
		exit(EXIT_FAILURE);
	}
	game.render.map = ft_read_map(argv[1], &game.render.size);
	if (!game.render.map)
	{
		ft_printf("Error\nCannot read map\n");
		return (0);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_free_map(game.render.map);
		return (0);
	}
	ft_convert_to_img(&game);
	ft_create_window(&game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &on_keypress, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask, &on_destroy, &game);
	mlx_loop(game.mlx);
	ft_free_map(game.render.map);
	return (0);
}
