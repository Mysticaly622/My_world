/*
** EPITECH PROJECT, 2026
** bootstrapMyWorld
** File description:
** my_world
*/

#ifndef MY_WORLD_H_
    #define MY_WORLD_H_
    #include "my_world_structs.h"
    #include "my_world_events.h"
    #include "my_world_render.h"
    #include "my.h"
    #include "macro.h"

editor_t *init_editor(void);
void destroy_editor(editor_t **editor);

my_world_t *init_world(int ac, char **av);
void destroy_world(my_world_t **world);

void handle_event(my_world_t *world);
void handle_clock(my_world_t *world);
void handle_render(my_world_t *world);

sfVector2f project_iso_point(my_world_t *world, int x, int y, int z);
void change_val(my_world_t *world);

int point_inside_view(my_world_t *world, sfVector2f *pos);
int point_near_view(my_world_t *world, sfVector2f *pos);

int save_map(my_world_t *world);
void resume_save(my_world_t *world);
int give_size(char *filepath);
void get_save_list(void);

#endif /* !MY_WORLD_H_ */
