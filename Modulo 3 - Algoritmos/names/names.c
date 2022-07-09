#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string names[] = {"Alefer", "Aline", "Gabriela", "Ana", "Junior", "Fernanda", "Jaqueline"};

    for (int i = 0; i < 7; i++)
    {
        if (strcmp(names[i], "Aline") == 0)
        {
            printf("Encontrado.\n");
            return 0;
        }
    }
    printf("Não encontrado.\n");
    return 1;
}