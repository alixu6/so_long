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
#include "so_long_bonus.h"

void	ft_init_enemy(t_game *game)
{
	game->enemy[0] = NULL;
	game->enemy[1] = NULL;
	game->enemy[2] = NULL;
	game->enemy[3] = NULL;
	game->enemy[4] = NULL;
	game->enemy[5] = NULL;
	game->enemy[6] = NULL;
}

void	ft_init_player(t_game *game)
{
	game->player[0] = NULL;
	game->player[1] = NULL;
	game->player[2] = NULL;
	game->player[3] = NULL;
	game->player[4] = NULL;
	game->player[5] = NULL;
	game->player[6] = NULL;
}

void	ft_init_struct(t_game *game, char **area, t_point size)
{
	game->render.map = area;
	game->render.size = size;
	game->render.player = ft_find_player_pos(area, size);
	game->render.nb = 0;
	game->render.goal = 0;
	game->render.valid = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->out = NULL;
	game->wall = NULL;
	game->space = NULL;
	game->item = NULL;
	game->exit_open = NULL;
	game->exit = NULL;
	game->count = 0;
	game->w = 0;
	game->h = 0;
	game->player_frame = 0;
	//ame->player_counter = 0;
	game->enemy_frame = 0;
	game->enemy_counter = 0;
	game->move = 0;
	ft_init_player(game);
	ft_init_enemy(game);
}

void	ft_cannot_read_map(void)
{
	ft_printf("Error\nCannot read map\n");
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nExpected input: ./so_long <map_file>\n");
		exit(0);
	}
	game.render.map = ft_read_map(argv[1], &game.render.size);
	if (!game.render.map)
		ft_cannot_read_map();
	ft_init_struct(&game, game.render.map, game.render.size);
	if (ft_check_map(&game.render)) //|| !ft_check_path(&game.render))
	{
		ft_printf("entering check path\n");
		if (!ft_check_path(&game.render))
		{
			ft_printf("Error\nInvalid map\n");
			ft_free_map(game.render.map);
			exit(0);
		}
	}
	ft_free_map(game.render.map);
	game.render.map = ft_read_map(argv[1], &game.render.size);
	if (!game.render.map)
		ft_cannot_read_map();
	ft_game_loop(&game);
	ft_free_map(game.render.map);
	return (0);
}
