/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** palette_range
*/
#include "my_world.h"

const range_t ranges[COLOR_PALETTE_SIZE] = {
    {0, 50, WATER_COLOR, WATER_COLOR},
    {50, 200, WATER_COLOR, SAND_COLOR},
    {200, 800, SAND_COLOR, DIRT_COLOR},
    {800, 2000, DIRT_COLOR, GRASS_COLOR},
    {2000, 3500, GRASS_COLOR, GRAVEL_COLOR},
    {3500, 4500, GRAVEL_COLOR, ROCK_COLOR},
    {4500, 5000, ROCK_COLOR, SNOW_COLOR},
};
