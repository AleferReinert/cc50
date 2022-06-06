#include <stdio.h>
#include <cs50.h>

int qtd_digitos(long);
void bandeira_do_cartao();
void validacao();

int main(void)
{
    long numero_do_cartao = get_long("Número do cartão de crédito: ");
    validacao(numero_do_cartao, qtd_digitos(numero_do_cartao));
}

// Verifica se é um cartão de crédito verdadeiro usando o algoritmo de Luhn
void validacao(long numero, int qtd_digitos)
{
    int digitos_somados = 0;
    int primeiros_dois_digitos = 0;

    for (int i = 0; i < qtd_digitos; i++)
    {
        int digito = numero % 10;
        numero /= 10;

        // Obtem os dois primeiros digitos para verificar qual é a bandeira
        if ((qtd_digitos == 13 && i == 10) || (qtd_digitos == 15 && i == 12) || (qtd_digitos == 16 && i == 13))
        {
            primeiros_dois_digitos += numero;
        }

        // Pega o número a cada dois digitos começando pelo penúltimo
        if (i % 2 == 1)
        {
            int digito_multiplicado = digito * 2;

            // Separa os números que são decimais
            if (digito_multiplicado > 9)
            {
                digitos_somados += digito_multiplicado / 10; // Primeiro digito
                digitos_somados += digito_multiplicado % 10; // Ultimo digito
            }
            else
            {
                digitos_somados += digito_multiplicado;
            }
        }
        else
        {
            // Pega os digitos que não foram multiplicados por 2 e adiciona a soma
            digitos_somados += digito;
        }
    }

    // Se o último digito da soma for 0 então o cartão é verdadeiro
    if (digitos_somados % 10 == 0)
    {
        bandeira_do_cartao(primeiros_dois_digitos);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Verifica a quantidade de digitos
int qtd_digitos(long numero)
{
    if (numero >= 340000000000000 && numero <= 379999999999999)
    {
        return 15;
    }
    else if (numero >= 5100000000000000 && numero <= 5599999999999999)
    {
        return 16;
    }
    else if ((numero >= 4000000000000 && numero <= 4999999999999))
    {
        return 13;
    }
    else
    {
        return 16;
    }
}

// Verifica qual é a bandeira do cartão com base nos dois primeiros digitos
void bandeira_do_cartao(int digitos)
{
    if (digitos == 34 || digitos == 37)
    {
        printf("AMEX\n");
    }
    else if (digitos >= 51 && digitos <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (digitos >= 40 && digitos <= 49)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}