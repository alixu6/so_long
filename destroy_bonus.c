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
#include "so_long.h"

void	ft_destroy_images(t_game *game)
{
	game->player_frame = 0;
	while (game->player_frame < 7)
	{
		if (game->player[game->player_frame])
			mlx_destroy_image(game->mlx, game->player[game->player_frame]);
		game->player_frame++;
	}
	/*int i;

    for (i = 0; i < 7; i++) {
        if (game->enemy[i] != NULL) {
            mlx_destroy_image(game->mlx, game->enemy[i]);
            game->enemy[i] = NULL; // Reset pointer to avoid dangling pointer issues
        }
    }

    for (i = 0; i < 7; i++) {
        if (game->player[i] != NULL) {
            mlx_destroy_image(game->mlx, game->player[i]);
            game->player[i] = NULL; // Reset pointer to avoid dangling pointer issues
		}
	}*/
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
