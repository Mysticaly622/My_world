/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** create_matrix
*/
#include <stdlib.h>
#include "matrix.h"
#include "my_world.h"

void *malloc_tile_matrix(int c, int r)
{
    matrix_map_t *matrix = malloc(sizeof(matrix_map_t));
    tile_t *tiles = malloc(sizeof(tile_t) * r * c);
    tile_t **grid = malloc(sizeof(tile_t *) * r);

    if (!matrix || !tiles || !grid)
        return NULL;
    for (int i = 0; i < r * c; i++)
        tiles[i] = (tile_t){0};
    for (int i = 0; i < r; i++)
        grid[i] = &tiles[i * c];
    matrix->c = c;
    matrix->r = r;
    matrix->matrix = grid;
    return matrix;
}
