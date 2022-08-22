// Listas vinculadas usando malloc e realloc
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *list = malloc(3 * sizeof(int));

    if (list == NULL)
    {
        free(list);
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    int *tmp = realloc(list, 4 * sizeof(int)); // Copia list para tmp

    if (tmp == NULL)
    {
        free(tmp);
        return 1;
    }

    tmp[3] = 4;

    free(list);

    list = tmp;
    for (int i = 0; i < 4; i++)
    {
        printf("list[%i]: %i\n", i, list[i]);
    }
}