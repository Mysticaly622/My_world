/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** my_world_structs
*/

#ifndef MY_WORLD_STRUCTS_H_
    #define MY_WORLD_STRUCTS_H_
    #include <SFML/Graphics.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <SFML/Window.h>
    #include "matrix.h"
    #include "macro.h"

typedef struct mwindow_s
{
    sfRenderWindow *mwindow;
    sfVideoMode mode;
    sfColor background_color;
} mwindow_t;

typedef struct camera_s
{
    sfVector2f angle;
    sfVector2f target_angle;
    sfVector3f pos;
    sfVector3f target_pos;
    float zoom;
    float zoom_target;
} camera_t;

typedef struct sprite_s
{
    sfTexture *spritesheet;
    sfIntRect size;
    sfSprite *sprite;
} sprite_t;

typedef struct hud_s
{
    sprite_t *s;
    sfVector2f scale;
} hud_t;

typedef struct editor_s
{
    hud_t *hud;
    camera_t *camera;
    struct matrix_map_cxr *map;
    sfTexture *controlmap;
    sfVector2i select_curs;
    char *last_save;
    int showmap;
    int mode_brush;
    int enter_prev_selection;
    int enter_select_val;
    struct tile_s **sorted_tiles;
    int sorted_count;
    sfVertexArray *faces;
    sfVertexArray *lines;
    int show_lines;
} editor_t;

typedef struct my_world_s
{
    mwindow_t *mwindow;
    editor_t *editor;
    sfClock *clock;
    sfMusic *chopin;
} my_world_t;

typedef struct
{
    int min;
    int max;
    sfColor low;
    sfColor high;
} range_t;

const extern range_t ranges[COLOR_PALETTE_SIZE];

#endif /* !MY_WORLD_STRUCTS_H_ */
