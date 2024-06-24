/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axu <axu@student.42luxembourg.lu>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:27:53 by axu               #+#    #+#             */
/*   Updated: 2024/06/21 19:26:34 by axu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_init_struct(t_map *params, char **area, t_point size)
{
	t_point player_pos;

	params->map = area;
	params->size = size;
	ft_printf("params sizre is %d %d\n", params->size.y, params->size.x);
	player_pos = ft_find_player_pos(area, size);
        if (player_pos.x == -1 && player_pos.y == -1)
                return ;
	params->player = player_pos;
	ft_printf("player pos is %d %d\n", params->player.y, params->player.x);
	params->nb = 0;
	params->goal = 0;
	params->valid = 0;
}

/*int	main(int argc, char *argv[])
{
	t_map	params;
	if (argc != 2)
		exit(EXIT_FAILURE);
	if (argc == 2)
	
	area = map.ber;

	t_point size;
	t_point player;

	**map = ft_make_map(area, size);
	ft_init_struct(&params, map, size, player);
	if (ft_check_map(&params))
		ft_check_path(&params);
*/


/*int main() {

	t_map params;
    char *area[] = {
        "P00C",
        "0C11",
        "000E",
        "C111"
    };

    t_point size = {4, 4};

    char **map = ft_make_map(area, size);
	for (int i = 0; i < size.y; ++i)
		printf("%s\n", area[i]);
	printf("\n");

    int is_valid_path = ft_check_map(&params);
    if (is_valid_path) {
        printf("Path is valid and all coins collected!\n");
    } else {
        printf("Path is invalid or not all coins collected.\n");
    }

    // Free allocated memory
    int i = 0;
    while (i < size.y) {
        free(map[i]);
        i++;
    }
    free(map);

    return 0;
}*/

/*int main() {

        t_map   params;

  t_point size;

    char **map = ft_read_map("map.ber", &size);
    ft_printf("initializing\n");
    ft_init_struct(&params, map, size);
        for (int i = 0; i < size.y; ++i)
                printf("%s\n", map[i]);
        printf("\n");


        if (ft_check_map(&params))
        {
		int is_valid_path = ft_check_path(&params);
                if (is_valid_path) {
                        printf("Path is valid and all coins collected!\n");
                } else {
                        printf("Path is invalid or not all coins collected.\n");
                 }
        }
        else
                printf("Error\n");


    // Free allocated memory
    int i = 0;
    while (i < size.y) {
        free(map[i]);
        i++;
    }
    free(map);

    return 0;
}*/

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return (1);
    }

    t_game game;
    t_point map_size;
    t_map	params;

    game.map = ft_read_map(argv[1], &map_size);
    if (!game.map) {
        fprintf(stderr, "Error reading map\n");
        return (1);
    }

    game.map_rows = map_size.y;
    game.map_cols = map_size.x;

    ft_init_struct(&params, game.map, map_size);
    for (int i = 0; i < map_size.y; ++i)
        printf("%s\n", game.map[i]);
    printf("\n");

    if (ft_check_map(&params)) {
        int is_valid_path = ft_check_path(&params);
        if (is_valid_path) {
            printf("Path is valid and all coins collected!\n");
        } else {
            printf("Path is invalid or not all coins collected.\n");
        }
    } else {
        printf("Error\n");
	exit(EXIT_FAILURE);
    }

    game.mlx_ptr = mlx_init();
    if (!game.mlx_ptr)
        return (1);
    game.wdw_ptr = mlx_new_window(game.mlx_ptr, 1000, 800, "GAME");
    if (!game.wdw_ptr)
        return (free(game.mlx_ptr), 1);

    game.img_collectible = mlx_xpm_file_to_image(game.mlx_ptr, "star.xpm", &game.img_width, &game.img_height);
    game.img_wall = mlx_xpm_file_to_image(game.mlx_ptr, "tileset.xpm", &game.img_width, &game.img_height);
    game.img_empty = mlx_xpm_file_to_image(game.mlx_ptr, "Cloud.xpm", &game.img_width, &game.img_height);
    if (!game.img_wall || !game.img_empty || !game.img_collectible) {
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

    return 0;
}
