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
	int width;
	int	height;

	width = CELL_SIZE * 7;
	height = CELL_SIZE;
	game->out = mlx_xpm_file_to_image(game->mlx, OUT_IMG, &width, &height);
	game->wall = mlx_xpm_file_to_image(game->mlx, WALL_IMG, &width, &height);
	game->space = mlx_xpm_file_to_image(game->mlx, SPACE_IMG, &width, &height);
	game->item = mlx_xpm_file_to_image(game->mlx, ITEM_IMG, &width, &height);
	game->player[0] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG, &width, &height);
    game->player[1] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG1, &width, &height);
    game->player[2] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG2, &width, &height);
    game->player[3] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG3, &width, &height);
    game->player[4] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG4, &width, &height);
    game->player[5] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG5, &width, &height);
    game->player[6] = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG6, &width, &height);
	game->exit = mlx_xpm_file_to_image(game->mlx, EXIT_START_IMG, &width, &height);
	game->exit_open = mlx_xpm_file_to_image(game->mlx, EXIT_END_IMG, &width, &height);

	if (!game->out || !game->wall || !game->space || !game->item || !game->exit || !game->exit_open)
	{
		ft_printf("Error\nError loading images");
		exit (EXIT_FAILURE);
	}
}

int on_destroy(t_game *game) {
    if (game->out)
		mlx_destroy_image(game->mlx, game->out);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->space)
		mlx_destroy_image(game->mlx, game->space);
	if (game->item)
		mlx_destroy_image(game->mlx, game->item);
	if (game->player[game->player_frame])
		mlx_destroy_image(game->mlx, game->player[game->player_frame]);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->exit_open)
		mlx_destroy_image(game->mlx, game->exit_open);
    mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
    free(game->mlx);

    // Free map data
    /*for (int i = 0; i < game->render.size.x; ++i) {
        free(game->render.map[i]);
    }
    free(game->render.map);

    exit(0);*/
    return (0);
}

int on_keypress(int keysym, t_game *game)
{
	/*print_map(game->render.map, game->render.size.x, game->render.size.y);*/
    t_point new_pos = game->render.player;
	ft_printf("player pos is %d %d\n", game->render.player);
	/*game->render.nb = 0;*/
	/*ft_printf("nb game is %d\n", game->render.nb_game);*/
    if (keysym == XK_Escape)
        on_destroy(game);
    else if (keysym == XK_w || keysym == XK_Up)
        new_pos.y--;
    else if (keysym == XK_s || keysym == XK_Down)
        new_pos.y++;
    else if (keysym == XK_a || keysym == XK_Left)
        new_pos.x--;
    else if (keysym == XK_d || keysym == XK_Right)
        new_pos.x++;
    game->move++;
    ft_printf("Number of moves: %d\n", game->move);
    // Check if the new position is within bounds and not a wall ('1')
    if (new_pos.x >= 0 && new_pos.x < game->render.size.x &&
        new_pos.y >= 0 && new_pos.y < game->render.size.y &&
        game->render.map[new_pos.y][new_pos.x] != '1')
    {
        // Handle item interactions
        if (game->render.map[new_pos.y][new_pos.x] == 'C')
        {
            // Collectible found, increment collectibles count
            game->count++;
			ft_printf("nb game is now %d after collecting\n", game->count);
            game->render.map[new_pos.y][new_pos.x] = '0'; // Remove collectible from map
        }
        else if (game->render.map[new_pos.y][new_pos.x] == 'E')
        {
            // Check if all collectibles have been collected
            if (game->count == game->render.goal)
            {
                // All collectibles collected, move to exit
                game->render.map[game->render.player.y][game->render.player.x] = '0'; // Clear previous player position
                game->render.player = new_pos;
                game->render.map[new_pos.y][new_pos.x] = 'P'; // Place player in new position
                ft_render_map(game);
                on_destroy(game); // Game won
                return 0; // Exit function to prevent further movement
            }
            else
            {
                // Not all collectibles collected, cannot move to exit
                return 0; // Exit function without further action
            }
        }

        // Update player position
        game->render.map[game->render.player.y][game->render.player.x] = '0'; // Clear previous player position
        game->render.player = new_pos;
        game->render.map[new_pos.y][new_pos.x] = 'P'; // Place player in new position
        /*ft_player_frame(keysym, game);*/
        // Render updated map
        ft_render_map(game);
    }

    return 0;
}

void	ft_create_window(t_game	*game)
{
	game->w = (game->render.size.x - 1) * CELL_SIZE;
	game->h = game->render.size.y * CELL_SIZE;
	ft_printf("game render size x is %d\n", game->render.size.x);
	ft_printf("game w is %d\n", game->w);
	ft_printf("game render size y is %d\n", game->render.size.y);
	ft_printf("game h is %d\n", game->h);
	game->win = mlx_new_window(game->mlx, game->w, game->h, "GAME");
        if (!game->win)
	{
		free(game->mlx);
		return ;
	}
	ft_render_map(game);
}
