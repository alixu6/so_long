/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:58:37 by axu               #+#    #+#             */
/*   Updated: 2024/06/28 13:58:49 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int ft_keypress(int keysym, t_game *game)
{
    t_point new_pos = game->render.player;	
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
    game->move++;
    ft_printf("Number of moves: %d, Number of collectibles: %d\n", game->move, game->count);
    if (new_pos.x >= 0 && new_pos.x < game->render.size.x &&
        new_pos.y >= 0 && new_pos.y < game->render.size.y &&
        game->render.map[new_pos.y][new_pos.x] != '1')
    {
        if (game->render.map[new_pos.y][new_pos.x] == 'C')
        {
            game->count++;
            game->render.map[new_pos.y][new_pos.x] = '0';
        }
        else if (game->render.map[new_pos.y][new_pos.x] == 'E')
        {
            if (game->count == game->render.goal)
            {
                game->render.map[game->render.player.y][game->render.player.x] = '0';
                game->render.player = new_pos;
                game->render.map[new_pos.y][new_pos.x] = 'P';
                ft_render_map(game);
                ft_destroy(game);
                exit(0);
            }
            else
                return (0);
        }
        game->render.map[game->render.player.y][game->render.player.x] = '0';
        game->render.player = new_pos;
        game->render.map[new_pos.y][new_pos.x] = 'P';
        ft_render_map(game);
    }
    return (0);
}