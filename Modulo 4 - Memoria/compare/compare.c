#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // // int
    // int i = get_int("i: ");
    // int j = get_int("j ");

    // if (i == j)
    // {
    //     printf("Igual.\n");
    // }
    // else
    // {
    //     printf("Diferente.\n");
    // }

    // string
    char *s = get_string("s: ");
    char *t = get_string("t: ");

    if (strcmp(s, t) == 0)
    {
        printf("Igual.\n");
    }
    else
    {
        printf("Diferente.\n");
    }
}