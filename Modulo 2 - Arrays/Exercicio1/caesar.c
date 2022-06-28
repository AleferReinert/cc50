#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int criptografia(string p, int k);

int main(int argc, string argv[])
{
    bool int_positivo = false;

    if (argc == 1)
    {
        printf("Passe um parâmetro.\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("Passe apenas um parâmetro.\n");
        return 1;
    }
    else
    {
        // Verifica se é um inteiro positivo
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (argv[1][0] == '0')
            {
                printf("Use: ./caesar key\n");
                return 1;
            }
            if (!isdigit(argv[1][i]))
            {
                printf("Use: ./caesar key\n");
                int_positivo = false;
                return 1;
            }
            else
            {
                int_positivo = true;
            }
        }
        if (int_positivo)
        {
            string p = get_string("plaintext: ");
            criptografia(p, atoi(argv[1]));
        }
        else
        {
            return 1;
        }
    }
}

int criptografia(string p, int k)
{
    char c[strlen(p)]; // texto cifrado
    int char_int;
    int limit;
    for (int i = 0; i < strlen(p); i++)
    {
        if (isalpha(p[i]))
        {
            if (islower(p[i]))
            {
                limit = 122;
            }
            else
            {
                limit = 90;
            }
            if (p[i] + k > limit)
            {
                char_int = p[i] + k;
                do
                {
                    char_int -= 26;
                } while (char_int > limit);
                c[i] = (char)char_int;
            }
            else
            {
                c[i] = p[i] + k;
            }
        }
        else
        {
            c[i] = p[i];
        }
    }
    printf("ciphertext: %s\n", (string)c);
    return 0;
}