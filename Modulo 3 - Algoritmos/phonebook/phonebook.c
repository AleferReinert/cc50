#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string nome;
    string numero;
} pessoa;

const int NUMBER = 3;

int main(void)
{
    pessoa pessoas[3];

    for (int i = 0; i < NUMBER; i++)
    {
        pessoas[i].nome = get_string("Qual o seu nome?");
        pessoas[i].numero = get_string("Qual o seu número?");
    }

    for (int i = 0; i < NUMBER; i++)
    {
        printf("Nome: %s\nWhatsapp: %s\n\n", pessoas[i].nome, pessoas[i].numero);
    }
}