/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** mouse_select
*/
#include "my_world.h"
#include <stdio.h>

static void set_selected_all(my_world_t *world, int val)
{
    if (!world || !EDITOR(world) || !MAP(world))
        return;
    for (int y = 0; y < MAP(world)->r; y++)
        for (int x = 0; x < MAP(world)->c; x++)
            MAP(world)->matrix[y][x].selected = val;
}

static void select_point_mouse(my_world_t *world, sfVector2i *pos,
    sfVector2i *mouse)
{
    sfFloatRect select_bound = {0};

    if (!world || !EDITOR(world) || !pos)
        return;
    select_bound = (sfFloatRect){D_MAPXY(world, pos->x, pos->y).x - 32.f,
        D_MAPXY(world, pos->x, pos->y).y - 32.f, 64.f, 64.f};
    if (sfFloatRect_contains(&select_bound, mouse->x, mouse->y) == sfTrue) {
        CURS(world) = (sfVector2i) {pos->x, pos->y};
        if (pos->x + 1 < MAP(world)->c && pos->y + 1 < MAP(world)->r) {
            S_MAPXY(world, pos->x, pos->y) = 1;
            S_MAPXY(world, pos->x + 1, pos->y) = 1;
            S_MAPXY(world, pos->x, pos->y + 1) = 1;
            S_MAPXY(world, pos->x + 1, pos->y + 1) = 1;
        }
    }
}

static void select_mouse(my_world_t *world)
{
    sfVector2i mouse;

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    if (!sfMouse_isButtonPressed(sfMouseLeft))
        return;
    mouse = sfMouse_getPositionRenderWindow(WIN(world));
    for (sfVector2i curr = {0, 0}; curr.y < MAP(world)->r; curr.x++) {
        if (curr.x >= MAP(world)->c) {
            curr.x = -1;
            curr.y++;
            continue;
        }
        if (point_near_view(world, &(sfVector2f){curr.x, curr.y}))
            select_point_mouse(world, &curr, &mouse);
    }
}

static void brush_mouse(my_world_t *world)
{
    sfVector2i mouse;

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    if (!sfMouse_isButtonPressed(sfMouseRight))
        return;
    set_selected_all(world, 0);
    mouse = sfMouse_getPositionRenderWindow(WIN(world));
    for (sfVector2i curr = {0, 0}; curr.y < MAP(world)->r; curr.x++) {
        if (curr.x >= MAP(world)->c) {
            curr.x = -1;
            curr.y++;
            continue;
        }
        if (point_near_view(world, &(sfVector2f){curr.x, curr.y}))
            select_point_mouse(world, &curr, &mouse);
    }
    sea_level(world, EDITOR(world)->mode_brush);
}

static void brush_mode_change(my_world_t *world)
{
    if (!world || !EDITOR(world))
        return;
    if (KEY_PRESSED(sfKeyG))
        EDITOR(world)->mode_brush--;
    if (KEY_PRESSED(sfKeyT))
        EDITOR(world)->mode_brush++;
}

static void select_movement(my_world_t *world)
{
    if (!world || !EDITOR(world) || !MAP(world))
        return;
    if (KEY_PRESSED(sfKeyUp) && CURS_Y(world) > 0)
        CURS_Y(world)--;
    if (KEY_PRESSED(sfKeyDown) && CURS_Y(world) < MAP(world)->r - 1)
        CURS_Y(world)++;
    if (KEY_PRESSED(sfKeyLeft) && CURS_X(world) > 0)
        CURS_X(world)--;
    if (KEY_PRESSED(sfKeyRight) && CURS_X(world) < MAP(world)->c - 1)
        CURS_X(world)++;
}

static void select_points(my_world_t *world)
{
    int enter_curr = KEY_PRESSED(sfKeyEnter);

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    if (enter_curr && !EDITOR(world)->enter_prev_selection)
        EDITOR(world)->enter_select_val =
            !MAP(world)->matrix[CURS_Y(world)][CURS_X(world)].selected;
    if (enter_curr)
        MAP(world)->matrix[CURS_Y(world)][CURS_X(world)].selected =
            EDITOR(world)->enter_select_val;
    EDITOR(world)->enter_prev_selection = enter_curr;
    if (KEY_PRESSED(sfKeyBackspace))
        set_selected_all(world, 0);
    if (KEY_PRESSED(sfKeyRShift))
        set_selected_all(world, 1);
}

void handle_select(my_world_t *world)
{
    if (!world || !EDITOR(world) || !MAP(world))
        return;
    select_movement(world);
    select_mouse(world);
    select_points(world);
    brush_mode_change(world);
    brush_mouse(world);
}
