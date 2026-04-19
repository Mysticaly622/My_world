/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** destroy_editor
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "my_world.h"

sfVector2f project_iso_point(my_world_t *world, int x, int y, int z)
{
    sfVector2f point;
    float yaw = RANGLE_Y(world);
    float pitch = RANGLE_X(world);
    float wx = x - CAMERA(world)->pos.x;
    float wy = y - CAMERA(world)->pos.y;
    float wz = (z - CAMERA(world)->pos.z * (1.f / HEIGHT_SCALE)) * HEIGHT_SCALE;
    float rx = (wx * cos(yaw) - wy * sin(yaw)) * 64.0f * CAMERA(world)->zoom;
    float ry = (wx * sin(yaw) + wy * cos(yaw)) * sin(pitch) * 64.0f *
        CAMERA(world)->zoom - wz * cos(pitch) * 64.0f * CAMERA(world)->zoom;

    point.x = rx;
    point.y = ry;
    return point;
}
