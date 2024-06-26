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
	ft_printf("game->w is %d\n", game->w);
	ft_printf("game->h is %d\n", game->h);
	game->bg = mlx_xpm_file_to_image(game->mlx, BG_IMG, &width, &height);
	game->wall = mlx_xpm_file_to_image(game->mlx, WALL_IMG, &width, &height);
	ft_printf("widht is %d\n", width);
	ft_printf("height is %d\n", height);
	ft_printf("cell size is %d %d\n", CELL_SIZE);
	//if (!game->wall)
		//ft_printf("error wall\n");
	game->space = mlx_xpm_file_to_image(game->mlx, SPACE_IMG, &width, &height);
	//if (!game->space)
        //ft_printf("error space\n");
	game->item = mlx_xpm_file_to_image(game->mlx, ITEM_IMG, &width, &height);
	//if (!game->item)
              //ft_printf("error item\n");
	game->player = mlx_xpm_file_to_image(game->mlx, PLAYER_IMG, &width, &height);
	//if (!game->player)
          // ft_printf("error player\n");
	game->exit = mlx_xpm_file_to_image(game->mlx, EXIT_IMG, &width, &height);
	//if (!game->exit)
     //       ft_printf("error exit\n");
	/*if (!game->wall || !game->space || !game->item || !game->player || !game->exit)
	{
		ft_printf("Error\nError loading images");
		exit (EXIT_FAILURE);
	}*/
	/*if (!game->wall || !game->space || !game->item || !game->player || !game->exit)
    {
        ft_printf("Error\nFailed to load textures\n");
        exit(EXIT_FAILURE);
    }*/
	
}



void	ft_render_map(t_game *game)
{
	int	cell_x;
	int	cell_y;
	//int	cell_size = 16; // Set your tile size here
	int	y;
	int	x;
	
	mlx_clear_window(game->mlx, game->win);

	for (y = 0; y < game->render.size.y; y++)
    {
        for (x = 0; x < game->render.size.x; x++)
        {
			
			if (game->render.map[y][x] != '\n' || game->render.map[y][x] != '\0')
           			 mlx_put_image_to_window(game->mlx, game->win, game->space, x * CELL_SIZE, y * CELL_SIZE);
			else
				x++;		 
        }
    }
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < game->render.size.x)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bg, x * CELL_SIZE, y * CELL_SIZE);
		j++;
	}
	i = game->render.size.y - 1;
	j = 0;
	while (j < game->render.size.x)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bg, x * CELL_SIZE, y * CELL_SIZE);
		j++;
	}
	i = 0;
	j = 0;
	while (i < game->render.size.y)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bg, x * CELL_SIZE, y * CELL_SIZE);
		i++;
	}
	i = 0;
	j = game->render.size.x - 1;
	while (i < game->render.size.y)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->bg, x * CELL_SIZE, y * CELL_SIZE);
		i++;
	}
	y = 0;
	while (y < game->render.size.y)
	{
		x = 0;
		while (x < game->render.size.x)
		{
			cell_x = x * CELL_SIZE;
			cell_y = y * CELL_SIZE;
			char tile = game->render.map[y][x];
			if (tile == '1')
			{
				mlx_put_image_to_window(game->mlx, game->win, game->wall, cell_x, cell_y);
				//ft_printf("cellx is %d and celly is %d\n", cell_x, cell_y);
			}
			/*else if(tile == '0')
			{
				mlx_put_image_to_window(game->mlx, game->win, game->space, cell_x, cell_y);
				//ft_printf("cellx is %d and celly is %d\n", cell_x, cell_y);
			}*/
			/*else if (tile == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->item, cell_x, cell_y);*/
			else if (tile == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player, cell_x, cell_y + (game->player_frame * CELL_SIZE));
			/*else if (tile == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit, cell_x, cell_y);*/
			x++;
		}
		y++;
	}
/*for (int y = 0; y < game->render.size.y; y++) {
        for (int x = 0; x < game->render.size.x; x++) {
            cell_x = x * CELL_SIZE;
            cell_y = y * CELL_SIZE;
            if (game->render.map[y][x] == 'P') {
                ft_render_player(game);
            }
        }
	}*/
}

int on_destroy(t_game *game) {
    mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
    free(game->mlx);

    // Free map data
    for (int i = 0; i < game->render.size.x; ++i) {
        free(game->render.map[i]);
    }
    free(game->render.map);

    exit(0);
    return (0);
}

int on_keypress(int keysym, t_game *game)
{
    t_point new_pos = game->render.player;
    if (keysym == XK_Escape)
        on_destroy(game);
    else if (keysym == XK_w)
        new_pos.y--;
    else if (keysym == XK_s)
        new_pos.y++;
    else if (keysym == XK_a)
        new_pos.x--;
    else if (keysym == XK_d)
        new_pos.x++;
    if (new_pos.x >= 0 && new_pos.x < game->render.size.x &&
        new_pos.y >= 0 && new_pos.y < game->render.size.y &&
        game->render.map[new_pos.y][new_pos.x] != '1')
    {
        if (game->render.map[new_pos.y][new_pos.x] == 'E' && game->render.nb == game->render.goal)
            on_destroy(game); // Game won
        else if (game->render.map[new_pos.y][new_pos.x] == 'C')
            game->render.nb++;
        game->render.map[game->render.player.y][game->render.player.x] = '0';
        game->render.player = new_pos;
        game->render.map[new_pos.y][new_pos.x] = 'P';
		ft_player_frame(game);
        ft_render_map(game);
    }
    return (0);
}


