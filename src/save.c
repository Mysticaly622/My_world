/*
** EPITECH PROJECT, 2026
** G-ING-200-MPL-2-1-myworld-2
** File description:
** save
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "my_world.h"

char *get_time(void)
{
    time_t raw;
    char *buff = malloc(40);
    struct tm *timeinfo;

    time(&raw);
    timeinfo = localtime(&raw);
    strftime(buff, 40, "%Y-%m-%d,%H:%M:%S", timeinfo);
    return buff;
}

void get_save_list(void)
{
    DIR *save_dir = opendir("./save");
    struct dirent *save_in_dir;

    if (save_dir == NULL)
        return;
    save_in_dir = readdir(save_dir);
    while (save_in_dir != NULL) {
        if (save_in_dir->d_name[0] == '.') {
            save_in_dir = readdir(save_dir);
            continue;
        }
        printf("%s\n", save_in_dir->d_name);
        save_in_dir = readdir(save_dir);
    }
    closedir(save_dir);
}

int save_map(my_world_t *world)
{
    FILE *save;
    char *date = get_time();
    char full_path[100];

    snprintf(full_path, sizeof(full_path), "save/save_%s.legend", date);
    free(date);
    save = fopen(full_path, "w+");
    if (save == NULL)
        return ERROR_CODE;
    free(world->editor->last_save);
    world->editor->last_save = strdup(full_path);
    for (int y = 0; y < MAP(world)->r; y++) {
        for (int x = 0; x < MAP(world)->c; x++)
            fprintf(save, "%d.", H_MAPXY(world, x, y));
        fprintf(save, "\n");
    }
    fclose(save);
    return 0;
}

static char *get_file_buffer(char *filepath)
{
    FILE *save;
    size_t size = 0;
    char *buff = NULL;

    if (!filepath)
        return NULL;
    save = fopen(filepath, "r");
    if (!save)
        return NULL;
    size = give_size(filepath);
    buff = malloc(sizeof(char) * (size + 1));
    if (!buff) {
        fclose(save);
        return NULL;
    }
    fread(buff, sizeof(char), size, save);
    buff[size] = '\0';
    fclose(save);
    return buff;
}

static int check_file_integrity(char *filepath, size_t expected_size)
{
    char *buff = get_file_buffer(filepath);
    char *token;
    size_t count = 0;

    if (!buff)
        return ERROR_CODE;
    if (strstr(filepath, ".legend") == NULL) {
        free(buff);
        return ERROR_CODE;
    }
    for (token = strtok(buff, ".\n"); token; token = strtok(NULL, ".\n")) {
        if (atoi(token) > INT_MAX) {
            free(buff);
            return ERROR_CODE;
        }
        count++;
    }
    free(buff);
    return (count != expected_size) ? ERROR_CODE : 0;
}

void resume_save(my_world_t *world)
{
    char *buff;
    int val = 0;

    if (!world || !EDITOR(world) || !EDITOR(world)->last_save)
        return;
    if (check_file_integrity(EDITOR(world)->last_save,
            MAP(world)->r * MAP(world)->c))
        return;
    buff = get_file_buffer(EDITOR(world)->last_save);
    val = atoi(strtok(buff, "."));
    for (int y = 0; y < MAP(world)->r; y++)
        for (int x = 0; x < MAP(world)->c; x++) {
            H_MAPXY(world, x, y) = val;
            val = atoi(strtok(NULL, "."));
        }
    free(buff);
}
