/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:04:42 by axu               #+#    #+#             */
/*   Updated: 2024/06/25 18:31:57 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_convert_to_img(t_game *game)
{
    int pix;

    pix = PIXEL;
	game->out = mlx_xpm_file_to_image(game->mlx, OUT_IMG, &pix, &pix);
	game->wall = mlx_xpm_file_to_image(game->mlx, WALL_IMG, &pix, &pix);
	game->space = mlx_xpm_file_to_image(game->mlx, SPACE_IMG, &pix, &pix);
	game->item = mlx_xpm_file_to_image(game->mlx, ITEM_IMG, &pix, &pix);
	game->player[0] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG, &pix, &pix);
    game->player[1] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG1, &pix, &pix);
    game->player[2] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG2, &pix, &pix);
    game->player[3] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG3, &pix, &pix);
    game->player[4] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG4, &pix, &pix);
    game->player[5] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG5, &pix, &pix);
    game->player[6] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG6, &pix, &pix);
	game->exit = mlx_xpm_file_to_image(game->mlx, EXIT_START_IMG, &pix, &pix);
	game->exit_open = mlx_xpm_file_to_image(game->mlx, EXIT_END_IMG, &pix, &pix);

	if (!game->out || !game->wall || !game->space || !game->item
        || !game->exit || !game->exit_open)
	{
		ft_printf("Error\nError loading images");
		exit (0);
	}
}

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
	ft_render_map(game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &ft_keypress, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &ft_destroy, game);
	mlx_loop(game->mlx);
}
