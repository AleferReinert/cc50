#include <stdio.h>

/*
    Mostra que os valores na memória podem ser lixo, pois não foram definidos
*/

int main(void)
{
    int scores[3];

    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", scores[i]);
    }
}