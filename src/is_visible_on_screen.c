/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** is_visible_on_screen
*/
#include "my_world.h"

int point_inside_view(my_world_t *world, sfVector2f *coord)
{
    int w = world->mwindow->mode.width;
    int h = world->mwindow->mode.height;
    sfVector2f d_pos;

    if (!world || !EDITOR(world) || !MAP(world) || !MAP(world)->matrix ||
        !coord)
        return 0;
    d_pos = MAP(world)->matrix[(int)coord->y][(int)coord->x].d_pos;
    if (d_pos.x < 0 || d_pos.x > w ||
        d_pos.y < 0 || d_pos.y > h)
        return 0;
    return 1;
}

static int is_point_neighoring_visible(my_world_t *world, int x, int y)
{
    if (!world || !EDITOR(world) || !MAP(world))
        return 0;
    if (x > 0)
        if (point_inside_view(world, &(sfVector2f){x - 1, y}))
            return 1;
    if (x + 1 < MAP(world)->c)
        if (point_inside_view(world, &(sfVector2f){x + 1, y}))
            return 1;
    if (y > 0)
        if (point_inside_view(world, &(sfVector2f){x, y - 1}))
            return 1;
    if (y + 1 < MAP(world)->r)
        if (point_inside_view(world, &(sfVector2f){x, y + 1}))
            return 1;
    if (x + 1 < MAP(world)->c && y + 1 < MAP(world)->r)
        if (point_inside_view(world, &(sfVector2f){x + 1, y + 1}))
            return 1;
    return 0;
}

int point_near_view(my_world_t *world, sfVector2f *coord)
{
    if (!world || !EDITOR(world) || !MAP(world) || !MAP(world)->matrix ||
        !coord)
        return 0;
    if (point_inside_view(world, coord))
        return 1;
    return is_point_neighoring_visible(world, (int)coord->x, (int)coord->y);
}
