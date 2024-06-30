
#include "so_long_bonus.h"

void	ft_enemy_case(t_game *game, t_point new_pos)
{
	game->render.map[game->render.player.y][game->render.player.x] = '0';
	game->render.player = new_pos;
	game->render.map[new_pos.y][new_pos.x] = 'P';
	ft_render_loop(game);
	ft_printf("Oops, you are dead\n");
	ft_destroy(game);
	exit(0);
}

int     ft_enemy_loop(t_game *game)
{
    game->enemy_counter++;
    if (game->enemy_counter >= 7)
    {
        game->enemy_frame = (game->enemy_frame + 1) % 7;
        game->enemy_counter = 0;
    }
    ft_render_loop(game);
    return (0);
}

void    ft_render_enemy(t_game *game, int x, int y)
{
    int	px;
	int	py;
	int frame;

	px = x * PIXEL;
	py = y * PIXEL;
	frame = game->enemy_frame;
	mlx_put_image_to_window(game->mlx, game->win, game->enemy[frame], px, py);
}