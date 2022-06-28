#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int valida_chave(string chave);
void substituicao(string chave, string p);
int main(int argc, string argv[])
{
    // Condição para aceitar apenas um argumento
    if (argc == 1)
    {
        printf("Digite uma chave como argumento.\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("É permitido apenas um argumento.\n");
        return 1;
    }
    else
    {
        if (valida_chave(argv[1]) != 0)
        {
            return 1;
        }
        else
        {
            string texto_simples = get_string("plaintext: ");
            substituicao(argv[1], texto_simples);
            return 0;
        };
    }
}

// Verifica se é uma chave válida (26 caracteres alfabéticos sem caracteres duplicados)
int valida_chave(string chave)
{
    if (strlen(chave) != 26)
    {
        printf("A chave precisa conter 26 caracteres.\n");
        return 1;
    }
    else
    {
        int count;
        for (int i = 0, n = strlen(chave); i < n; i++)
        {
            if (!isalpha(chave[i]))
            {
                printf("A chave precisa conter apenas caracteres alfabéticos.\n");
                return 1;
            }

            count = 1;
            for (int j = i + 1; j < strlen(chave); j++)
            {
                if (chave[i] == chave[j] && chave[i] != ' ')
                {
                    count++;
                    chave[j] = '0';
                }
                if (count > 1 && chave[i] != '0')
                {
                    printf("A chave não pode conter caracteres duplicados.\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Criptografa através da substituição
void substituicao(string chave, string p)
{
    int c = strlen(p);

    // Posições (index) das letras
    int posicoes[strlen(p)];
    for (int i = 0; i < c; i++)
    {
        posicoes[i] = p[i] - 65;
    }

    // Obtem cada caracter na chave a partir do index e printa
    printf("ciphertext: ");
    int caracter_cifrado;
    for (int i = 0; i < c; i++)
    {
        if (islower(chave[posicoes[i]]))
        {
            chave[posicoes[i]] = toupper(chave[posicoes[i]]);
        }

        if (posicoes[i] >= 32 && posicoes[i] <= 57) // Se for minusculo
        {
            posicoes[i] -= 32;
            caracter_cifrado = chave[posicoes[i]];

            if (isupper(caracter_cifrado))
            {
                caracter_cifrado = chave[posicoes[i]] + 32;
            }
        }
        else if (posicoes[i] >= 0 && posicoes[i] <= 25) // Se for maiusculo
        {
            caracter_cifrado = chave[posicoes[i]];
        }
        else // Se não for caracter alfabético, mantem igual
        {
            caracter_cifrado = p[i];
        }
        printf("%c", caracter_cifrado);
    }
    printf("\n");
}