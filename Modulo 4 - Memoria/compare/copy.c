#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
    A função malloc pede memória ao computador,
    o argumento é quantos bites vão ser pedidos
*/
int main(void)
{
    char *s = get_string("s: ");
    char *t = malloc(strlen(s) + 1);

    if (t == NULL) // NULL para pointers, \0 para chars
    {
        return 1;
    }

    strcpy(t, s); // Copia o valor de uma variável para outra, no caso, t recebe s

    if (strlen(s) > 0)
    {
        t[0] = toupper(t[0]);
    }
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t); // free() devolve o espaço na memória que havia sido pedido com malloc
}