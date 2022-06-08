#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Obtem do usuário uma população inicial maior ou igual a 9
    int populacao_inicial = 0;
    do
    {
        populacao_inicial = get_int("População inicial: ");
    } while (populacao_inicial < 9);

    // Obtem do usuário uma população final maior ou igual a população inicial
    int populacao_final = 0;
    do
    {
        populacao_final = get_int("População final: ");
    } while (populacao_final < populacao_inicial);

    // Calcula os nascimentos e mortes e atualiza a população
    int populacao = populacao_inicial;
    float nascimentos = 0;
    float mortes = 0;
    int anos = 0;
    while (populacao < populacao_final)
    {
        nascimentos = round(populacao / 3);
        mortes = round(populacao / 4);
        populacao = populacao + (nascimentos - mortes);
        anos++;
    }

    // Se a população atual for maior ou igual a população final, exibe os anos passados
    printf("Years: %i", anos);
}