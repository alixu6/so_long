/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:26:16 by axu               #+#    #+#             */
/*   Updated: 2024/06/28 17:30:41 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	ft_destroy_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		mlx_destroy_image(game->mlx, game->enemy[i]);
		i++;
	}
}

void	ft_destroy_player(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		mlx_destroy_image(game->mlx, game->player[i]);
		i++;
	}
}

void	ft_destroy_images(t_game *game)
{
	ft_destroy_player(game);
	ft_destroy_enemy(game);
	if (game->out)
		mlx_destroy_image(game->mlx, game->out);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->space)
		mlx_destroy_image(game->mlx, game->space);
	if (game->item)
		mlx_destroy_image(game->mlx, game->item);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->exit_open)
		mlx_destroy_image(game->mlx, game->exit_open);
}

int	ft_destroy(t_game *game)
{
	ft_destroy_images(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	ft_free_map(game->render.map);
	exit(0);
	return (0);
}
