#include <stdio.h>
#include <stdlib.h>

/*
    Programa escrito para testar a ferramenta valgrind
    valgrind identifica os erros de memória
    valgrid ./memory
*/

int main(void)
{
    char *s = malloc(4);
    s[0] = 'H';
    s[1] = 'i';
    s[2] = '!';
    s[3] = '\0';
    printf("%s\n", s);
    free(s);
}