#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Está faltando o argumento na linha de comando\n");
        return 1;
    }
    printf("Hello, %s\n", argv[1]);
    return 0;
}