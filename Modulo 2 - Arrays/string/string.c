#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = get_string("Input: ");
    printf("Output: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");

    string words[2];
    words[0] = "Ola ";
    words[1] = "Alefer!";

    printf("%c \n", words[0][1]);
}