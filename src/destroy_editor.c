/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** destroy_editor
*/
#include <stdlib.h>
#include "matrix.h"
#include "my_world.h"

void destroy_editor(editor_t **editor)
{
    if (!editor || !(*editor))
        return;
    free_matrix((*editor)->map);
    (*editor)->map = NULL;
    free((*editor)->camera);
    (*editor)->camera = NULL;
    free((*editor)->sorted_tiles);
    (*editor)->sorted_tiles = NULL;
    free((*editor)->last_save);
    (*editor)->last_save = NULL;
    sfTexture_destroy((*editor)->controlmap);
    (*editor)->controlmap = NULL;
    sfVertexArray_destroy((*editor)->faces);
    (*editor)->faces = NULL;
    sfVertexArray_destroy((*editor)->lines);
    (*editor)->lines = NULL;
    free(*editor);
    *editor = NULL;
}
