/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:04:42 by axu               #+#    #+#             */
/*   Updated: 2024/06/28 14:39:59 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	ft_enemy_img(t_game *game)
{
	int	pix;

	pix = PIXEL;
	game->enemy[0] = mlx_xpm_file_to_image(game->mlx, ENEMY, &pix, &pix);
	game->enemy[1] = mlx_xpm_file_to_image(game->mlx, ENEMY1, &pix, &pix);
	game->enemy[2] = mlx_xpm_file_to_image(game->mlx, ENEMY2, &pix, &pix);
	game->enemy[3] = mlx_xpm_file_to_image(game->mlx, ENEMY3, &pix, &pix);
	game->enemy[4] = mlx_xpm_file_to_image(game->mlx, ENEMY4, &pix, &pix);
	game->enemy[5] = mlx_xpm_file_to_image(game->mlx, ENEMY5, &pix, &pix);
	game->enemy[6] = mlx_xpm_file_to_image(game->mlx, ENEMY6, &pix, &pix);
	if (!game->enemy[0] || !game->enemy[1] || !game->enemy[2]
		|| !game->enemy[3] || !game->player[4] || !game->enemy[5] || !game->enemy[6])
	{
		ft_printf("Error\nError loading images");
		exit (0);
	}
}

void	ft_player_img(t_game *game)
{
	int	pix;

	pix = PIXEL;
	game->player[0] = mlx_xpm_file_to_image(game->mlx, PLAYER, &pix, &pix);
	game->player[1] = mlx_xpm_file_to_image(game->mlx, PLAYER1, &pix, &pix);
	game->player[2] = mlx_xpm_file_to_image(game->mlx, PLAYER2, &pix, &pix);
	game->player[3] = mlx_xpm_file_to_image(game->mlx, PLAYER3, &pix, &pix);
	game->player[4] = mlx_xpm_file_to_image(game->mlx, PLAYER4, &pix, &pix);
	game->player[5] = mlx_xpm_file_to_image(game->mlx, PLAYER5, &pix, &pix);
	game->player[6] = mlx_xpm_file_to_image(game->mlx, PLAYER6, &pix, &pix);
	if (!game->player[0] || !game->player[1] || !game->player[2]
		|| !game->player[3] || !game->player[4] || !game->player[5] || !game->player[6])
	{
		ft_printf("Error\nError loading images");
		exit (0);
	}
}

void	ft_convert_to_img(t_game *game)
{
	int	pix;

	pix = PIXEL;
	ft_player_img(game);
	ft_enemy_img(game);
	game->out = mlx_xpm_file_to_image(game->mlx, OUT_IMG, &pix, &pix);
	game->wall = mlx_xpm_file_to_image(game->mlx, WALL_IMG, &pix, &pix);
	game->space = mlx_xpm_file_to_image(game->mlx, SPACE_IMG, &pix, &pix);
	game->item = mlx_xpm_file_to_image(game->mlx, ITEM_IMG, &pix, &pix);
	game->exit = mlx_xpm_file_to_image(game->mlx, EXIT_IMG1, &pix, &pix);
	game->exit_open = mlx_xpm_file_to_image(game->mlx, EXIT_IMG2, &pix, &pix);
	if (!game->out || !game->wall || !game->space || !game->item
		|| !game->exit || !game->exit_open)
	{
		ft_printf("Error\nError loading images");
		exit (0);
	}
}

void	ft_create_window(t_game	*game)
{
	game->w = (game->render.size.x - 1) * PIXEL;
	game->h = game->render.size.y * PIXEL;
	game->win = mlx_new_window(game->mlx, game->w, game->h, "GAME");
	if (!game->win)
	{
		free(game->mlx);
		return ;
	}
}

void	ft_game_loop(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_free_map(game->render.map);
		exit(0);
	}
	ft_convert_to_img(game);
	ft_create_window(game);
	mlx_clear_window(game->mlx, game->win);
	ft_render_loop(game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &ft_keys, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_destroy, game);
	mlx_loop_hook(game->mlx, &ft_enemy_loop, game);
	mlx_loop(game->mlx);
}
