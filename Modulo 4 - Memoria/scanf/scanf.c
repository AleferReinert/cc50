#include <stdio.h>

int main(void)
{
    // int x;
    // printf("x: ");
    // scanf("%i", &x); // Obtem a entrada do usuário armazena no endereço de x
    // printf("x: %i\n", x);

    char s[4];
    printf("s: ");
    scanf("%s", s); // Obtem a entrada do usuário armazena no endereço de s (s já é um endereço)
    printf("s: %s\n", s);
}