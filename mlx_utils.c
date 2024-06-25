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
	game->wall = mlx_xpm_file_to_image(game->mlx, "flower.xpm", &game->w, &game->h);
	if (!game->wall)
		ft_printf("error wall\n");
	//game->space = mlx_xpm_file_to_image(game->mlx, "space.xpm", &game->w, &game->h);
	//if (!game->space)
          //      ft_printf("error space\n");
	game->item = mlx_xpm_file_to_image(game->mlx, "heart.xpm", &game->w, &game->h);
	if (!game->item)
                ft_printf("error item\n");
	game->player = mlx_xpm_file_to_image(game->mlx, "./assets/Pink_Monster.xpm", &game->w, &game->h);
	if (!game->player)
              ft_printf("error player\n");
	game->exit = mlx_xpm_file_to_image(game->mlx, "star.xpm", &game->w, &game->h);
	if (!game->exit)
                ft_printf("error exit\n");
	/*if (!game->wall || !game->space || !game->item || !game->player || !game->exit)
	{
		ft_printf("Error\nError loading images");
		exit (EXIT_FAILURE);
	}*/
}



void	ft_render_map(t_game *game)
{
	int	cell_x;
	int	cell_y;
	//int	cell_size = 16; // Set your tile size here
	int	y;
	int	x;

	
	ft_convert_to_img(game);
	y = 0;
	while (y < game->render.size.y)
	{
		x = 0;
		while (x < game->render.size.x)
		{
			cell_x = x * CELL_SIZE;
			cell_y = y * CELL_SIZE;
			/*if (game->render.map[y][x] == '0')
			{
				mlx_put_image_to_window(game->mlx, game->win, game->space, cell_x, cell_y);
				ft_printf("cellx is %d and celly is %d\n", cell_x, cell_y);
			}
			else if(game->render.map[y][x] == '1')
			{
				mlx_put_image_to_window(game->mlx, game->win, game->wall, cell_x, cell_y);
				ft_printf("cellx is %d and celly is %d\n", cell_x, cell_y);
			}
			else if (game->render.map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->item, cell_x, cell_y);
			*/ if (game->render.map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player, cell_x, cell_y);
			x++;
		}
		y++;
	}
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

int on_keypress(int keysym, t_game *game) {
    (void)game;
    printf("Pressed key: %d\n", keysym);
    return (0);
}

