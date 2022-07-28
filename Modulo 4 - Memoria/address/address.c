#include <stdio.h>
#include <string.h>

/*
    %p = representa um pointer
    & = obtem o endereço (na memória) de uma variável
    * = operador de desreferencia, serve para "ir para" o local que o ponteiro está apontando
    Ponteiro é uma variável que armazena um endereço, ela aponta para algum lugar na memória
*/

int main(void)
{
    // int n = 50;
    // printf("int n: %i\n", n);
    // printf("endereço (hexadecimal) na memória de int n: %p\n", &n);
    // printf("int n (*&n): %i\n", *&n);

    // strings
    char *s = "Hi!"; // char * = representa uma string
    printf("%p\n", &s);

    for (int i = 0; i < strlen(s); i++)
    {
        printf("%p\n", &s[i]);
    }
}