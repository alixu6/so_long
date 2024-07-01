/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:00 by axu               #+#    #+#             */
/*   Updated: 2024/06/28 17:15:42 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	ft_render_player(t_game *game, int x, int y)
{
	int	px;
	int	py;
	int	frame;

	px = x * PIXEL;
	py = y * PIXEL;
	frame = game->player_frame;
	mlx_put_image_to_window(game->mlx, game->win, game->player[frame], px, py);
}

void	ft_render_space(t_game *game, int x, int y)
{
	int	px;
	int	py;

	px = x * PIXEL;
	py = y * PIXEL;
	mlx_put_image_to_window(game->mlx, game->win, game->space, px, py);
}

void	ft_render_exit(t_game *game, int x, int y)
{
	int	px;
	int	py;

	px = x * PIXEL;
	py = y * PIXEL;
	if (game->count == game->render.goal)
		mlx_put_image_to_window(game->mlx, game->win, game->exit_open, px, py);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->exit, px, py);
}

void	ft_render_map(t_game *game, int x, int y)
{
	int	px;
	int	py;

	px = x * PIXEL;
	py = y * PIXEL;
	if (y == 0 || y == game->render.size.y - 1
		|| x == 0 || x == game->render.size.x - 2)
		mlx_put_image_to_window(game->mlx, game->win, game->out, px, py);
	else
	{
		if (game->render.map[y][x] == '1')
			mlx_put_image_to_window(game->mlx, game->win, game->wall, px, py);
		else if (game->render.map[y][x] == 'C')
			mlx_put_image_to_window(game->mlx, game->win, game->item, px, py);
		else if (game->render.map[y][x] == 'P')
			ft_render_player(game, x, y);
		else if (game->render.map[y][x] == 'E')
			ft_render_exit(game, x, y);
		else if (game->render.map[y][x] == 'F')
			ft_render_enemy(game, x, y);
	}
}

void	ft_render_loop(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->render.size.y)
	{
		x = 0;
		while (x < game->render.size.x)
		{
			ft_render_space(game, x, y);
			ft_render_map(game, x, y);
			x++;
		}
		y++;
	}
	ft_render_moves(game);
}
