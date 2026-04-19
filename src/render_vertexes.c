/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** render_vertexes
*/
#include "my_world.h"
#include <stdlib.h>

static int compare_depth(const void *a, const void *b)
{
    tile_t *ta = *(tile_t **)a;
    tile_t *tb = *(tile_t **)b;

    if (ta->depth < tb->depth)
        return -1;
    if (ta->depth > tb->depth)
        return 1;
    return 0;
}

static void build_sorted_tiles(my_world_t *world)
{
    int count = 0;
    tile_t **tiles = EDITOR(world)->sorted_tiles;

    for (sfVector2i curr = {0, 0}; curr.y < MAP(world)->r; curr.x++) {
        if (curr.x >= MAP(world)->c) {
            curr.y++;
            curr.x = -1;
            continue;
        }
        if (!point_near_view(world, &(sfVector2f){curr.x, curr.y}))
            continue;
        tiles[count] = &MAP(world)->matrix[curr.y][curr.x];
        count++;
    }
    qsort(tiles, count, sizeof(tile_t *), compare_depth);
    EDITOR(world)->sorted_count = count;
}

static void append_lines(my_world_t *world, int x, int y, sfVertexArray *v)
{
    int nx = (x + 1 < MAP(world)->c) ? x + 1 : x;
    int ny = (y + 1 < MAP(world)->r) ? y + 1 : y;
    sfColor w = sfWhite;

    if (!world || !EDITOR(world) || !v)
        return;
    if (nx == x || ny == y)
        return;
    sfVertexArray_append(v, (sfVertex){MAPXY(world, x, y).d_pos, w, {0}});
    sfVertexArray_append(v, (sfVertex){MAPXY(world, nx, y).d_pos, w, {0}});
    sfVertexArray_append(v, (sfVertex){MAPXY(world, x, y).d_pos, w, {0}});
    sfVertexArray_append(v, (sfVertex){MAPXY(world, x, ny).d_pos, w, {0}});
    sfVertexArray_append(v, (sfVertex){MAPXY(world, nx, y).d_pos, w, {0}});
    sfVertexArray_append(v, (sfVertex){MAPXY(world, nx, ny).d_pos, w, {0}});
    sfVertexArray_append(v, (sfVertex){MAPXY(world, x, ny).d_pos, w, {0}});
    sfVertexArray_append(v, (sfVertex){MAPXY(world, nx, ny).d_pos, w, {0}});
}

static void append_face(my_world_t *world, int x, int y, sfVertexArray *va)
{
    int nx = (x + 1 < MAP(world)->c) ? x + 1 : x;
    int ny = (y + 1 < MAP(world)->r) ? y + 1 : y;
    sfColor p1c = MAPXY(world, x, y).color;
    sfColor p2c = MAPXY(world, nx, y).color;
    sfColor p3c = MAPXY(world, nx, ny).color;
    sfColor p4c = MAPXY(world, x, ny).color;

    if (!world || !EDITOR(world) || !MAP(world))
        return;
    if (nx == x || ny == y)
        return;
    sfVertexArray_append(va, (sfVertex){MAPXY(world, x, y).d_pos, p1c, {0}});
    sfVertexArray_append(va, (sfVertex){MAPXY(world, nx, y).d_pos, p2c, {0}});
    sfVertexArray_append(va, (sfVertex){MAPXY(world, nx, ny).d_pos, p3c, {0}});
    sfVertexArray_append(va, (sfVertex){MAPXY(world, x, y).d_pos, p1c, {0}});
    sfVertexArray_append(va, (sfVertex){MAPXY(world, nx, ny).d_pos, p3c, {0}});
    sfVertexArray_append(va, (sfVertex){MAPXY(world, x, ny).d_pos, p4c, {0}});
}

static void draw_line(my_world_t *world, int x, int y)
{
    sfVertexArray_clear(EDITOR(world)->lines);
    append_lines(world, x, y, EDITOR(world)->lines);
    sfRenderWindow_drawVertexArray(WIN(world), EDITOR(world)->lines, NULL);
}

static void draw_tile(my_world_t *world, int x, int y)
{
    if (!world || !EDITOR(world) || !MAP(world))
        return;
    sfVertexArray_clear(EDITOR(world)->faces);
    append_face(world, x, y, EDITOR(world)->faces);
    sfRenderWindow_drawVertexArray(WIN(world), EDITOR(world)->faces, NULL);
}

void draw_all_tiles(my_world_t *world)
{
    int idx;
    int x;
    int y;

    build_sorted_tiles(world);
    for (int i = 0; i < EDITOR(world)->sorted_count; i++) {
        idx = EDITOR(world)->sorted_tiles[i] - MAP(world)->matrix[0];
        x = idx % MAP(world)->c;
        y = idx / MAP(world)->c;
        draw_tile(world, x, y);
        if (EDITOR(world)->show_lines)
            draw_line(world, x, y);
    }
}
