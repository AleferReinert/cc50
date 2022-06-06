#include <stdio.h>
#include <cs50.h>

void create_blocks();
void create_spaces();

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
        create_spaces(height, i);
        create_blocks(i);
        printf("  ");
        create_blocks(i);
        printf("\n");
    }
}

// Cria a quantidade de blocos definidas pelo usuário
void create_blocks(int counter)
{
    for (int j = 0; j <= counter; j++)
    {
        printf("#");
    }
}

// Cria os espaços da primeira torre para alinhar a direita
void create_spaces(int height, int counter)
{
    for (int k = height - 1; k > counter; k--)
    {
        printf(" ");
    }
}