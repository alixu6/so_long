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
	//t_printf("params size is %d %d\n", params->size.y, params->size.x);
	player_pos = ft_find_player_pos(area, size);
        if (player_pos.x == -1 && player_pos.y == -1)
                return ;
	game->render.player = player_pos;
	//ft_printf("player pos is %d %d\n", params->player.y, params->player.x);
	game->render.nb = 0;
	game->render.goal = 0;
	game->render.valid = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->bg = NULL;
	game->wall = NULL;
	game->space = NULL;
	game->item = NULL;
	game->player = NULL;
	game->exit = NULL;
	game->w = 0;
	game->h = 0;
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
	ft_init_struct(&game, game.render.map, game.render.size);
	if (!ft_check_map(&game.render) || !ft_check_path(&game.render))
	{
		printf("Error\nInvalid map\n");
		exit(EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	ft_convert_to_img(&game);
	ft_create_window(&game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &on_keypress, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask, &on_destroy, &game);
	mlx_loop(game.mlx);
	ft_free_map(game.render.map);
	return (0);
}
