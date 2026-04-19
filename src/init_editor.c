/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** init_editor
*/
#include <stdlib.h>
#include "my_world.h"
#include "my_world_events.h"

static camera_t *init_camera(sfVector2i *init_angle)
{
    camera_t *camera = malloc(sizeof(camera_t));

    if (!camera)
        return NULL;
    camera->angle = (sfVector2f){init_angle->x, init_angle->y};
    camera->target_angle = (sfVector2f){init_angle->x, init_angle->y};
    camera->pos = (sfVector3f){0.f, 0.f, 0.f};
    camera->target_pos = (sfVector3f){0.f, 0.f, 0.f};
    camera->zoom = 1.f;
    camera->zoom_target = 1.f;
    return camera;
}

static void init_vertex(editor_t *editor)
{
    if (!editor)
        return;
    editor->faces = sfVertexArray_create();
    editor->lines = sfVertexArray_create();
    if (!editor->faces || !editor->lines)
        return;
    editor->show_lines = 1;
    sfVertexArray_setPrimitiveType(editor->faces, sfTriangles);
    sfVertexArray_setPrimitiveType(editor->lines, sfLines);
}

static void init_control_mapping(editor_t *editor)
{
    if (!editor)
        return;
    editor->showmap = 0;
    editor->controlmap = sfTexture_createFromFile("assets/control.png", NULL);
}

editor_t *init_editor(void)
{
    editor_t *editor = malloc(sizeof(editor_t));

    if (!editor)
        return NULL;
    editor->camera = init_camera(&(sfVector2i){20, 35});
    editor->map = malloc_tile_matrix(MAP_X_INIT, MAP_Y_INIT);
    editor->select_curs = (sfVector2i){0, 0};
    editor->enter_prev_selection = 0;
    editor->enter_select_val = 0;
    editor->sorted_count = 0;
    editor->mode_brush = 0;
    init_control_mapping(editor);
    init_vertex(editor);
    editor->sorted_tiles = malloc(MAP_X_INIT * MAP_Y_INIT * sizeof(tile_t *));
    if (!editor->camera || !editor->map || !editor->map->matrix ||
        !editor->faces || !editor->lines || !editor->sorted_tiles) {
        destroy_editor(&editor);
        return NULL;
    }
    return editor;
}
