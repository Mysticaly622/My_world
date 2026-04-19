/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** handle_event
*/
#include "my_world.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

void sea_level(my_world_t *world, int mode)
{
    if (!world || !EDITOR(world) || !MAP(world))
        return;
    for (int y = 0; y < MAP(world)->r; y++)
        for (int x = 0; x < MAP(world)->c; x++)
            H_MAPXY(world, x, y) += mode * S_MAPXY(world, x, y);
}

static void adjust_sea_level_keys(my_world_t *world)
{
    if (!world || !EDITOR(world))
        return;
    if (KEY_PRESSED(sfKeyI))
        sea_level(world, 1);
    if (KEY_PRESSED(sfKeyK))
        sea_level(world, -1);
    if (KEY_PRESSED(sfKeyO))
        sea_level(world, 5);
    if (KEY_PRESSED(sfKeyL))
        sea_level(world, -5);
    if (KEY_PRESSED(sfKeyP))
        sea_level(world, 10);
    if (KEY_PRESSED(sfKeyM))
        sea_level(world, -10);
}

static void reset_map_heights(my_world_t *world)
{
    for (int y = 0; y < MAP(world)->r; y++)
        for (int x = 0; x < MAP(world)->c; x++)
            H_MAPXY(world, x, y) = 0;
}

static void handle_misc_keys(my_world_t *world, sfEvent *event)
{
    if (KEY_PRESSED(sfKeyLAlt) && event->type == sfEvtKeyPressed)
        world->editor->showmap = !world->editor->showmap;
    if (KEY_PRESSED(sfKeyH) && event->type == sfEvtKeyPressed)
        save_map(world);
    if (KEY_PRESSED(sfKeyB) && event->type == sfEvtKeyPressed)
        resume_save(world);
    if (KEY_PRESSED(sfKeyY) && event->type == sfEvtKeyPressed)
        get_save_list();
    if (KEY_PRESSED(sfKeyF) && event->type == sfEvtKeyPressed)
        EDITOR(world)->show_lines = !EDITOR(world)->show_lines;
}

void handle_event(my_world_t *world)
{
    sfEvent event;
    float dt = 0.f;

    if (!world)
        return;
    dt = sfTime_asSeconds(sfClock_restart(world->clock));
    while (sfRenderWindow_pollEvent(WIN(world), &event)) {
        if (KEY_PRESSED(sfKeyEscape) || event.type == sfEvtClosed)
            sfRenderWindow_close(WIN(world));
        if (KEY_PRESSED(sfKeyDelete))
            reset_map_heights(world);
        handle_misc_keys(world, &event);
        handle_zoom(world, &event, dt);
        adjust_sea_level_keys(world);
    }
    handle_select(world);
    handle_camera_displacement(world, dt);
    update_lerp_zoom(world, dt);
    update_lerp_move(world, dt);
    change_val(world);
}
