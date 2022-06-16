#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Calcula o nível aproximado necessário para compreender algum texto e retorna a grade
int main(void)
{
    string s = get_string("Texto: ");
    int letras = 0;
    int palavras = 1;
    int frases = 0;

    // Calcula a quantidade de letras, palavras e frases
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            letras++;
        }
        else if (s[i] == ' ')
        {
            palavras++;
        }
        else if ((s[i] == '.') || (s[i] == '!') || (s[i] == '?'))
        {
            frases++;
        }
    }

    float media_letras_por_palavras = ((float)letras / palavras) * 100;
    float media_frases_por_palavras = ((float)frases / palavras) * 100;

    // Indice Coleman Liau:
    int result = round((0.0588 * media_letras_por_palavras) - (0.296 * media_frases_por_palavras) - 15.8);

    if (result >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", result);
    }
}