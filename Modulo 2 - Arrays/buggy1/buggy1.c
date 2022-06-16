#include <cs50.h>
#include <stdio.h>

// Protótipo
int get_negative_int(void);

int main(void)
{
    // Obtem um número negativo do usuário
    int i = get_negative_int();
    printf("%i\n", i);
}

int get_negative_int(void)
{
    int n;
    do
    {
        n = get_int("Inteiro negativo: ");
    } while (n >= 0);

    return n;
}