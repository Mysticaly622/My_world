/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** matrix_struct
*/

#ifndef MACRO_H
    #define MACRO_H
    #include <SFML/Graphics.h>
    #define MAP_X_INIT (int)(100)
    #define MAP_Y_INIT (int)(100)
    #define MAX_TILT (float)(80.f)
    #define MIN_TILT (float)(15.f)
    #define MAX_ZOOM (float)(3.f)
    #define MIN_ZOOM (float)(0.1f)
    #define WATER_COLOR ((sfColor){4, 150, 255, 255})
    #define SAND_COLOR ((sfColor){247, 219, 167, 255})
    #define DIRT_COLOR ((sfColor){63, 34, 15, 255})
    #define GRASS_COLOR ((sfColor){80, 100, 60, 255})
    #define GRAVEL_COLOR ((sfColor){190, 190, 190, 255})
    #define ROCK_COLOR ((sfColor){85, 82, 93, 255})
    #define SNOW_COLOR ((sfColor){244, 244, 249, 255})
    #define CAMERA_SPEED_XY (float)(5.f)
    #define CAMERA_SPEED_Z (float)(10.f)
    #define CAMERA_ROTATION_SPEED (float)(45.f)
    #define HEIGHT_SCALE (float)(0.01f)
    #define LERP_SPEED (float)(3.f)
    #define COLOR_PALETTE_SIZE (int)(7)
    #define BASE_CAMERA_ELEVATION (float)(3.f)
    #define MY_M_PI (float)(3.14159265358979323846264338327950288)
    #define TORAD(degree) (float)((degree) * MY_M_PI / 180.0)
    #define TODEG(radian) (int)((radian) / MY_M_PI * 180.0)
    #define ANGLE_X(world) (float)(CAMERA(world)->angle.x)
    #define ANGLE_Y(world) (float)(CAMERA(world)->angle.y)
    #define RANGLE_X(world) (float)(TORAD(CAMERA(world)->angle.x))
    #define RANGLE_Y(world) (float)(TORAD(CAMERA(world)->angle.y))
    #define KEY_PRESSED(k) (sfKeyboard_isKeyPressed(k) == sfTrue)
    #define EDITOR(world) (world->editor)
    #define CAMERA(world) (world->editor->camera)
    #define MAP(world) (world->editor->map)
    #define MAPXY(world, x, y) (MAP(world)->matrix[y][x])
    #define H_MAPXY(world, x, y) (MAPXY(world, x, y).height)
    #define S_MAPXY(world, x, y) (MAPXY(world, x, y).selected)
    #define D_MAPXY(world, x, y) (MAPXY(world, x, y).d_pos)
    #define P_MAPXY(world, x, y) (MAPXY(world, x, y).depth)
    #define CURS(world) (world->editor->select_curs)
    #define CURS_X(world) (world->editor->select_curs.x)
    #define CURS_Y(world) (world->editor->select_curs.y)
    #define WIN(world) (world->mwindow->mwindow)
    #define MODE(world) (world->mwindow->mode)

#endif // MACRO_H
