/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:04:42 by axu               #+#    #+#             */
/*   Updated: 2024/06/28 14:39:59 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_convert_to_img(t_game *game)
{
	int	pix;

	pix = PIXEL;
	game->out = mlx_xpm_file_to_image(game->mlx, OUT_IMG, &pix, &pix);
	game->wall = mlx_xpm_file_to_image(game->mlx, WALL_IMG, &pix, &pix);
	game->space = mlx_xpm_file_to_image(game->mlx, SPACE_IMG, &pix, &pix);
	game->item = mlx_xpm_file_to_image(game->mlx, ITEM_IMG, &pix, &pix);
	game->player = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG, &pix, &pix);
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
	mlx_loop(game->mlx);
}
