#include <stdio.h>
#include <cs50.h>
#include <math.h>

int devolver();

int main(void)
{
    // Espera o valor do troco inserido pelo usuário
    float real;
    int centavos;
    do
    {
        real = get_float("Troco: ");
        centavos = round(real * 100);
    } while (centavos < 1);

    printf("Centavos: %i centavos\n", centavos);

    int moedas_25c = devolver(centavos, 25);
    int moedas_10c = devolver(centavos - (moedas_25c * 25), 10);
    int moedas_5c = devolver(centavos - ((moedas_25c * 25) + (moedas_10c * 10)), 5);
    int moedas_1c = devolver(centavos - ((moedas_25c * 25) + (moedas_10c * 10) + (moedas_5c * 5)), 1);

    int total_moedas = moedas_25c + moedas_10c + moedas_5c + moedas_1c;
    printf("Total de moedas: %i\n", total_moedas);
}

// Calcula a quantidade de cada moeda a ser devolvida
int devolver(int troco, int moeda)
{
    int qtd_moeda = 0;
    while (troco >= moeda)
    {
        troco = troco - moeda;
        qtd_moeda++;
    }
    printf("Moedas de %ic: %i\n", moeda, qtd_moeda);
    return qtd_moeda;
}