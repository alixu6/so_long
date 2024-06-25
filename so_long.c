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

void	ft_init_struct(t_map *params, char **area, t_point size)
{
	t_point player_pos;

	params->map = area;
	params->size = size;
	//t_printf("params size is %d %d\n", params->size.y, params->size.x);
	player_pos = ft_find_player_pos(area, size);
        if (player_pos.x == -1 && player_pos.y == -1)
                return ;
	params->player = player_pos;
	//ft_printf("player pos is %d %d\n", params->player.y, params->player.x);
	params->nb = 0;
	params->goal = 0;
	params->valid = 0;
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
	ft_init_struct(&game.render, game.render.map, game.render.size);
	if (!ft_check_map(&game.render) || !ft_check_path(&game.render))
	{
		printf("Error\nInvalid map\n");
		exit(EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	ft_create_window(&game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &on_keypress, &game);
	mlx_hook(game.win, DestroyNotify, StructureNotifyMask, &on_destroy, &game);
	mlx_loop(game.mlx);
	return (0);
}
