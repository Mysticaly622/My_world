/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** init_world
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_world.h"

static mwindow_t *init_render_window(void)
{
    mwindow_t *window = malloc(sizeof(mwindow_t));
    sfVideoMode mode = {1200, 700, 64};

    if (!window)
        return NULL;
    window->mode = mode;
    window->mwindow = sfRenderWindow_create(mode, "AETHER",
        sfDefaultStyle & ~sfResize, 0);
    if (!window->mwindow)
        return NULL;
    sfRenderWindow_setFramerateLimit(window->mwindow, 60);
    window->background_color = sfColor_fromRGB(0, 167, 225);
    return window;
}

sfMusic *init_music(char *src, int replay)
{
    sfMusic *music = sfMusic_createFromFile(src);

    if (replay)
        sfMusic_setLoop(music, sfTrue);
    sfMusic_setVolume(music, 100);
    return music;
}

my_world_t *init_world(int ac, char **av)
{
    my_world_t *world = malloc(sizeof(my_world_t));

    if (!world)
        return NULL;
    world->mwindow = init_render_window();
    world->editor = init_editor();
    world->clock = sfClock_create();
    world->chopin = init_music("assets/backgroundmusic.ogg", 1);
    world->editor->last_save = NULL;
    if (ac == 2)
        world->editor->last_save = strdup(av[1]);
    if (!world->mwindow || !world->mwindow->mwindow || !world->editor ||
        !world->chopin)
        destroy_world(&world);
    sfMusic_play(world->chopin);
    change_val(world);
    camera_reset(world);
    return world;
}
