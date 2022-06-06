#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Espera uma resposta do usuário que seja entre 1 e 8 para definir a altura da piramide
    int height;
    do
    {
        height = get_int("Altura da pirâmide (entre 1 e 8): ");
    } while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {

        // Cria a quantidade certa de espaços
        for (int k = height - 1; k > i; k--)
        {
            printf(" ");
        }

        // Cria a quantidade de blocos definidas pelo usuário
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}