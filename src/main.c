/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** main
*/
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "my_world.h"

static int main_game_loop(int ac, char **av)
{
    my_world_t *world = init_world(ac, av);

    if (!world)
        return ERROR_CODE;
    if (ac == 2)
        resume_save(world);
    while (sfRenderWindow_isOpen(WIN(world))) {
        handle_event(world);
        handle_render(world);
    }
    destroy_world(&world);
    return SUCCESS_CODE;
}

int main(int ac, char **av)
{
    if (ac < 1 || ac > 2 || !av[0])
        return ERROR_CODE;
    return main_game_loop(ac, av);
}
