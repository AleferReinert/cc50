#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*
    FILE = representa um arquivo
    file = nome da variável
    fopen("nome do arquivo", "modo") = abrir um arquivo
*/
int main(void)
{
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    fprintf(file, "%s, %s\n", name, number); // Imprimi no arquivo, o primeiro argumento é o arquivo
    fclose(file);
}