/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** destroy_matrix
*/
#include <stdlib.h>
#include "matrix.h"

void free_matrix(void *matrix)
{
    matrix_map_t *casted = (matrix_map_t *)matrix;

    if (!casted)
        return;
    free(casted->matrix[0]);
    free(casted->matrix);
    free(casted);
}
