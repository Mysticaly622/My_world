/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** destroy_world
*/
#include <stdlib.h>
#include "my_world.h"

static void destroy_render_window(mwindow_t **window)
{
    if (!window || !(*window))
        return;
    sfRenderWindow_destroy((*window)->mwindow);
    (*window)->mwindow = NULL;
    free(*window);
    *window = NULL;
}

void destroy_world(my_world_t **world)
{
    if (!world || !*world)
        return;
    destroy_render_window(&((*world)->mwindow));
    destroy_editor(&((*world)->editor));
    sfClock_destroy((*world)->clock);
    sfMusic_destroy((*world)->chopin);
    (*world)->clock = NULL;
    free(*world);
    *world = NULL;
}
