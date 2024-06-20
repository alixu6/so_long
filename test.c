#include <stdlib.h>
#include <stdio.h>

typedef struct s_map {
    int x;
    int y;
    struct s_map *next;
} t_stack;

// Push a new position onto the stack
void push(t_stack **stack, int x, int y) {
    t_stack *new_node = (t_stack *)malloc(sizeof(t_stack));
    new_node->x = x;
    new_node->y = y;
    new_node->next = *stack;
    *stack = new_node;
}

// Pop a position from the stack
int pop(t_stack **stack, int *x, int *y) {
    if (*stack == NULL)
        return 0;
    t_stack *temp = *stack;
    *x = temp->x;
    *y = temp->y;
    *stack = (*stack)->next;
    free(temp);
    return 1;
}

// Function to create a map from the given area
char **ft_make_map(char **area, t_stack size) {
    char **map;
    int i = 0;
    int j;

    map = (char **)malloc(sizeof(char *) * size.y);
    while (i < size.y) {
        map[i] = (char *)malloc(sizeof(char) * (size.x + 1));
        j = 0;
        while (j < size.x) {
            map[i][j] = area[i][j];
            j++;
        }
        map[i][size.x] = '\0';
        i++;
    }
    return map;
}


int is_valid_move(char **map, t_stack size, int x, int y) {
    // Check if x and y are within the bounds of the map
    if (x < 0 || x >= size.x || y < 0 || y >= size.y) {
        // If coordinates are out of bounds, return 0 (invalid move)
        return 0;
    }

    // Check the content of the map cell at (x, y)
    char cell = map[y][x];
    if (cell == ' ' || cell == 'C' || cell == 'E') {
        // If cell is empty (' '), contains a coin ('C'), or is the exit ('E'), return 1 (valid move)
        return 1;
    } else {
        // Otherwise, return 0 (invalid move)
        return 0;
    }
}

// Iterative flood fill function to check path validity
void flood_fill(char **map, t_stack size, t_stack player, int *coins_collected, int coins_needed, int *path_valid) {
    t_stack *stack = NULL;
    push(&stack, player.x, player.y);

    while (stack != NULL) {
        int x, y;
        if (!pop(&stack, &x, &y))
            continue;

        if (map[y][x] == 'E') {
            if (*coins_collected == coins_needed)
                *path_valid = 1;
            continue;
        }

        if (map[y][x] == 'C')
            (*coins_collected)++;

        // Mark the current cell as visited
        map[y][x] = 'V';

        // Push all valid neighboring cells onto the stack
        if (is_valid_move(map, size, x + 1, y)) push(&stack, x + 1, y);
        if (is_valid_move(map, size, x - 1, y)) push(&stack, x - 1, y);
        if (is_valid_move(map, size, x, y + 1)) push(&stack, x, y + 1);
        if (is_valid_move(map, size, x, y - 1)) push(&stack, x, y - 1);
    }
}

// Function to initiate the flood fill check from the player's starting position
void ft_check_map(char **map, t_stack size, t_stack player) {
    int coins_collected = 0;
    int coins_needed = 0;
    int path_valid = 0;
    int i = 0;
    int j;

    // Count the total number of coins
    while (i < size.y) {
        j = 0;
        while (j < size.x) {
            if (map[i][j] == 'C')
                coins_needed++;
            j++;
        }
        i++;
    }

    flood_fill(map, size, player, &coins_collected, coins_needed, &path_valid);

    if (path_valid)
        printf("Path is valid and all coins collected!\n");
    else
        printf("Path is invalid or not all coins collected.\n");
}

// Main function for testing
int main() {
    char *area[] = {
        "P  C",
        " CX ",
        " X E",
        "    "
    };

    t_stack size = {4, 4, NULL};
    t_stack player = {0, 0, NULL};

    char **map = ft_make_map(area, size);

    ft_check_map(map, size, player);

    // Free allocated memory
    int i = 0;
    while (i < size.y) {
        free(map[i]);
        i++;
    }
    free(map);

    return 0;
}

typedef struct s_map {
    int x;
    int y;
    struct s_map *next;
} t_map;

// Define a structure for flood fill parameters
typedef struct s_flood_params {
    char **map;
    t_map size;
    t_map player;
    int *coins_collected;
    int coins_needed;
    int *path_valid;
} t_flood_params;

// Push a new position onto the stack
void push(t_map **stack, int x, int y) {
    t_map *new_node = (t_map *)malloc(sizeof(t_map));
    new_node->x = x;
    new_node->y = y;
    new_node->next = *stack;
    *stack = new_node;
}

// Pop a position from the stack
int pop(t_map **stack, int *x, int *y) {
    if (*stack == NULL)
        return 0;
    t_map *temp = *stack;
    *x = temp->x;
    *y = temp->y;
    *stack = (*stack)->next;
    free(temp);
    return 1;
}

