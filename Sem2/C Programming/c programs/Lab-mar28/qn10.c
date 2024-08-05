#include <stdio.h>
#include <ctype.h>
#include<string.h>

void countCharacters(char *str, int *alphabets, int *digits, int *special)
{
    char *ptr = str;

    while (*ptr != '\0')
    {
        if (isalpha(*ptr))
        {
            (*alphabets)++;
        }
        else if (isdigit(*ptr))
        {
            (*digits)++;
        }
        else
        {
            (*special)++;
        }
        ptr++;
    }
}

int main()
{
    char str[100];
    int alphabets = 0, digits = 0, special = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    countCharacters(str, &alphabets, &digits, &special);

    printf("Number of alphabets: %d\n", alphabets);
    printf("Number of digits: %d\n", digits);
    printf("Number of special characters: %d\n", special);

    return 0;
}
