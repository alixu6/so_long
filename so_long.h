
#ifndef SO_LONG_H
# define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include "minilibx-linux/mlx.h"
#include "ft_printf/libftprintf.h"

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*wdw_ptr;
	void	*textures[5];
	/*t_map	*map;*/
}	t_data;

#endif
