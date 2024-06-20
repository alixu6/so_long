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

int	main(void)
{
	void	*mlx_ptr;
	void	*wdw_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (1);
	wdw_ptr = mlx_new_window(mlx_ptr, 600, 300, "START");
	if (wdw_ptr == NULL)
	{
		free(wdw_ptr);
		return (1);
	}
	mlx_loop(mlx_ptr);	
	/*mlx_destroy_window(mlx_ptr, wdw_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);*/
	return (0);
}


