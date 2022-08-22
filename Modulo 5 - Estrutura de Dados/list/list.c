/*
    Listas vinculadas
    Diferente de arrays, os campos não são dispostos em sequência
    Usa dois lugares na memória para cada item, sendo o primeiro para o valor e o segundo um ponteiro para o próximo item
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int number;
    struct node *next;
} node;

int main(void)
{
    node *list = NULL;
    node *n = malloc(sizeof(node)); // Aloca espaço para caber o int e o ponteiro de node.

    if (n == NULL)
    {
        return 1;
    }
    n->number = 1;
    n->next = NULL;
    list = n; // Atualiza a lista para apontar para n

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }

    n->number = 2;
    n->next = NULL;
    list->next = n; // Para colocar após o primeiro valor

    /*
        1. Cria um ponteiro temporário (tmp) de um node, que inicia com o que estiver no início de list
        2. Enquanto tmp for diferente de NULL:
        3. Atualiza o ponteiro temporário para o próximo campo
    */
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i", tmp->number);
    }

    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}