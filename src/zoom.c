/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** zoom
*/
#include "my_world.h"

static void clamp_camera_zoom(my_world_t *world)
{
    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (CAMERA(world)->zoom_target < MIN_ZOOM)
        CAMERA(world)->zoom_target = MIN_ZOOM;
    if (CAMERA(world)->zoom_target > MAX_ZOOM)
        CAMERA(world)->zoom_target = MAX_ZOOM;
}

static void handle_zoom_scroll(my_world_t *world, sfEvent *event)
{
    float step = 0.25f;

    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (KEY_PRESSED(sfKeyLControl))
        step = 0.05f;
    if (event->type == sfEvtMouseWheelMoved) {
        if (event->mouseWheel.delta > 0)
            CAMERA(world)->zoom_target += step;
        if (event->mouseWheel.delta < 0)
            CAMERA(world)->zoom_target -= step;
    }
}

static void handle_zoom_input(my_world_t *world, float dt)
{
    float speed = 1.f;

    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (KEY_PRESSED(sfKeyLControl))
        speed = 0.1f;
    if (KEY_PRESSED(sfKeyAdd))
        CAMERA(world)->zoom_target += speed * dt;
    if (KEY_PRESSED(sfKeySubtract))
        CAMERA(world)->zoom_target -= speed * dt;
}

void update_lerp_zoom(my_world_t *world, float dt)
{
    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    CAMERA(world)->zoom += (CAMERA(world)->zoom_target - CAMERA(world)->zoom) *
        LERP_SPEED * dt;
}

void handle_zoom(my_world_t *world, sfEvent *event, float dt)
{
    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    handle_zoom_scroll(world, event);
    handle_zoom_input(world, dt);
    clamp_camera_zoom(world);
}
