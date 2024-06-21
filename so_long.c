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

void	ft_init_struct(t_map *params, char **area, t_point size, t_point player)
{
	params->map = area;
	params->size = size;
	params->player = player;
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

int main() {

        t_map   params;

 /*   char *area[] = {
        "1111111",
        "1C000P1",
        "100E01",
        "1111111"
    };*/
  t_point size;
    t_point player = {9, 7};

    char **map = ft_read_map("map.ber", &size);
    ft_init_struct(&params, map, size, player);
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
}

