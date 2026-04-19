/*
** EPITECH PROJECT, 2025
** my_inctype.c
** File description:
** cat a number or a char to a string
*/
#include "my.h"
#include <stdlib.h>

static int custom_strlen(char const *str)
{
    int size = 0;

    for (int i = 0; str[i] != '\0'; i++){
        size++;
    }
    return size;
}

static char *my_incchar(char *dest, char src)
{
    int len;

    if (!dest)
        return NULL;
    len = custom_strlen(dest);
    dest[len] = src;
    dest[len + 1] = '\0';
    return dest;
}

char *my_incnbr(char *dest, int nb)
{
    long n = nb;

    if (!dest)
        return NULL;
    if (n < 0){
        dest = my_incchar(dest, '-');
        n = -n;
    }
    if (n >= 10){
        dest = my_incnbr(dest, n / 10);
    }
    dest = my_incchar(dest, (n % 10) + '0');
    return dest;
}
