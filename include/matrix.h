/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** matrix_struct
*/
#ifndef MATRIX_STRUCT_H
    #define MATRIX_STRUCT_H
    #include "my_world_structs.h"

typedef struct tile_s
{
    int selected;
    sfVector2f d_pos;
    sfColor color;
    int height;
    float depth;
} tile_t;

typedef struct matrix_map_cxr
{
    int c;
    int r;
    tile_t **matrix;
} matrix_map_t;

void *malloc_tile_matrix(int c, int r);
void free_matrix(void *matrix);

#endif // MATRIX_STRUCT_H
