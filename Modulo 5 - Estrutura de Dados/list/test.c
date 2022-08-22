#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int number(char *name);
int main(void)
{
    char name[50];
    printf("Digite o nome:\n");
    scanf("%s", name);
    number(name);
    return 0;
}

int number(char *name)
{
    int first_letter = (int)name[0];
    if (isupper(first_letter))
    {
        first_letter -= 65;
    }
    else
    {
        first_letter -= 97;
    }
    printf("Primeira letra: %i\n", first_letter);
    return first_letter;
}