/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:04:42 by axu               #+#    #+#             */
/*   Updated: 2024/06/20 10:04:48 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void render_map(t_game *game) {
    int tile_x, tile_y;
    int tile_size = 35; // Set your tile size here

    for (int y = 0; y < game->map_rows; ++y) {
        for (int x = 0; x < game->map_cols; ++x) {
            // Determine tile position
            tile_x = x * tile_size;
            tile_y = y * tile_size;

	    // Example: Rendering logic based on map data
            if (game->map[y][x] == '1') // Example condition for rendering a wall tile
                mlx_put_image_to_window(game->mlx_ptr, game->wdw_ptr, game->img_wall, tile_x, tile_y);
            else if (game->map[y][x] == '0') // Example condition for rendering an empty tile
                mlx_put_image_to_window(game->mlx_ptr, game->wdw_ptr, game->img_empty, tile_x, tile_y);
	    else if (game->map[y][x] == 'C')
		    mlx_put_image_to_window(game->mlx_ptr, game->wdw_ptr, game->img_collectible, tile_x, tile_y);
        }
    }
}

int on_destroy(t_game *game) {
    mlx_destroy_window(game->mlx_ptr, game->wdw_ptr);
    mlx_destroy_display(game->mlx_ptr);
    free(game->mlx_ptr);

    // Free map data
    for (int i = 0; i < game->map_rows; ++i) {
        free(game->map[i]);
    }
    free(game->map);

    exit(0);
    return (0);
}

int on_keypress(int keysym, t_game *game) {
    (void)game;
    printf("Pressed key: %d\n", keysym);
    return (0);
}

/*int main(void) {
    t_game game;
    t_point map_size;

    game.map = ft_read_map("map.ber", &map_size);
    if (!game.map) {
        fprintf(stderr, "Error reading map\n");
        return (1);
    }

    game.map_rows = map_size.y;
    game.map_cols = map_size.x;

    game.mlx_ptr = mlx_init();
    if (!game.mlx_ptr)
        return (1);
    game.wdw_ptr = mlx_new_window(game.mlx_ptr, 1000, 800, "GAME");
    if (!game.wdw_ptr)
        return (free(game.mlx_ptr), 1);

    game.img_collectible = mlx_xpm_file_to_image(game.mlx_ptr, "star.xpm", &game.img_width, &game.img_height);
    game.img_wall = mlx_xpm_file_to_image(game.mlx_ptr, "tileset.xpm", &game.img_width, &game.img_height);
    game.img_empty = mlx_xpm_file_to_image(game.mlx_ptr, "Cloud.xpm", &game.img_width, &game.img_height);
    if (!game.img_wall || !game.img_empty) {
        fprintf(stderr, "Error loading images\n");
        return (1);
    }
    render_map(&game);

    // Register key release hook
    mlx_hook(game.wdw_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &game);

    // Register destroy hook
    mlx_hook(game.wdw_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &game);

    // Loop over the MLX pointer
    mlx_loop(game.mlx_ptr);
    return (0);
}
*/
