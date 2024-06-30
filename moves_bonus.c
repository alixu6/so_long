/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:58:37 by axu               #+#    #+#             */
/*   Updated: 2024/06/28 17:25:24 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long_bonus.h"

void	ft_end_game(t_game *game, t_point new_pos)
{
	if (game->count == game->render.goal)
	{
		game->render.map[game->render.player.y][game->render.player.x] = '0';
		game->render.player = new_pos;
		game->render.map[new_pos.y][new_pos.x] = 'P';
		ft_render_loop(game);
		ft_printf("Congrats! You collected all items!\n");
		ft_destroy(game);
		exit(0);
	}
	else
		return ;
}

void	ft_game_moves(t_game *game, t_point new_pos)
{
	if (new_pos.x >= 0 && new_pos.x < game->render.size.x 
		&& new_pos.y >= 0 && new_pos.y < game->render.size.y 
		&& game->render.map[new_pos.y][new_pos.x] != '1')
	{
		game->move++;
		ft_printf("Number of moves: %d\n", game->move);
		if (game->render.map[new_pos.y][new_pos.x] == 'C')
		{
			game->count++;
			game->render.map[new_pos.y][new_pos.x] = '0';
		}
		else if (game->render.map[new_pos.y][new_pos.x] == 'E')
			ft_end_game(game, new_pos);
		else if (game->render.map[new_pos.y][new_pos.x] == 'F')
			ft_enemy_case(game, new_pos);
		game->render.map[game->render.player.y][game->render.player.x] = '0';
		game->render.player = new_pos;
		game->render.map[new_pos.y][new_pos.x] = 'P';
		game->player_frame = (game->player_frame + 1) % 7;
		ft_render_loop(game);
	}
}

int	ft_keys(int keysym, t_game *game)
{
	t_point	new_pos;

	new_pos = game->render.player;
	if (keysym == XK_Escape)
		ft_destroy(game);
	else if (keysym == XK_w || keysym == XK_Up)
		new_pos.y--;
	else if (keysym == XK_s || keysym == XK_Down)
		new_pos.y++;
	else if (keysym == XK_a || keysym == XK_Left)
		new_pos.x--;
	else if (keysym == XK_d || keysym == XK_Right)
		new_pos.x++;
	ft_game_moves(game, new_pos);
	return (0);
}
