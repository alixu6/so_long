/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:00 by axu               #+#    #+#             */
/*   Updated: 2024/06/27 19:06:13 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void    ft_player_frame(t_game *game, int x, int y)
{
	int PIXEL_x = x * PIXEL;
	int PIXEL_y = y * PIXEL;
	/*static int frame_counter = 0;*/
	   /*if (keysym == XK_w || keysym == XK_Up || keysym == XK_s || keysym == XK_Down ||
        keysym == XK_a || keysym == XK_Left || keysym == XK_d || keysym == XK_Right) {*/
       // if (frame_counter == 10)
		//{
			game->player_frame = (game->player_frame + 1) % 7;
		//	frame_counter = 0;
		//}
		mlx_put_image_to_window(game->mlx, game->win, game->player[game->player_frame], PIXEL_x, PIXEL_y);
		//frame_counter++;
}

void ft_render_outline(t_game *game, int x, int y)
{
	int PIXEL_x = x * PIXEL;
	int PIXEL_y = y * PIXEL;
	mlx_put_image_to_window(game->mlx, game->win, game->out, PIXEL_x, PIXEL_y);
}

void ft_render_wall(t_game *game, int x, int y)
{
	int PIXEL_x = x * PIXEL;
	int PIXEL_y = y * PIXEL;
	mlx_put_image_to_window(game->mlx, game->win, game->wall, PIXEL_x, PIXEL_y);
}

void ft_render_space(t_game *game, int x, int y)
{
	int PIXEL_x = x * PIXEL;
	int PIXEL_y = y * PIXEL;
	mlx_put_image_to_window(game->mlx, game->win, game->space, PIXEL_x, PIXEL_y);
}

void ft_render_item(t_game *game, int x, int y)
{
	int PIXEL_x = x * PIXEL;
	int PIXEL_y = y * PIXEL;
	mlx_put_image_to_window(game->mlx, game->win, game->item, PIXEL_x, PIXEL_y);
}

void ft_render_player(t_game *game, int x, int y)
{
	int PIXEL_x = x * PIXEL;
	int PIXEL_y = y * PIXEL;
	mlx_put_image_to_window(game->mlx, game->win, game->player, PIXEL_x, PIXEL_y);
}

void ft_render_exit(t_game *game, int x, int y)
{
	int PIXEL_x = x * PIXEL;
	int PIXEL_y = y * PIXEL;
	if (game->count == game->render.goal)
		mlx_put_image_to_window(game->mlx, game->win, game->exit_open, PIXEL_x, PIXEL_y);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->exit, PIXEL_x, PIXEL_y);
}

void ft_render_map(t_game *game)
{
	int y;
	int x;

	mlx_clear_window(game->mlx, game->win);
    ft_printf("count is %d\n", game->count);
    y = 0;
    while (y < game->render.size.y)
    {
        x = 0;
        while (x < game->render.size.x)
        {
            ft_render_space(game, x, y);
            if (y == 0 || y == game->render.size.y - 1 || x == 0 || x == game->render.size.x - 2)
                ft_render_outline(game, x, y);
            else
			{
				if (game->render.map[y][x] == '1')
					ft_render_wall(game, x, y);
				else if (game->render.map[y][x] == 'C')
					ft_render_item(game, x, y);
				else if (game->render.map[y][x] == 'P')
					ft_player_frame(game, x, y);
				else if (game->render.map[y][x] == 'E')
					ft_render_exit(game, x, y);
			}
            x++;
        }
        y++;
    }
}
