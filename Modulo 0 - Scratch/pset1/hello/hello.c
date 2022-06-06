#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Apresenta o usuário
    string name = get_string("Qual seu nome?");
    int age = get_int("Qual sua idade?");
    printf("Meu nome é %s, tenho %i anos!\n", name, age);
}