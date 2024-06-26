
#include "so_long.h"

/*void    ft_render_player(t_game *game)
{
    // Calculate the position and size of the current frame in the sprite sheet
    int frame_x = frame_index * CELL_SIZE;   // Adjust based on your animation logic
    int frame_y = anim_state * CELL_SIZE; // Adjust based on your animation logic

    // Calculate the position to render on screen
    int render_x = game->render.player.x * CELL_SIZE;   // Adjust as needed
    int render_y = game->render.player.y * CELL_SIZE;   // Adjust as needed

    // Render the current frame of the player sprite
    mlx_put_image_to_window(game->mlx, game->win, game->player, frame_x, frame_y, render_x, render_y, CELL_SIZE, CELL_SIZE);
}

int ft_player_state(t_game *game)
{
    if ()
}*/

void    ft_player_frame(t_game *game)
{
    game->player_frame++;

    if (game->player_frame >= 7)
    {
        game->player_frame = 0; // Loop back to the first frame
    }
}