#include <cs50.h>
#include <stdio.h>

const int QUANTIDADE_DE_NOTAS = 3;
float calcular_media(int comprimento);

int main(void)
{
    printf("Média: %f\n", calcular_media(QUANTIDADE_DE_NOTAS));
}

float calcular_media(int comprimento)
{
    float media = 0;
    int notas[QUANTIDADE_DE_NOTAS];

    for (int i = 0; i < comprimento; i++)
    {
        notas[i] = get_int("Nota da prova %i: ", i + 1);
        media += notas[i];
    }
    return media / comprimento;
}