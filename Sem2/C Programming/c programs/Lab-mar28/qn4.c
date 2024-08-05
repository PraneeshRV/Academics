#include <stdio.h>
#include <ctype.h>
#include<string.h>

void countVowelsAndConsonants(char *str, int *vowels, int *consonants)
{
    char *ptr = str;

    while (*ptr != '\0')
    {
        if (isalpha(*ptr))
        {
            switch (tolower(*ptr))
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                (*vowels)++;
                break;
            default:
                (*consonants)++;
            }
        }
        ptr++;
    }
}

int main()
{
    char str[100];
    int vowels = 0, consonants = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);


    str[strlen(str) - 1] = '\0';

    countVowelsAndConsonants(str, &vowels, &consonants);

    printf("Number of vowels: %d\n", vowels);
    printf("Number of consonants: %d\n", consonants);

    return 0;
}
