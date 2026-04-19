/*
** EPITECH PROJECT, 2026
** my_sh
** File description:
** size
*/

#include <sys/stat.h>
#include <stdio.h>

int give_size(char *filepath)
{
    struct stat sb = {};

    if (stat(filepath, &sb) == -1) {
        printf("File not found\n");
        return 84;
    }
    return sb.st_size;
}
