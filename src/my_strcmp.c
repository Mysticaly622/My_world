/*
** EPITECH PROJECT, 2025
** my_strcmp.c
** File description:
** Homemade function of strcmp
*/
int custom_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    int n1 = 0;
    int n2 = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        n1 = n1 + s1[i];
        n2 = n2 + s2[i];
        if (s1[i] != s2[i])
            return n1 - n2;
        i++;
    }
    n1 = n1 + s1[i];
    n2 = n2 + s2[i];
    return n1 - n2;
}
