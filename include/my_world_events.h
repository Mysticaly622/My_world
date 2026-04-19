/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** my_world_events
*/

#ifndef MY_WORLD_EVENTS_H_
    #define MY_WORLD_EVENTS_H_
    #include "my_world.h"

void handle_camera_displacement(my_world_t *world, float dt);
void update_lerp_move(my_world_t *world, float dt);
void camera_reset(my_world_t *world);

void handle_zoom(my_world_t *world, sfEvent *event, float dt);
void update_lerp_zoom(my_world_t *world, float dt);

void handle_select(my_world_t *world);
void sea_level(my_world_t *world, int mode);

#endif /* !MY_WORLD_EVENTS_H_ */