// Function to create a map from the given area
char **ft_make_map(char **area, t_map size) {
    char **map;
    int i = 0;
    int j;

    map = (char **)malloc(sizeof(char *) * size.y);
    while (i < size.y) {
        map[i] = (char *)malloc(sizeof(char) * (size.x + 1));
        j = 0;
        while (j < size.x) {
            map[i][j] = area[i][j];
            j++;
        }
        map[i][size.x] = '\0';
        i++;
    }
    return map;
}

// Function to check if a move is valid
int is_valid_move(char **map, t_map size, int x, int y) {
    if (x < 0 || x >= size.x || y < 0 || y >= size.y) {
        return 0; // Out of bounds
    }
    char cell = map[y][x];
    return (cell == ' ' || cell == 'C' || cell == 'E'); // Valid if empty, coin, or exit
}

// Iterative flood fill function to check path validity
void flood_fill(t_flood_params params) {
    t_map *stack = NULL;
    push(&stack, params.player.x, params.player.y);

    while (stack != NULL) {
        int x, y;
        if (!pop(&stack, &x, &y))
            continue;

        if (params.map[y][x] == 'E') {
            if (*(params.coins_collected) == params.coins_needed)
                *(params.path_valid) = 1;
            continue;
        }

        if (params.map[y][x] == 'C')
            (*(params.coins_collected))++;

        // Mark the current cell as visited
        params.map[y][x] = 'V';

        // Push all valid neighboring cells onto the stack
        if (is_valid_move(params.map, params.size, x + 1, y)) push(&stack, x + 1, y);
        if (is_valid_move(params.map, params.size, x - 1, y)) push(&stack, x - 1, y);
        if (is_valid_move(params.map, params.size, x, y + 1)) push(&stack, x, y + 1);
        if (is_valid_move(params.map, params.size, x, y - 1)) push(&stack, x, y - 1);
    }
}

void flood_fill(char **map, t_map size, t_map player, int *coins_collected, int coins_needed, int *path_valid) {
    // Base case: check if player is out of bounds or at a wall
    if (player.x < 0 || player.x >= size.x || player.y < 0 || player.y >= size.y || map[player.y][player.x] == 'X' || map[player.y][player.x] == 'V') {
        return;
    }
    
    // Mark current cell as visited
    if (map[player.y][player.x] == 'C') {
        (*coins_collected)++;
    } else if (map[player.y][player.x] == 'E') {
        if (*coins_collected == coins_needed) {
            *path_valid = 1;
        }
        return;
    }
    
    map[player.y][player.x] = 'V'; // Mark as visited
    
    // Recursively flood fill in all four directions
    flood_fill(map, size, (t_map){player.x + 1, player.y, NULL}, coins_collected, coins_needed, path_valid); // Right
    flood_fill(map, size, (t_map){player.x - 1, player.y, NULL}, coins_collected, coins_needed, path_valid); // Left
    flood_fill(map, size, (t_map){player.x, player.y + 1, NULL}, coins_collected, coins_needed, path_valid); // Down
    flood_fill(map, size, (t_map){player.x, player.y - 1, NULL}, coins_collected, coins_needed, path_valid); // Up
}


// Function to initiate the flood fill check from the player's starting position
void ft_check_map(char **map, t_map size, t_map player) {
    int coins_collected = 0;
    int coins_needed = 0;
    int path_valid = 0;
    int i = 0;
    int j;

    // Count the total number of coins
    while (i < size.y) {
        j = 0;
        while (j < size.x) {
            if (map[i][j] == 'C')
                coins_needed++;
            j++;
        }
        i++;
    }

    // Initialize flood fill parameters
    t_flood_params params = {
        .map = map,
        .size = size,
        .player = player,
        .coins_collected = &coins_collected,
        .coins_needed = coins_needed,
        .path_valid = &path_valid
    };

    // Perform flood fill
    flood_fill(params);

    // Print result
    if (path_valid)
        printf("Path is valid and all coins collected!\n");
    else
        printf("Path is invalid or not all coins collected.\n");
}

void ft_check_map(char **map, t_map size, t_map player) {
    int coins_collected = 0;
    int coins_needed = 0;
    int path_valid = 0;
    int i = 0;
    int j;

    // Count the total number of coins
    while (i < size.y) {
        j = 0;
        while (j < size.x) {
            if (map[i][j] == 'C') {
                coins_needed++;
            }
            j++;
        }
        i++;
    }

    // Perform flood fill to check path validity
    flood_fill(map, size, player, &coins_collected, coins_needed, &path_valid);

    // Print result
    if (path_valid) {
        printf("Path is valid and all coins collected!\n");
    } else {
        printf("Path is invalid or not all coins collected.\n");
    }
}


// Main function for testing
int main() {
    char *area[] = {
        "P  C",
        " CX ",
        " X E",
        "    "
    };

    t_map size = {4, 4, NULL};
    t_map player = {0, 0, NULL};

    char **map = ft_make_map(area, size);

    ft_check_map(map, size, player);

    // Free allocated memory
    int i = 0;
    while (i < size.y) {
        free(map[i]);
        i++;
    }
    free(map);

    return 0;
}

