/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** camera_displacements
*/
#include "my_world.h"
#include <math.h>

static void fix_camera_angle(my_world_t *world)
{
    float min_tilt = MIN_TILT;
    float max_tilt = MAX_TILT;

    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (CAMERA(world)->target_angle.y < 0.f)
        CAMERA(world)->target_angle.y += 360.f;
    if (CAMERA(world)->target_angle.y > 360.f)
        CAMERA(world)->target_angle.y -= 360.f;
    if (CAMERA(world)->target_angle.x < min_tilt)
        CAMERA(world)->target_angle.x = min_tilt;
    if (CAMERA(world)->target_angle.x > max_tilt)
        CAMERA(world)->target_angle.x = max_tilt;
}

static void clamp_camera_pos(my_world_t *world)
{
    int map_c = 0;
    int map_r = 0;

    if (!world || !EDITOR(world) || !CAMERA(world) || !MAP(world))
        return;
    map_c = MAP(world)->c;
    map_r = MAP(world)->r;
    if (CAMERA(world)->target_pos.x < 0.f)
        CAMERA(world)->target_pos.x = 0.f;
    if (CAMERA(world)->target_pos.x > map_c)
        CAMERA(world)->target_pos.x = map_c;
    if (CAMERA(world)->target_pos.y < 0.f)
        CAMERA(world)->target_pos.y = 0.f;
    if (CAMERA(world)->target_pos.y > map_r)
        CAMERA(world)->target_pos.y = map_r;
}

static void camera_forward_backward(my_world_t *world, float dt)
{
    float speed = CAMERA_SPEED_XY * dt * (1.f / CAMERA(world)->zoom + 1.f);

    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (KEY_PRESSED(sfKeyLControl))
        speed *= 2;
    if (KEY_PRESSED(sfKeyZ)) {
        CAMERA(world)->target_pos.x -= sin(RANGLE_Y(world)) * speed;
        CAMERA(world)->target_pos.y -= cos(RANGLE_Y(world)) * speed;
    }
    if (KEY_PRESSED(sfKeyS)) {
        CAMERA(world)->target_pos.x += sin(RANGLE_Y(world)) * speed;
        CAMERA(world)->target_pos.y += cos(RANGLE_Y(world)) * speed;
    }
    clamp_camera_pos(world);
}

static void camera_left_right(my_world_t *world, float dt)
{
    float speed = CAMERA_SPEED_XY * dt * (1.f / CAMERA(world)->zoom + 1.f);

    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (KEY_PRESSED(sfKeyLControl))
        speed *= 2;
    if (KEY_PRESSED(sfKeyQ)) {
        CAMERA(world)->target_pos.x -= cos(RANGLE_Y(world)) * speed;
        CAMERA(world)->target_pos.y += sin(RANGLE_Y(world)) * speed;
    }
    if (KEY_PRESSED(sfKeyD)) {
        CAMERA(world)->target_pos.x += cos(RANGLE_Y(world)) * speed;
        CAMERA(world)->target_pos.y -= sin(RANGLE_Y(world)) * speed;
    }
    clamp_camera_pos(world);
}

static void camera_rotation(my_world_t *world, float dt)
{
    float speed = CAMERA_ROTATION_SPEED;

    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (KEY_PRESSED(sfKeyLControl))
        speed *= 2;
    if (KEY_PRESSED(sfKeyA))
        CAMERA(world)->target_angle.y -= speed * dt;
    if (KEY_PRESSED(sfKeyE))
        CAMERA(world)->target_angle.y += speed * dt;
    if (KEY_PRESSED(sfKeyW))
        CAMERA(world)->target_angle.x += speed * dt;
    if (KEY_PRESSED(sfKeyX))
        CAMERA(world)->target_angle.x -= speed * dt;
    fix_camera_angle(world);
}

static void camera_up_down(my_world_t *world, float dt)
{
    float speed = CAMERA_SPEED_Z * 20.f * dt * (1.f / CAMERA(world)->zoom);

    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (KEY_PRESSED(sfKeyLControl))
        speed *= 2;
    if (KEY_PRESSED(sfKeySpace))
        CAMERA(world)->target_pos.z += speed * dt;
    if (KEY_PRESSED(sfKeyLShift))
        CAMERA(world)->target_pos.z -= speed * dt;
}

void camera_reset(my_world_t *world)
{
    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    if (KEY_PRESSED(sfKeyR)) {
        CAMERA(world)->target_pos = (sfVector3f){CURS_X(world),
            CURS_Y(world),
            H_MAPXY(world, CURS_X(world), CURS_Y(world)) * HEIGHT_SCALE};
        CAMERA(world)->zoom_target = 1.5f;
    }
}

static float lerp_angle(float current, float target, float t)
{
    float diff = target - current;

    while (diff > 180.f)
        diff -= 360.f;
    while (diff < -180.f)
        diff += 360.f;
    return current + diff * t;
}

void update_lerp_move(my_world_t *world, float dt)
{
    if (!world || !EDITOR(world) || !CAMERA(world))
        return;
    CAMERA(world)->angle.x += (CAMERA(world)->target_angle.x -
        CAMERA(world)->angle.x) * LERP_SPEED * dt;
    CAMERA(world)->angle.y = lerp_angle(CAMERA(world)->angle.y,
        CAMERA(world)->target_angle.y, LERP_SPEED * dt);
    CAMERA(world)->pos.x += (CAMERA(world)->target_pos.x -
        CAMERA(world)->pos.x) * LERP_SPEED * dt;
    CAMERA(world)->pos.y += (CAMERA(world)->target_pos.y -
        CAMERA(world)->pos.y) * LERP_SPEED * dt;
    CAMERA(world)->pos.z += (CAMERA(world)->target_pos.z -
        CAMERA(world)->pos.z) * LERP_SPEED * dt;
}

void handle_camera_displacement(my_world_t *world, float dt)
{
    if (!world)
        return;
    camera_rotation(world, dt);
    camera_left_right(world, dt);
    camera_forward_backward(world, dt);
    camera_up_down(world, dt);
    camera_reset(world);
}
