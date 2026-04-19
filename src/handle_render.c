/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** handle_render
*/
#include "my_world.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static void draw_curs_select(my_world_t *world)
{
    sfCircleShape *cursor = NULL;

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    cursor = sfCircleShape_create();
    if (!cursor)
        return;
    sfCircleShape_setRadius(cursor, 5.f);
    sfCircleShape_setFillColor(cursor, sfWhite);
    sfCircleShape_setOrigin(cursor, (sfVector2f){5.f, 5.f});
    sfCircleShape_setPosition(cursor,
        MAP(world)->matrix[CURS_Y(world)][CURS_X(world)].d_pos);
    sfRenderWindow_drawCircleShape(WIN(world), cursor, NULL);
    sfCircleShape_destroy(cursor);
}

static void draw_one_select(my_world_t *world, sfVector2f *pos)
{
    sfCircleShape *cursor = NULL;

    if (!world || !EDITOR(world) || !pos)
        return;
    cursor = sfCircleShape_create();
    if (!cursor)
        return;
    sfCircleShape_setRadius(cursor, 7.f);
    sfCircleShape_setFillColor(cursor, sfRed);
    sfCircleShape_setOrigin(cursor, (sfVector2f){7.f, 7.f});
    sfCircleShape_setPosition(cursor, *pos);
    sfRenderWindow_drawCircleShape(WIN(world), cursor, NULL);
    sfCircleShape_destroy(cursor);
}

static void draw_all_select(my_world_t *world)
{
    sfVector2f d_pos;

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    for (sfVector2i curr = {0, 0}; curr.y < MAP(world)->r; curr.x++) {
        if (curr.x >= MAP(world)->c) {
            curr.y++;
            curr.x = -1;
            continue;
        }
        if (!MAP(world)->matrix[curr.y][curr.x].selected)
            continue;
        d_pos = MAP(world)->matrix[curr.y][curr.x].d_pos;
        if (point_inside_view(world, &(sfVector2f){curr.x, curr.y}))
            draw_one_select(world, &d_pos);
    }
}

static void draw_select(my_world_t *world)
{
    if (!world || !EDITOR(world))
        return;
    draw_all_select(world);
    draw_curs_select(world);
}

static void display_controls(my_world_t *world)
{
    sfVector2u size = sfTexture_getSize(world->editor->controlmap);
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, (sfVector2f){size.x, size.y});
    sfRectangleShape_setScale(rect, (sfVector2f){0.45, 0.45});
    sfRectangleShape_setOrigin(rect, (sfVector2f){size.x / 2, size.y / 2});
    sfRectangleShape_setPosition(rect,
        (sfVector2f){world->mwindow->mode.width / 2,
            world->mwindow->mode.height / 2});
    sfRectangleShape_setTexture(rect, world->editor->controlmap, sfTrue);
    sfRenderWindow_drawRectangleShape(world->mwindow->mwindow, rect, NULL);
    sfRectangleShape_destroy(rect);
}

void handle_render(my_world_t *world)
{
    if (!world || !EDITOR(world) || !MAP(world) || !WIN(world))
        return;
    sfRenderWindow_clear(WIN(world), world->mwindow->background_color);
    draw_all_tiles(world);
    draw_select(world);
    if (world->editor->showmap == 1)
        display_controls(world);
    sfRenderWindow_display(WIN(world));
}
