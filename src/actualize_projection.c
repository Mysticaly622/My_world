/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** actualize_projection
*/
#include "my_world.h"
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

static sfColor blend_color(const sfColor *a, const sfColor *b, float t)
{
    return sfColor_fromRGB(
        (uint8_t)(a->r + (b->r - a->r) * t),
        (uint8_t)(a->g + (b->g - a->g) * t),
        (uint8_t)(a->b + (b->b - a->b) * t)
    );
}

static sfColor height_to_color(int height)
{
    float t;
    int n = sizeof(ranges) / sizeof(ranges[0]);

    for (int i = 0; i < n; i++)
        if (height >= ranges[i].min && height < ranges[i].max) {
            t = (float)(height - ranges[i].min) /
                (ranges[i].max - ranges[i].min);
            return blend_color(&ranges[i].low, &ranges[i].high, t);
        }
    if (height < 0)
        return (sfColor){0, 80, 160, 255};
    return (sfColor){255, 255, 255, 255};
}

static sfColor shade_by_slope(my_world_t *world, int x, int y, sfColor *base)
{
    int h = MAPXY(world, x, y).height;
    int diff = 0;
    float shade;

    if (x + 1 < MAP(world)->c)
        diff += abs(h - MAPXY(world, x + 1, y).height);
    if (y + 1 < MAP(world)->r)
        diff += abs(h - MAPXY(world, x, y + 1).height);
    shade = 1.f - fminf((float)diff / 3000.f, 0.4f);
    return sfColor_fromRGB(
        (uint8_t)(base->r * shade),
        (uint8_t)(base->g * shade),
        (uint8_t)(base->b * shade)
    );
}

static void change_color(my_world_t *world, int x, int y)
{
    sfColor base;

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    base = height_to_color(MAPXY(world, x, y).height);
    MAPXY(world, x, y).color = shade_by_slope(world, x, y, &base);
}

void change_val(my_world_t *world)
{
    int offset_w = 0;
    int offset_h = 0;
    float yaw = RANGLE_Y(world);

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    offset_w = world->mwindow->mode.width / 2;
    offset_h = world->mwindow->mode.height / 2;
    for (int y = 0; y < MAP(world)->r; y++) {
        for (int x = 0; x < MAP(world)->c; x++) {
            D_MAPXY(world, x, y) = project_iso_point(world, x, y,
                H_MAPXY(world, x, y));
            D_MAPXY(world, x, y).x += offset_w;
            D_MAPXY(world, x, y).y += offset_h / 1.5;
            P_MAPXY(world, x, y) = x * sinf(yaw) + y * cosf(yaw);
            change_color(world, x, y);
        }
    }
}
