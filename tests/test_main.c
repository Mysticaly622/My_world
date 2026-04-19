/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** Simple unit test runner for pure helpers
*/
#include "my.h"
#include <stdio.h>
#include <string.h>

static int test_custom_strcmp(void)
{
    int failures = 0;

    if (custom_strcmp("abc", "abc") != 0) {
        printf("[FAIL] custom_strcmp equal strings\n");
        failures++;
    }
    if (custom_strcmp("abc", "abd") >= 0) {
        printf("[FAIL] custom_strcmp ordering (abc < abd)\n");
        failures++;
    }
    if (custom_strcmp("abd", "abc") <= 0) {
        printf("[FAIL] custom_strcmp ordering (abd > abc)\n");
        failures++;
    }
    return failures;
}

static int test_my_incnbr(void)
{
    int failures = 0;
    char buffer[64] = {0};

    my_incnbr(buffer, 0);
    if (strcmp(buffer, "0") != 0) {
        printf("[FAIL] my_incnbr zero conversion\n");
        failures++;
    }
    memset(buffer, 0, sizeof(buffer));
    my_incnbr(buffer, 12345);
    if (strcmp(buffer, "12345") != 0) {
        printf("[FAIL] my_incnbr positive conversion\n");
        failures++;
    }
    memset(buffer, 0, sizeof(buffer));
    my_incnbr(buffer, -42);
    if (strcmp(buffer, "-42") != 0) {
        printf("[FAIL] my_incnbr negative conversion\n");
        failures++;
    }
    return failures;
}

static int test_give_size(void)
{
    int failures = 0;
    FILE *tmp = fopen("tests_tmp_size.txt", "w");

    if (!tmp) {
        printf("[FAIL] give_size setup failed\n");
        return 1;
    }
    fputs("abcd\n", tmp);
    fclose(tmp);
    if (give_size("tests_tmp_size.txt") != 5) {
        printf("[FAIL] give_size valid file\n");
        failures++;
    }
    remove("tests_tmp_size.txt");
    if (give_size("tests_not_found.txt") != 84) {
        printf("[FAIL] give_size invalid file\n");
        failures++;
    }
    return failures;
}

int main(void)
{
    int failures = 0;

    failures += test_custom_strcmp();
    failures += test_my_incnbr();
    failures += test_give_size();
    if (failures == 0) {
        printf("[OK] All unit tests passed\n");
        return 0;
    }
    printf("[KO] %d unit test(s) failed\n", failures);
    return 1;
}
