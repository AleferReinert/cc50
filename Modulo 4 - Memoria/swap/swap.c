#include <stdio.h>

// Função que troca dois valores

void swap(int *a, int *b);
int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    swap(&x, &y); // Endereço de x e y
    printf("x is %i, y is %i\n", x, y);
}

void swap(int *a, int *b)
{
    int tmp = *a; // tmp recebe o valor que está no endereço de a
    *a = *b;      // o endereço de a recebe o valor que está no endereço de b
    *b = tmp;     // o endereço de b recebe tmp
}